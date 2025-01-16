#pragma once
#include "SceneBase.h"

// 追加の読み込み -------------------

#include "VampirePresenter.h"
#include "StagePresenter.h"
#include "UICanvas.h"

// ----------------------------------

/**
* @author   Suzuki N
* @date     24/10/01
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
	
	//! ステージオブジェクト
	std::unique_ptr<HWGameObject> stage;
	//! ステージの管理コンポーネント
	StagePresenter* stagePresenter;
	//! キャラクター1
	std::unique_ptr<HWGameObject> player_1;
	//! キャラクター1の管理コンポーネント
	VampirePresenter* player_1_presenter;
	//! キャラクター2
	std::unique_ptr<HWGameObject> player_2;
	//! キャラクター2の管理コンポーネント
	VampirePresenter* player_2_presenter;
	//! UIキャンバス
	std::unique_ptr<UICanvas> canvas;

	//! ポイントライトハンドル
	int pointLightHandle_1;
	//! ポイントライトハンドル
	int pointLightHandle_2;
	//! ポイントライトハンドル
	int pointLightHandle_3;
	//! ポイントライトハンドル
	int pointLightHandle_4;
	//! スポットライトハンドル(Playerの上部に設置する)
	int spotLightHandle;


	//! フォントデータ
	int fontHandle;


public:
	// メソッド

	// コンストラクタ
	SceneGame(InputSystem* _input);

	// デストラクタ
	~SceneGame() override;

	// 毎F呼ばれる関数
	// オーバライドメソッド
	void Update() override;
};

