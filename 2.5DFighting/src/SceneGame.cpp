#include "SceneGame.h"

/**
* @author   Suzuki N
* @date     24/10/01
* @note		SceneGameの実装ファイル
*/


//
// 静的変数の初期化処理
//

// 最初はpause状態から始まる
GameParam GameManager::param = GameParam::SetUp;
// ゲーム開始時刻を記録
int GameManager::startTime = GetNowCount();
// 画面サイズ
int GameManager::screenWidth = 1920;
int GameManager::screenHeight = 1080;
// ヴァンパイアの飛び道具のエフェクトハンドル
int VampireModel::projectileEffectHandle = -1;


SceneGame::SceneGame(InputSystem* _input)
{
	// 実行中のシーンタグ
	sceneTag = SceneTag::Game;


	// 入力系を設定
#ifdef DEBUG
	{
		input = _input;
		// キー押下時のコールバックを設定
		callBackId = input->AddCallBack("Change", [&](InputAction::CallBackContext c) {
			if (c.state == InputState::Started) SceneChange(SceneTag::Result);
			});
	}
#endif // DEBUG


	// ライト関係
	{
		SetLightEnable(false);
		pointLightHandle_1 = CreatePointLightHandle(VGet(0, 0, 1000), 2000.0f, 0.0001f, 0.008f, 0.000f);
		pointLightHandle_2 = CreatePointLightHandle(VGet(0, 00000, -15000), 1500000.0f, 0.005f, 0.00008f, 0.000f);
		pointLightHandle_3 = CreatePointLightHandle(VGet(10000, 10000, -15000), 1500000.0f, 0.001f, 0.00006f, 0.000f);
		pointLightHandle_4 = CreatePointLightHandle(VGet(-10000, 10000, -15000), 1500000.0f, 0.001f, 0.00006f, 0.000f);
	}


	// ヴァンパイアの飛び道具のエフェクトを読み込んでおく
	VampireModel::projectileEffectHandle = LoadEffekseerEffect("Assets/Effect/FireBall.efkefc", 50.f);


	// キャラクター1 の生成
	{
		player_1 = std::make_unique<HWGameObject>("Player_1");
		player_1_presenter = player_1->AddComponent<VampirePresenter>();
		player_1->transform->position = VGet(400, GROUND,0);
		player_1->transform->rotate = VGet(0, -90, 0);
	}
	// キャラクター2 の生成
	{
		player_2 = std::make_unique<HWGameObject>("Player_2");
		player_2_presenter = player_2->AddComponent<VampirePresenter>();
		player_2->transform->position = VGet(800, GROUND, 0);
		player_2->transform->rotate = VGet(0, 90, 0);
	}

	// それぞれに相手のGameObjectの情報を与える
	player_1_presenter->opponent = player_2.get();
	player_2_presenter->opponent = player_1.get();


	// ステージの初期化
	{
		stage = std::make_unique<HWGameObject>("traningStage", 100);
		stagePresenter = stage->AddComponent<StagePresenter>();
		stagePresenter->Initialize(player_1_presenter, player_2_presenter);
	}

	// UIキャンバスの作成
	{
		canvas = std::make_unique<UICanvas>();
	}

	// フォントデータ読み込み
	fontHandle = CreateFontToHandle(NULL, 32, 2, DX_FONTTYPE_ANTIALIASING_8X8);

	
	// 各種フラグの初期化
	GameManager::startTime = GetNowCount();

	// FPSを固定
	Time::SetTargetFPS(120);

	//! ゲームパラメータを変更する
	GameManager::param = GameParam::SetUp;
}

SceneGame::~SceneGame()
{
#if DEBUG
	input->DeleteCallBack("Change", callBackId);
#endif // DEBUG

	DeleteLightHandleAll();

	// 飛び道具のエフェクトを削除
	DeleteEffekseerEffect(VampireModel::projectileEffectHandle);
}

void SceneGame::Update()
{
	if(HandlerWaltan::debugMode)
	{
		DrawFormatString(10, 50, GetColor(255, 255, 255), "%d", player_1_presenter->model->param);
		DrawFormatString(10, 30, GetColor(255, 255, 255), "%d", player_1_presenter->model->crrInputParam);
		DrawFormatString(100, 30, GetColor(255, 255, 255), "%d", player_1_presenter->transform->position.x);

		for (int i = 0; i < player_1_presenter->model->keyHistory.size(); ++i)
		{
			int y = i < 15 ? 20 : 70;
			int x = i < 15 ? 70 + 20 * i : 70 + 20 * (i - 15);

			DrawFormatString(x, y, GetColor(255, 255, 255), "%d", player_1_presenter->model->keyHistory[i]);
		}

		DrawFormatString(430, 50, GetColor(255, 255, 255), "%d", player_2_presenter->model->param);

		for (int i = 0; i < player_2_presenter->model->keyHistory.size(); ++i)
		{
			int y = i < 15 ? 20 : 70;
			int x = i < 15 ? 470 + 20 * i : 470 + 20 * (i - 15);

			DrawFormatString(x, y, GetColor(255, 255, 255), "%d", player_2_presenter->model->keyHistory[i]);
		}
	}

	// HUDの表示
	canvas->ManualUpdate(player_1_presenter->model->maxHp, player_1_presenter->model->hp,
		player_2_presenter->model->maxHp, player_2_presenter->model->hp);


	// Managerのパラメータがresultになったら遷移
	if ((GameManager::param & GameParam::Title) == GameParam::Title)
		SceneChange(SceneTag::Title);
}
