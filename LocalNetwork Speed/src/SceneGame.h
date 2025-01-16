#pragma once
#include "SceneBase.h"

// 追加の読み込み -------------------

#include "TablePresenter.h"
#include "CardManager.h"
#include "Player.h"

// ----------------------------------

/**
* @author   Suzuki N
* @date     24/11/20
* @note		SceneGameの定義ファイル
*/


/**
 * @class	SceneGame
 * @brief   メインゲームシーン
 */
class SceneGame : public SceneBase 
{
private:
	//メンバ変数

	HWGameObject* CM;

	HWGameObject* table;

	HWGameObject* player;

	bool isConnect = false;
	bool isConnected = false;
	int netHandle = -2;
	int connectTime = 0;
	int resultTime = 0;


public:
	// メソッド

	/**
	 * @brief       コンストラクタ
	 * @author      Suzuki N
	 * @date        24/11/20
	 */
	SceneGame();

	/**
	 * @brief       デストラクタ
	 * @author      Suzuki N
	 * @date        24/11/20
	 */
	~SceneGame() override;

	/**
	 * @brief       毎F呼ばれるメソッド
	 * @author      Suzuki N
	 * @date        24/11/20
	 */
	void Update() override;
};

