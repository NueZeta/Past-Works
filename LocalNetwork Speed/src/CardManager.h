/**
 * @file	CardManager.h
 * @brief	カード全体の管理
 * @author	NS
 * @date	2024/1/2
 */

#pragma once
#include "Card.h"


 /**
  * @class	CardManager
  * @brief  カード全体を管理するクラス
  */
class CardManager : public HWComponent
{
	//
	// メンバ変数
	//

public:

	//! シングルトンインスタンス
	static CardManager* instance;
	//! カードのインスタンス
	std::shared_ptr<Card> cards[CardTotalNumber];
	//! デッキ
	std::vector < std::shared_ptr<Card>> deck;
	//! デッキ(対戦相手)
	std::vector < std::shared_ptr<Card>> deck_Opponent;
	//! フィールド(レーン1)
	std::vector < std::shared_ptr<Card>> field_1;
	//! フィールド(レーン2)
	std::vector < std::shared_ptr<Card>> field_2;
	//! 手札
	std::vector < std::shared_ptr<Card>> hand;
	//! 手札(対戦相手)
	std::vector < std::shared_ptr<Card>> hand_Opponent;

	//! 選択中の項目
	ItemList selectItem;
	//! 選択中のカード
	std::shared_ptr<Card> selectCard;
	//! このフレーム中に変更がもたらされた
	bool isUpdate = false;


	//
	// メソッド
	//

public:

	/**
	 * @brief		コンストラクタ
	 */
	CardManager();

	/**
	 * @brief		デストラクタ
	 */
	~CardManager();

	/**
	 * @brief		初期盤面を作成
	 */
	void SetUp();

	/**
	 * @brief		クライアントの初期盤面を作成
	 */
	void SetUpCliant(Card*);

	/**
	 * @brief		デッキをシャッフルする
	 */
	void Shuffle();

	/**
	 * @brief		領域座標を更新
	 * @param		更新する領域
	 */
	void AreaNumberUpdate(Area);

	/**
	 * @brief		手札のカードを広げる
	 */
	void SpreadHand();

	/**
	 * @brief		山札から一枚引く
	 * @return		? 正常に終了(true) : 山札がないか、手札がいっぱい(false) 
	 */
	bool DrawFromDeck();
	
	/**
	 * @brief		山札から一枚引く(クライアント)
	 * @return		? 正常に終了(true) : 山札がないか、手札がいっぱい(false) 
	 */
	bool DrawFromDeckCliant();
	
	/**
	 * @brief		選択項目の移動
	 * @param[in]	移動方向
	 */
	void MoveSelectItem(Direction);

	/**
	 * @brief		項目セレクト時のアクション
	 */
	void ItemSelect();

	/**
	 * @brief		選択中のカードを解除
	 */
	void SelectCardRelease();

	/**
	 * @brief		選択中のカードをフィールドに重ねる
	 */
	void Overlap();

	/**
	 * @brief		カードの領域を変更
	 * @param[in]	変更するカードの領域内の座標
	 * @param[in]	変更後の領域
	 */
	void CardAreaChange(int, Area);

	/**
	 * @brief		カードの領域を変更
	 * @param[in]	変更するカードのインスタンス
	 * @param[in]	変更後の領域
	 */
	void CardAreaChange(std::shared_ptr<Card>, Area);

	/**
	 * @brief		領域とカード座標から指定のカードを探す
	 * @param[in]	カード座標
	 * @param[in]	検索する領域
	 * @return		検索結果(存在しない場合はnullptr)
	 */
	std::shared_ptr<Card> FindCard(int, Area);

	/**
	 * @brief		コンストラクタ
	 */
	void GameJudge();

	/**
	 * @brief		コンストラクタ
	 * @return		CardManager& インスタンス
	 */
	static CardManager& Instance();

	/**
	 * @brief		初期化関数
	 */
	void Awake()override;

	/**
	 * @brief		更新処理
	 */
	void Update()override;
};

