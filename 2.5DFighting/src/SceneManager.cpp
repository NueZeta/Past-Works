#include "SceneManager.h"

/**
* @author   Suzuki N
* @date     24/10/01
* @note		SceneManagerの実装ファイル
*/


SceneManager::SceneManager()
{
	// エラー値を入れておく
	crrSceneTag = SceneTag::NotFound;

	// ゲーム終了用の入力
	{
		input = new InputSystem();
		// キーを登録
		// キーボードは Escape
		input->AddKeyCode("sys", KEY_INPUT_ESCAPE, InputType::Key);
		// Padは Start
		input->AddKeyCode("sys",PAD_INPUT_11, InputType::Pad1);
		// コールバック
		input->AddCallBack("sys", [&](InputAction::CallBackContext context) { isEnd = true; });

		// シーン遷移用
		// 特定のキーで次のシーンへ移行するようにする
		// キーボードは R
		input->AddKeyCode("Change", KEY_INPUT_RETURN, InputType::Key);
		// Padは BACK
		input->AddKeyCode("Change", PAD_INPUT_8, InputType::Pad1);
		// Padは BACK
		input->AddKeyCode("Change", PAD_INPUT_8, InputType::Pad2);
	}


	// 最初のシーン
	SceneChange(SceneTag::Title);
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

	// ! 遷移先のシーンタグを記憶しておく(参照型で持っているため)
	const SceneTag nextSceneTag = _nextSceneTag;

	// 実行中のシーンを削除
	if(crrScene != nullptr)
		delete(crrScene);

	// タグによって遷移先のシーンを変更する
	switch (nextSceneTag)
	{

	case SceneTag::Title:
		crrScene = new SceneTitle(input);
		break;

	case SceneTag::Game:
		crrScene = new SceneGame(input);
		break;

	case SceneTag::Result:
		crrScene = new SceneResult(input);
		break;

		/*
		// Sceneを増やす際は、こことSceneBase.hにあるSceneTagに追加で記述する

	case SceneTag:: :
		crrScene = new 追加シーン();
		break;
		*/
	}

	// シーンタグを更新
	crrSceneTag = nextSceneTag;
}

