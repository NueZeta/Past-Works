/**
 * @file	CardManager.cpp
 * @brief	カード全体の管理
 * @author	NS
 * @date	2024/1/2
 */

#include "CardManager.h"


//
// 静的メンバ変数の初期化
// 
CardManager* CardManager::instance = nullptr;


CardManager::CardManager()
{
	if (instance != nullptr) return;
	instance = this;

	// カードのモデルの読み込み
	Card::modelHandle = MV1LoadModel("Assets/Model/Cards/Cards.mv1");

	// ゲームのセットアップ
	SetUp();

	// 選択項目の初期値
	selectItem = ItemList::Deck;
	selectCard = nullptr;
}

void CardManager::SetUp()
{
	//
	// カードにインスタンスを与える
	//

	for (int i = 0; i <= 3; ++i)
	{
		for (int j = 0; j < 13; ++j)
		{
			// カードにマークと番号を与える
			cards[j + (i * 13)] = std::make_shared<Card>(static_cast<Suit>(i), j + 1);
			// デッキに加える
			deck.push_back(cards[j + (i * 13)]);
		}
	}

	//
	// 自身がホストの場合、盤面の初期配置を作る
	//	

	if (GameManager::playerType == PlayerType::Host)
	{
		// 領域座標(デッキの何枚目か)の初期化
		for (int i = 0; i < deck.size(); ++i)
			deck[i]->areaNumber = i;

		// デッキシャッフル
		Shuffle();


		//! 2Pの山札に加えるカードリスト
		std::vector<std::shared_ptr<Card>> v;

		// 山札をSuitで分ける
		if (Random::GetRandomInt(0, 1))
		{
			for (auto it = deck.begin(); it != deck.end(); ++it)
				if ((*it)->suit == Suit::Club || (*it)->suit == Suit::Spade)
					v.push_back(*it);
		}
		else
		{
			for (auto it = deck.begin(); it != deck.end(); ++it)
				if ((*it)->suit == Suit::Diamond || (*it)->suit == Suit::Heart)
					v.push_back(*it);
		}

		// 相手の山札に加える
		for (auto it = v.begin(); it != v.end(); ++it)
			CardAreaChange(*it, Area::Deck_Opponent);


		// 初期手札
		for (int i = 0; i < InitialHandNumber_1p; ++i)
			CardAreaChange(FindCard(0, Area::Deck), Area::Hand);
		// 対戦相手の初期手札
		for (int i = 0; i < InitialHandNumber_2p; ++i)
			CardAreaChange(FindCard(0, Area::Deck_Opponent), Area::Hand_Opponent);

		// フィールドのセット
		CardAreaChange(FindCard(0, Area::Deck), Area::Field_1);
		CardAreaChange(FindCard(0, Area::Deck_Opponent), Area::Field_2);
	}
	// クライアントの場合、受信データから初期盤面を作成
	else
	{

	}
}

void CardManager::SetUpCliant(Card* decodeData)
{
	hand.clear();
	hand_Opponent.clear();
	field_1.clear();
	field_2.clear();
	deck.clear();
	deck_Opponent.clear();

	for (int i = 0; i < CardTotalNumber; ++i)
	{
		cards[i]->suit = decodeData[i].suit;
		cards[i]->number = decodeData[i].number;
		cards[i]->areaNumber = decodeData[i].areaNumber;

		if (decodeData[i].area == Area::Deck_Opponent)
			cards[i]->area = Area::Deck;
		else if (decodeData[i].area == Area::Deck)
			cards[i]->area = Area::Deck_Opponent;
		else if (decodeData[i].area == Area::Hand)
			cards[i]->area = Area::Hand_Opponent;
		else if (decodeData[i].area == Area::Hand_Opponent)
			cards[i]->area = Area::Hand;
		else
			cards[i]->area = decodeData[i].area;

		if (cards[i]->area == Area::Deck)
			deck.push_back(cards[i]);
		if (cards[i]->area == Area::Deck_Opponent)
			deck_Opponent.push_back(cards[i]);
		if (cards[i]->area == Area::Hand)
			hand.push_back(cards[i]);
		if (cards[i]->area == Area::Hand_Opponent)
			hand_Opponent.push_back(cards[i]);
		if (cards[i]->area == Area::Field_1)
			field_1.push_back(cards[i]);
		if (cards[i]->area == Area::Field_2)
			field_2.push_back(cards[i]);
	}

	// 領域座標の更新
	AreaNumberUpdate(Area::Deck);
	AreaNumberUpdate(Area::Deck_Opponent);
	AreaNumberUpdate(Area::Field_1);
	AreaNumberUpdate(Area::Field_2);
	AreaNumberUpdate(Area::Hand);
	AreaNumberUpdate(Area::Hand_Opponent);
}

