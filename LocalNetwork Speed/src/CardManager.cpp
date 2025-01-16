/**
 * @file	CardManager.cpp
 * @brief	�J�[�h�S�̂̊Ǘ�
 * @author	NS
 * @date	2024/1/2
 */

#include "CardManager.h"


//
// �ÓI�����o�ϐ��̏�����
// 
CardManager* CardManager::instance = nullptr;


CardManager::CardManager()
{
	if (instance != nullptr) return;
	instance = this;

	// �J�[�h�̃��f���̓ǂݍ���
	Card::modelHandle = MV1LoadModel("Assets/Model/Cards/Cards.mv1");

	// �Q�[���̃Z�b�g�A�b�v
	SetUp();

	// �I�����ڂ̏����l
	selectItem = ItemList::Deck;
	selectCard = nullptr;
}

void CardManager::SetUp()
{
	//
	// �J�[�h�ɃC���X�^���X��^����
	//

	for (int i = 0; i <= 3; ++i)
	{
		for (int j = 0; j < 13; ++j)
		{
			// �J�[�h�Ƀ}�[�N�Ɣԍ���^����
			cards[j + (i * 13)] = std::make_shared<Card>(static_cast<Suit>(i), j + 1);
			// �f�b�L�ɉ�����
			deck.push_back(cards[j + (i * 13)]);
		}
	}

	//
	// ���g���z�X�g�̏ꍇ�A�Ֆʂ̏����z�u�����
	//	

	if (GameManager::playerType == PlayerType::Host)
	{
		// �̈���W(�f�b�L�̉����ڂ�)�̏�����
		for (int i = 0; i < deck.size(); ++i)
			deck[i]->areaNumber = i;

		// �f�b�L�V���b�t��
		Shuffle();


		//! 2P�̎R�D�ɉ�����J�[�h���X�g
		std::vector<std::shared_ptr<Card>> v;

		// �R�D��Suit�ŕ�����
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

		// ����̎R�D�ɉ�����
		for (auto it = v.begin(); it != v.end(); ++it)
			CardAreaChange(*it, Area::Deck_Opponent);


		// ������D
		for (int i = 0; i < InitialHandNumber_1p; ++i)
			CardAreaChange(FindCard(0, Area::Deck), Area::Hand);
		// �ΐ푊��̏�����D
		for (int i = 0; i < InitialHandNumber_2p; ++i)
			CardAreaChange(FindCard(0, Area::Deck_Opponent), Area::Hand_Opponent);

		// �t�B�[���h�̃Z�b�g
		CardAreaChange(FindCard(0, Area::Deck), Area::Field_1);
		CardAreaChange(FindCard(0, Area::Deck_Opponent), Area::Field_2);
	}
	// �N���C�A���g�̏ꍇ�A��M�f�[�^���珉���Ֆʂ��쐬
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

	// �̈���W�̍X�V
	AreaNumberUpdate(Area::Deck);
	AreaNumberUpdate(Area::Deck_Opponent);
	AreaNumberUpdate(Area::Field_1);
	AreaNumberUpdate(Area::Field_2);
	AreaNumberUpdate(Area::Hand);
	AreaNumberUpdate(Area::Hand_Opponent);
}

void CardManager::CardAreaChange(int _number, Area _newArea)
{
	// �ύX��̗̈�ƕύX�O�̗̈悪�����ꍇ�A���̂܂܏I��
	if (_newArea == cards[_number]->area)	return;

	//
	// �ύX�O�̗̈悩��폜����
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
	// �ύX��̗̈�ɒǉ�����
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

	// �ύX�O�̗̈���L��
	Area prevArea = cards[_number]->area;
	// �̈��ύX
	cards[_number]->area = _newArea;
	// �̈���W�̏�����ݒ�(��Ԍ��)
	cards[_number]->areaNumber = 9999;
	// �̈���W�̍X�V
	AreaNumberUpdate(prevArea);
	AreaNumberUpdate(_newArea);

	// �J�[�h�̃p�����[�^���ړ����ɕύX
	if (_newArea == Area::Field_1 || _newArea == Area::Field_2)
		cards[_number]->AreaChangeAnimStart(prevArea, _newArea);
}

void CardManager::CardAreaChange(std::shared_ptr<Card> _card, Area _newArea)
{
	// �ύX��̗̈�ƕύX�O�̗̈悪�����ꍇ�A���̂܂܏I��
	if (_newArea == _card->area)	return;

	//
	// �ύX�O�̗̈悩��폜����
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
	// �ύX��̗̈�ɒǉ�����
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

	// �ύX�O�̗̈���L��
	Area prevArea = _card->area;
	// �̈��ύX
	_card->area = _newArea;
	// �̈���W�̏�����ݒ�(��Ԍ��)
	_card->areaNumber = 9999;
	// �̈���W�̍X�V
	AreaNumberUpdate(prevArea);
	AreaNumberUpdate(_newArea);

	// �J�[�h�̃p�����[�^���ړ����ɕύX
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
	//! �V���b�t������z��
	std::vector<int> v;

	for (int i = 0; i < deck.size(); ++i)
		v.push_back(i);

	// �V���b�t��
	std::random_device seed_gen;
	std::mt19937 engine(seed_gen());
	std::shuffle(v.begin(), v.end(), engine);

	// �̈���W���X�V
	for (int i = 0; i < v.size(); ++i)
		deck[i]->areaNumber = v[i];

	// �̈���W�̍X�V
	AreaNumberUpdate(Area::Deck);
}

