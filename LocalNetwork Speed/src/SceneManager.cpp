#include "SceneManager.h"

/**
* @author   Suzuki N
* @date     24/11/20
* @note		SceneManagerの実装ファイル
*/


SceneManager::SceneManager()
{
	// エラー値を入れておく
	crrSceneTag = SceneTag::NotFound;
	// ロードステータスの初期化
	atomicLoadState = SceneLoadState::Wait;

	// ゲーム終了用の入力
	{
		input = new InputSystem();
		// キーを登録
		// キーボードは Escape
		input->AddKeyCode("sys", KEY_INPUT_ESCAPE, InputType::Key);
		// Padは Start
		input->AddKeyCode("sys", PAD_INPUT_11, InputType::Pad1);
		// コールバック
		input->AddCallBack("sys", [&](InputAction::CallBackContext context) { HandlerWaltan::End(); exit(0); });
	}
	// シーン遷移用
	{
		// 特定のキーで次のシーンへ移行するようにする
		// キーボードは R
		input->AddKeyCode("Change", KEY_INPUT_RETURN, InputType::Key);
		// Padは BACK
		input->AddKeyCode("Change", PAD_INPUT_8, InputType::Pad1);
		// Padは BACK
		input->AddKeyCode("Change", PAD_INPUT_8, InputType::Pad2);
	}


	// 最初のシーン
	SceneChangeSync(SceneTag::Title);
}


void SceneManager::Update()
{
	crrScene->Update();

	// 非同期でシーンを読み込んでいる最中
	if (atomicLoadState.load() == SceneLoadState::Loading)
	{
		DrawFormatString(100, 300, GetColor(0, 255, 0), "Loading...");
	}


	// 非同期の読み込みが完了した
	if (atomicLoadState.load() == SceneLoadState::Completed)
	{
		// シーンを上書き
		std::swap(crrScene, loadScene);
		// タグも変更
		crrSceneTag = loadScene->sceneTag;
		crrScene->nextSceneTagAsync = SceneTag::NotFound;
		//　読み込みデータを削除
		delete loadScene;
		// スレッドを開放
		sceneLoadThread.detach();
		// 読み込みステータスを変更
		atomicLoadState.store(SceneLoadState::Wait);
	}

	// シーン内で遷移指示が来た場合
	if (!(crrScene->nextSceneTag == SceneTag::NotFound ||
		crrScene->nextSceneTag == crrSceneTag))
		SceneChangeSync(crrScene->nextSceneTag);

	// シーン内で非同期で行う遷移指示が来た場合
	if (!(crrScene->nextSceneTagAsync == SceneTag::NotFound ||
		crrScene->nextSceneTagAsync == crrSceneTag))
		SceneChangeAsync(crrScene->nextSceneTagAsync);
}


void SceneManager::SceneChangeSync(const SceneTag& _nextSceneTag)
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
		crrScene = new SceneTitle();
		break;

	case SceneTag::Game:
		crrScene = new SceneGame();
		break;

	case SceneTag::Result:
		crrScene = new SceneResult();
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


void SceneManager::SceneChangeAsync(const SceneTag& _nextSceneTag)
{
	// シーン読み込み中の場合、指示を無効
	if (sceneLoadThread.joinable() || atomicLoadState.load() != SceneLoadState::Wait) return;
	// 遷移指示の来たタグが実行中のシーンと同じか、NotFoundだった場合はそのまま終了
	if (_nextSceneTag == crrSceneTag || _nextSceneTag == SceneTag::NotFound) return;

	// シーン読み込み開始
	sceneLoadThread = std::thread(&SceneManager::SceneLoad, this, _nextSceneTag);
}


void SceneManager::SceneLoad(const SceneTag& _nextSceneTag)
{
	// シーン読み込み完了のフラグを折っておく
	atomicLoadState.store(SceneLoadState::Loading);

	//! 遷移先のシーンタグを記憶しておく(参照型で持っているため)
	const SceneTag nextSceneTag = _nextSceneTag;

	// タグによって遷移先のシーンを変更する
	switch (nextSceneTag)
	{

	case SceneTag::Title:
		loadScene = new SceneTitle();
		break;

	case SceneTag::Game:
		loadScene = new SceneGame();
		break;

	case SceneTag::Result:
		loadScene = new SceneResult();
		break;
	}

	// 読み込み完了
	atomicLoadState.store(SceneLoadState::Completed);
}