void CardManager::CardAreaChange(int _number, Area _newArea)
{
	// 変更後の領域と変更前の領域が同じ場合、そのまま終了
	if (_newArea == cards[_number]->area)	return;

	//
	// 変更前の領域から削除する
	//

	if (cards[_number]->area == Area::Deck)
		deck.erase(deck.begin() + _number);
	else if (cards[_number]->area == Area::Deck_Opponent)
		deck_Opponent.erase(deck_Opponent.begin() + _number);

	else if (cards[_number]->area == Area::Field_1)
		field_1.erase(field_1.begin() + _number);
	else if (cards[_number]->area == Area::Field_2)
		field_2.erase(field_2.begin() + _number);

	else if (cards[_number]->area == Area::Hand)
		hand.erase(hand.begin() + _number);
	else if (cards[_number]->area == Area::Hand_Opponent)
		hand_Opponent.erase(hand.begin() + _number);

	//
	// 変更後の領域に追加する
	//

	if (_newArea == Area::Deck)
		deck.push_back(cards[_number]);
	else if (_newArea == Area::Deck_Opponent)
		deck_Opponent.push_back(cards[_number]);

	else if (_newArea == Area::Field_1)
		field_1.push_back(cards[_number]);
	else if (_newArea == Area::Field_2)
		field_2.push_back(cards[_number]);

	else if (_newArea == Area::Hand)
		hand.push_back(cards[_number]);
	else if (_newArea == Area::Hand_Opponent)
		hand_Opponent.push_back(cards[_number]);

	// 変更前の領域を記憶
	Area prevArea = cards[_number]->area;
	// 領域を変更
	cards[_number]->area = _newArea;
	// 領域座標の初期を設定(一番後ろ)
	cards[_number]->areaNumber = 9999;
	// 領域座標の更新
	AreaNumberUpdate(prevArea);
	AreaNumberUpdate(_newArea);

	// カードのパラメータを移動中に変更
	if (_newArea == Area::Field_1 || _newArea == Area::Field_2)
		cards[_number]->AreaChangeAnimStart(prevArea, _newArea);
}

void CardManager::CardAreaChange(std::shared_ptr<Card> _card, Area _newArea)
{
	// 変更後の領域と変更前の領域が同じ場合、そのまま終了
	if (_newArea == _card->area)	return;

	//
	// 変更前の領域から削除する
	//

	if (_card->area == Area::Deck)
		deck.erase(std::find(deck.begin(), deck.end(), _card));
	else if (_card->area == Area::Deck_Opponent)
		deck_Opponent.erase(std::find(deck_Opponent.begin(), deck_Opponent.end(), _card));

	else if (_card->area == Area::Field_1)
		field_1.erase(std::find(field_1.begin(), field_1.end(), _card));
	else if (_card->area == Area::Field_2)
		field_2.erase(std::find(field_2.begin(), field_2.end(), _card));

	else if (_card->area == Area::Hand)
		hand.erase(std::find(hand.begin(), hand.end(), _card));
	else if (_card->area == Area::Hand_Opponent)
		hand_Opponent.erase(std::find(hand_Opponent.begin(), hand_Opponent.end(), _card));

	//
	// 変更後の領域に追加する
	//

	if (_newArea == Area::Deck)
		deck.push_back(_card);
	else if (_newArea == Area::Deck_Opponent)
		deck_Opponent.push_back(_card);

	else if (_newArea == Area::Field_1)
		field_1.push_back(_card);
	else if (_newArea == Area::Field_2)
		field_2.push_back(_card);

	else if (_newArea == Area::Hand)
		hand.push_back(_card);
	else if (_newArea == Area::Hand_Opponent)
		hand_Opponent.push_back(_card);

	// 変更前の領域を記憶
	Area prevArea = _card->area;
	// 領域を変更
	_card->area = _newArea;
	// 領域座標の初期を設定(一番後ろ)
	_card->areaNumber = 9999;
	// 領域座標の更新
	AreaNumberUpdate(prevArea);
	AreaNumberUpdate(_newArea);

	// カードのパラメータを移動中に変更
	if (_newArea == Area::Field_1 || _newArea == Area::Field_2)
		_card->AreaChangeAnimStart(prevArea, _newArea);
}

