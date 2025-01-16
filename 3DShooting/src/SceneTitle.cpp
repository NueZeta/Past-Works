#include "SceneTitle.h"

/**
* @author   Suzuki N
* @date     24/10/01
* @note		SceneTitleの実装ファイル
*/


SceneTitle::SceneTitle(InputSystem* _Input)
{
	// 実行中のシーンタグ
	sceneTag = SceneTag::Title;

	// SceneManagerのシステム系InputSystemを受け取る
	sysInput = _Input;
	// シーン遷移用コールバック関数を登録
	// R キーでシーン遷移
	{
		sysInput->AddKeyCode("sceneChange", KEY_INPUT_R);
		callBackId = sysInput->AddCallBack("sceneChange", [&](InputAction::CallBackContext context)
			{
				if (context.state == InputState::Started)
					SceneChange(SceneTag::Game);
			});
	}
}

SceneTitle::~SceneTitle()
{
	sysInput->DeleteCallBack("sceneChange", callBackId);
}

void SceneTitle::Update()
{
	DrawFormatString(10, 50, GetColor(0, 0, 0), "SceneTitle");
	DrawFormatString(10, 70, GetColor(0, 0, 0), "R でGame");

	DrawFormatString(GameManager::ScreenSizeX / 2 - 10, 70, GetColor(0, 0, 0), "操作説明");
	DrawFormatString(GameManager::ScreenSizeX / 2 + 10, 130, GetColor(0, 0, 0), "W");
	DrawFormatString(GameManager::ScreenSizeX / 2 - 50, 170, GetColor(0, 0, 0), "A    移動    S");
	DrawFormatString(GameManager::ScreenSizeX / 2 + 10, 210, GetColor(0, 0, 0), "D");

	DrawFormatString(GameManager::ScreenSizeX / 2 - 10, 250, GetColor(0, 0, 0), "攻撃 : SPACE");

}