void CardManager::AreaNumberUpdate(Area _area)
{
	switch (_area)
	{
	case Area::Deck:
		// �R���e�i�N���X�̔z��̕��т�areaNumber���Ƀ\�[�g����
		std::sort(deck.begin(), deck.end(), [](std::shared_ptr<Card>& a, std::shared_ptr<Card>& b)
			{return a->areaNumber < b->areaNumber; });

		// �G���A�i���o�[��U�蕪����
		for (int i = 0; i < deck.size(); i++)
			deck[i]->areaNumber = i;
		break;

	case Area::Deck_Opponent:
		// �R���e�i�N���X�̔z��̕��т�areaNumber���Ƀ\�[�g����
		std::sort(deck_Opponent.begin(), deck_Opponent.end(), [](std::shared_ptr<Card>& a, std::shared_ptr<Card>& b)
			{return a->areaNumber < b->areaNumber; });

		// �G���A�i���o�[��U�蕪����
		for (int i = 0; i < deck_Opponent.size(); i++)
			deck_Opponent[i]->areaNumber = i;
		break;

	case Area::Field_1:
		// �R���e�i�N���X�̔z��̕��т�areaNumber���Ƀ\�[�g����
		std::sort(field_1.begin(), field_1.end(), [](std::shared_ptr<Card>& a, std::shared_ptr<Card>& b)
			{return a->areaNumber < b->areaNumber; });

		// �G���A�i���o�[��U�蕪����
		for (int i = 0; i < field_1.size(); i++)
			field_1[i]->areaNumber = i;
		break;

	case Area::Field_2:
		// �R���e�i�N���X�̔z��̕��т�areaNumber���Ƀ\�[�g����
		std::sort(field_2.begin(), field_2.end(), [](std::shared_ptr<Card>& a, std::shared_ptr<Card>& b)
			{return a->areaNumber < b->areaNumber; });

		// �G���A�i���o�[��U�蕪����
		for (int i = 0; i < field_2.size(); i++)
			field_2[i]->areaNumber = i;
		break;

	case Area::Hand:
		// �R���e�i�N���X�̔z��̕��т�areaNumber���Ƀ\�[�g����
		std::sort(hand.begin(), hand.end(), [](std::shared_ptr<Card>& a, std::shared_ptr<Card>& b)
			{return a->areaNumber < b->areaNumber; });

		// �G���A�i���o�[��U�蕪����
		for (int i = 0; i < hand.size(); i++)
			hand[i]->areaNumber = i;
		break;

	case Area::Hand_Opponent:
		// �R���e�i�N���X�̔z��̕��т�areaNumber���Ƀ\�[�g����
		std::sort(hand_Opponent.begin(), hand_Opponent.end(), [](std::shared_ptr<Card>& a, std::shared_ptr<Card>& b)
			{return a->areaNumber < b->areaNumber; });

		// �G���A�i���o�[��U�蕪����
		for (int i = 0; i < hand_Opponent.size(); i++)
			hand_Opponent[i]->areaNumber = i;
		break;
	}
}

void CardManager::SpreadHand()
{
	//
	// �����̎�D�̃J�[�h���L����
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
	// �ΐ푊��̎�D�̃J�[�h���L����
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
	// �R�D���Ȃ��ꍇ�͂��̂܂܏I��
	if (deck.size() <= 0)	return false;

	// ��D������ɒB���Ă���ꍇ���I��
	if (hand.size() >= HandNumberLimit_1p) return false;

	//
	// �R�D����ꖇ�ڂ���D�ɉ�������
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
	// �I�����Ă���J�[�h�����݂��Ȃ��ꍇ�̓f�b�L�Ǝ�D���ړ���
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
	// �J�[�h�I�𒆂̈ړ���̓t�B�[���h1,2
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
	// �����Ă��鍀�ڂŕ���
	//

	switch (selectItem)
	{
	case ItemList::Deck:
		// �f�b�L����ꖇ����
		DrawFromDeck();
		isUpdate = true;
		break;

	case ItemList::Hand_1:
		// �J�[�h�I��
		selectCard = FindCard(0,Area::Hand);
		selectItem = ItemList::Field_2;
		break;

	case ItemList::Hand_2:
		// �J�[�h�I��
		selectCard = FindCard(1, Area::Hand);
		selectItem = ItemList::Field_2;
		break;

	case ItemList::Hand_3:
		// �J�[�h�I��
		selectCard = FindCard(2, Area::Hand);
		selectItem = ItemList::Field_1;
		break;

	case ItemList::Hand_4:
		// �J�[�h�I��
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

		// �I�𒆂̃J�[�h������
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

		// �I�𒆂̃J�[�h������
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

	// ���s����
	GameJudge();

	//
// �J�[�h�̒u���ꏊ���݂��ɂȂ��Ȃ����ꍇ�̏���
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
			// �t�B�[���h�̃Z�b�g
			CardAreaChange(FindCard(0, Area::Deck), Area::Field_1);
			CardAreaChange(FindCard(0, Area::Deck_Opponent), Area::Field_2);
			isUpdate = true;
		}
	}


	//
	// �����I�ȍX�V�������Ăт���
	// 

	for (int i = 0; i < CardTotalNumber; ++i)
		cards[i]->ManualUpdate();

	// �J�[�h�̍��W�X�V
	SpreadHand();

	//
	// ���f���̕`��
	//

	MV1SetPosition(Card::modelHandle, transform->position);
	MV1SetRotationXYZ(Card::modelHandle, transform->rotate);
	MV1SetScale(Card::modelHandle, transform->scale);
	MV1DrawModel(Card::modelHandle);
}