std::shared_ptr<Card> CardManager::FindCard(int _areaNumber, Area _area)
{
	switch (_area)
	{
	case Area::Deck:
		if (_areaNumber < 0 || _areaNumber >= deck.size()) return nullptr;
		return *std::find_if(deck.begin(), deck.end(), 
			[&](std::shared_ptr<Card> a) {return a->areaNumber == _areaNumber; });
		break;

	case Area::Deck_Opponent:
		if (_areaNumber < 0 || _areaNumber >= deck_Opponent.size()) return nullptr;
		return *std::find_if(deck_Opponent.begin(), deck_Opponent.end(),
			[&](std::shared_ptr<Card> a) {return a->areaNumber == _areaNumber; });
		break;

	case Area::Field_1:
		if (_areaNumber < 0 || _areaNumber >= field_1.size()) return nullptr;
		return *std::find_if(field_1.begin(), field_1.end(),
			[&](std::shared_ptr<Card> a) {return a->areaNumber == _areaNumber; });
		break;

	case Area::Field_2:
		if (_areaNumber < 0 || _areaNumber >= field_2.size()) return nullptr;
		return *std::find_if(field_2.begin(), field_2.end(),
			[&](std::shared_ptr<Card> a) {return a->areaNumber == _areaNumber; });
		break;

	case Area::Hand:
		if (_areaNumber < 0 || _areaNumber >= hand.size()) return nullptr;
		return *std::find_if(hand.begin(), hand.end(),
			[&](std::shared_ptr<Card> a) {return a->areaNumber == _areaNumber; });
		break;

	case Area::Hand_Opponent:
		if (_areaNumber < 0 || _areaNumber >= hand_Opponent.size()) return nullptr;
		return *std::find_if(hand_Opponent.begin(), hand_Opponent.end(),
			[&](std::shared_ptr<Card> a) {return a->areaNumber == _areaNumber; });
		break;

	default:
		return nullptr;
		break;
	}
}

void CardManager::GameJudge()
{
	if (hand.size() <= 0 && deck.size() <= 0)
		GameManager::isWin = true;
	if (hand_Opponent.size() <= 0 && deck_Opponent.size() <= 0)
		GameManager::isLose = true;
}

void CardManager::Shuffle()
{
	//! シャッフルする配列
	std::vector<int> v;

	for (int i = 0; i < deck.size(); ++i)
		v.push_back(i);

	// シャッフル
	std::random_device seed_gen;
	std::mt19937 engine(seed_gen());
	std::shuffle(v.begin(), v.end(), engine);

	// 領域座標を更新
	for (int i = 0; i < v.size(); ++i)
		deck[i]->areaNumber = v[i];

	// 領域座標の更新
	AreaNumberUpdate(Area::Deck);
}

void CardManager::AreaNumberUpdate(Area _area)
{
	switch (_area)
	{
	case Area::Deck:
		// コンテナクラスの配列の並びをareaNumber順にソートする
		std::sort(deck.begin(), deck.end(), [](std::shared_ptr<Card>& a, std::shared_ptr<Card>& b)
			{return a->areaNumber < b->areaNumber; });

		// エリアナンバーを振り分ける
		for (int i = 0; i < deck.size(); i++)
			deck[i]->areaNumber = i;
		break;

	case Area::Deck_Opponent:
		// コンテナクラスの配列の並びをareaNumber順にソートする
		std::sort(deck_Opponent.begin(), deck_Opponent.end(), [](std::shared_ptr<Card>& a, std::shared_ptr<Card>& b)
			{return a->areaNumber < b->areaNumber; });

		// エリアナンバーを振り分ける
		for (int i = 0; i < deck_Opponent.size(); i++)
			deck_Opponent[i]->areaNumber = i;
		break;

	case Area::Field_1:
		// コンテナクラスの配列の並びをareaNumber順にソートする
		std::sort(field_1.begin(), field_1.end(), [](std::shared_ptr<Card>& a, std::shared_ptr<Card>& b)
			{return a->areaNumber < b->areaNumber; });

		// エリアナンバーを振り分ける
		for (int i = 0; i < field_1.size(); i++)
			field_1[i]->areaNumber = i;
		break;

	case Area::Field_2:
		// コンテナクラスの配列の並びをareaNumber順にソートする
		std::sort(field_2.begin(), field_2.end(), [](std::shared_ptr<Card>& a, std::shared_ptr<Card>& b)
			{return a->areaNumber < b->areaNumber; });

		// エリアナンバーを振り分ける
		for (int i = 0; i < field_2.size(); i++)
			field_2[i]->areaNumber = i;
		break;

	case Area::Hand:
		// コンテナクラスの配列の並びをareaNumber順にソートする
		std::sort(hand.begin(), hand.end(), [](std::shared_ptr<Card>& a, std::shared_ptr<Card>& b)
			{return a->areaNumber < b->areaNumber; });

		// エリアナンバーを振り分ける
		for (int i = 0; i < hand.size(); i++)
			hand[i]->areaNumber = i;
		break;

	case Area::Hand_Opponent:
		// コンテナクラスの配列の並びをareaNumber順にソートする
		std::sort(hand_Opponent.begin(), hand_Opponent.end(), [](std::shared_ptr<Card>& a, std::shared_ptr<Card>& b)
			{return a->areaNumber < b->areaNumber; });

		// エリアナンバーを振り分ける
		for (int i = 0; i < hand_Opponent.size(); i++)
			hand_Opponent[i]->areaNumber = i;
		break;
	}
}

