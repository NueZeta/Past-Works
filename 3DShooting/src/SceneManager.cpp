#include "SceneManager.h"

/**
* @author   Suzuki N
* @date     24/10/01
* @note		SceneManagerの実装ファイル
*/

bool SceneManager::isEnd = false;

SceneManager::SceneManager()
{
	// エラー値を入れておく
	crrSceneTag = SceneTag::NotFound;

	// 入力系の初期化
	{
		sysInput = new InputSystem();
		// escapeキーで終了
		{
			sysInput->AddKeyCode("close", KEY_INPUT_ESCAPE);
			sysInput->AddCallBack("close", [&](InputAction::CallBackContext context) { isEnd = true; });
		}
	}

	// 最初のシーン
	SceneChange(SceneTag::Title);
}

SceneManager::~SceneManager()
{
	delete sysInput;
}

void SceneManager::Update()
{
	crrScene->Update();

	// シーン内で遷移指示が来た場合
	if (!(crrScene->nextSceneTag == SceneTag::NotFound ||
		crrScene->nextSceneTag == crrSceneTag))
		SceneChange(crrScene->nextSceneTag);
}

void SceneManager::SceneChange(const SceneTag& _nextSceneTag)
{
	// 遷移指示の来たタグが実行中のシーンと同じか、NotFoundだった場合はそのまま終了
	if (_nextSceneTag == crrSceneTag || _nextSceneTag == SceneTag::NotFound)
		return;

	// タグによって遷移先のシーンを変更する
	switch (_nextSceneTag)
	{
	case SceneTag::Title:
		// 明示的に現在のシーンをdeleteする
		delete(crrScene);
		crrScene = new SceneTitle(sysInput);
		break;

	case SceneTag::Game:
		// 明示的に現在のシーンをdeleteする
		delete(crrScene);
		crrScene = new SceneGame(sysInput);
		break;

	case SceneTag::Result:
		// 明示的に現在のシーンをdeleteする
		delete(crrScene);
		crrScene = new SceneResult(sysInput);
		break;

		/*
		// Sceneを増やす際は、こことSceneBase.hにあるSceneTagに追加で記述する

	case SceneTag:: :
		crrScene = new 追加シーン();
		break;
		*/
	}

	// シーンタグを更新
	crrSceneTag = _nextSceneTag;
}