void CardManager::SpreadHand()
{
	//
	// 自分の手札のカードを広げる
	//

	for (auto it = hand.begin(); it != hand.end(); ++it)
	{
		if (CardManager::Instance().hand.size() % 2)
		{
			int distance = (*it)->areaNumber - hand.size() / 2;
			(*it)->position.x = distance * -20;
		}
		else
		{
			int distance = (*it)->areaNumber - hand.size() / 2;
			(*it)->position.x = distance * -20 - 10;
		}
	}

	//
	// 対戦相手の手札のカードを広げる
	//

	for (auto it = hand_Opponent.begin(); it != hand_Opponent.end(); ++it)
	{
		if (CardManager::Instance().hand_Opponent.size() % 2)
		{
			int distance = (*it)->areaNumber - hand_Opponent.size() / 2;
			(*it)->position.x = distance * 20;
		}
		else
		{
			int distance = (*it)->areaNumber - hand_Opponent.size() / 2;
			(*it)->position.x = distance * 20 + 10;
		}
	}
}

bool CardManager::DrawFromDeck()
{
	// 山札がない場合はそのまま終了
	if (deck.size() <= 0)	return false;

	// 手札が上限に達している場合も終了
	if (hand.size() >= HandNumberLimit_1p) return false;

	//
	// 山札から一枚目を手札に加ええる
	//

	CardAreaChange(*(deck.end() - 1), Area::Hand);

	return true;
}

bool CardManager::DrawFromDeckCliant()
{
	return false;
}

void CardManager::MoveSelectItem(Direction _dir)
{
	//
	// 選択しているカードが存在しない場合はデッキと手札が移動先
	//

	if (selectCard == nullptr)
	{
		if (_dir == Direction::Left)
		{
			if (selectItem == ItemList::Deck && hand.size() > 0)
				selectItem = ItemList::Hand_1;
			else if (selectItem == ItemList::Hand_1 && hand.size() > 1)
				selectItem = ItemList::Hand_2;
			else if (selectItem == ItemList::Hand_2 && hand.size() > 2)
				selectItem = ItemList::Hand_3;
			else if (selectItem == ItemList::Hand_3 && hand.size() > 3)
				selectItem = ItemList::Hand_4;

			else if (static_cast<int>(selectItem) == hand.size())
				selectItem = ItemList::Deck;
		}
		if (_dir == Direction::Right)
		{
			if (selectItem == ItemList::Deck && hand.size() > 0)
				selectItem = static_cast<ItemList>(hand.size());
			else if (selectItem != ItemList::Deck)
				selectItem = static_cast<ItemList>(static_cast<int>(selectItem) - 1);
		}
	}

	//
	// カード選択中の移動先はフィールド1,2
	//

	else if (selectCard != nullptr)
	{
		if (selectItem == ItemList::Field_1)
			selectItem = ItemList::Field_2;
		else if (selectItem == ItemList::Field_2)
			selectItem = ItemList::Field_1;
	}
}

void CardManager::ItemSelect()
{
	//
	// 合っている項目で分岐
	//

	switch (selectItem)
	{
	case ItemList::Deck:
		// デッキから一枚引く
		DrawFromDeck();
		isUpdate = true;
		break;

	case ItemList::Hand_1:
		// カード選択
		selectCard = FindCard(0,Area::Hand);
		selectItem = ItemList::Field_2;
		break;

	case ItemList::Hand_2:
		// カード選択
		selectCard = FindCard(1, Area::Hand);
		selectItem = ItemList::Field_2;
		break;

	case ItemList::Hand_3:
		// カード選択
		selectCard = FindCard(2, Area::Hand);
		selectItem = ItemList::Field_1;
		break;

	case ItemList::Hand_4:
		// カード選択
		selectCard = FindCard(3, Area::Hand);
		selectItem = ItemList::Field_1;
		break;

	case ItemList::Field_1:
		Overlap();
		break;

	case ItemList::Field_2:
		Overlap();
		break;
	}
}

void CardManager::Overlap()
{

	if (selectItem == ItemList::Field_1)
	{
		if ((std::abs(selectCard->number - field_1[field_1.size() - 1]->number) != 1) &&
				!((selectCard->number == 1 && field_1[field_1.size() - 1]->number == 13) ||
				(selectCard->number == 13 && field_1[field_1.size() - 1]->number == 1)))
			return;
		CardAreaChange(selectCard, Area::Field_1);

		// 選択中のカードを解除
		SelectCardRelease();
		isUpdate = true;
	}
	else if (selectItem == ItemList::Field_2)
	{
		if ((std::abs(selectCard->number - field_2[field_2.size() - 1]->number) != 1) &&
				!((selectCard->number == 1 && field_2[field_2.size() - 1]->number == 13) ||
				(selectCard->number == 13 && field_2[field_2.size() - 1]->number == 1)))
			return;
		CardAreaChange(selectCard, Area::Field_2);

		// 選択中のカードを解除
		SelectCardRelease();
		isUpdate = true;
	}
}

void CardManager::SelectCardRelease()
{
	if (selectCard != nullptr) 
	{
		selectCard = nullptr;
		selectItem = ItemList::Deck;
	}
}

CardManager::~CardManager()
{
}

CardManager& CardManager::Instance()
{	
	if (instance == nullptr)
		instance = new CardManager();

	return *instance;
}

void CardManager::Awake()
{
	transform->scale = { 12,12,12 };
	transform->position.x = 0;
}

void CardManager::Update()
{
	if (GameManager::param != GameParameter::Game) return;

	// 勝敗判定
	GameJudge();

	//
// カードの置き場所が互いになくなった場合の処理
//

	if (hand.size() == 4 && hand_Opponent.size() == 4)
	{
		bool gameJam = true;
		for (auto it = hand.begin(); it != hand.end(); ++it)
		{
			if (((std::abs((*it)->number - field_1[field_1.size() - 1]->number) == 1) ||
				((*it)->number == 1 && field_1[field_1.size() - 1]->number == 13) ||
				((*it)->number == 13 && field_1[field_1.size() - 1]->number == 1))
				||
				((std::abs((*it)->number - field_2[field_2.size() - 1]->number) == 1) ||
					((*it)->number == 1 && field_2[field_2.size() - 1]->number == 13) ||
					((*it)->number == 13 && field_2[field_2.size() - 1]->number == 1)))
			{
				gameJam = false;
				break;
			}
		}
		for (auto it = hand_Opponent.begin(); it != hand_Opponent.end(); ++it)
		{
			if (((std::abs((*it)->number - field_1[field_1.size() - 1]->number) == 1) ||
				((*it)->number == 1 && field_1[field_1.size() - 1]->number == 13) ||
				((*it)->number == 13 && field_1[field_1.size() - 1]->number == 1))
				||
				((std::abs((*it)->number - field_2[field_2.size() - 1]->number) == 1) ||
					((*it)->number == 1 && field_2[field_2.size() - 1]->number == 13) ||
					((*it)->number == 13 && field_2[field_2.size() - 1]->number == 1)))
			{
				gameJam = false;
				break;
			}
		}

		if (gameJam)
		{
			// フィールドのセット
			CardAreaChange(FindCard(0, Area::Deck), Area::Field_1);
			CardAreaChange(FindCard(0, Area::Deck_Opponent), Area::Field_2);
			isUpdate = true;
		}
	}


	//
	// 明示的な更新処理を呼びだす
	// 

	for (int i = 0; i < CardTotalNumber; ++i)
		cards[i]->ManualUpdate();

	// カードの座標更新
	SpreadHand();

	//
	// モデルの描画
	//

	MV1SetPosition(Card::modelHandle, transform->position);
	MV1SetRotationXYZ(Card::modelHandle, transform->rotate);
	MV1SetScale(Card::modelHandle, transform->scale);
	MV1DrawModel(Card::modelHandle);
}

