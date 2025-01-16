// 当ライブラリで必須になるインクルードファイル
// "DxLib.h" もincludeされる
#include "HandlerWaltanForDxLib.h"

#include "SceneManager.h"


// プログラムは WinMain から始まります
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// DXライブラリの初期化処理も兼ねている
	if (HandlerWaltan::Instance().Init() == -1)
	{
		return 0;
	}

	// 幅: 1920, 高さ: 1080, ビット深度: 32
	SetGraphMode(1920, 1080, 32);  
	// ウインドウモードで起動
	ChangeWindowMode(FALSE);       

	// 背景
	SetBackgroundColor(255, 255, 255);

	// デプスバッファ（Zバッファ）を有効にする
	SetUseZBuffer3D(TRUE);
	// Zバッファへの書き込みを有効にする
	SetWriteZBuffer3D(TRUE);

	// FPSを固定
	Time::SetTargetFPS(60);


	// スクリーンサイズを取得する
	GetWindowSize(&GameManager::ScreenSizeX, &GameManager::ScreenSizeY);


	//! ハンドラーやライフサイクルに基づいたタイミングでメソッドを自動的に呼び出すオブジェクト
	//! シングルトンで設計されているため、以下の方法以外でインスタンスを取得することはできない
	HandlerWaltan& HW = HandlerWaltan::Instance();

#if DEBUG

	// デバッグ用モードで起動する
	HW.debugMode = true;

#endif // DEBUG


	//! シーン管理用のクラスのインスタンスを取得
	SceneManager sceneManager = SceneManager::Instance();

	// 静的クラスの初期化
	SceneGame::Init();
	HWGameObject::GetGameObjects();

	// メインループ
	while (ProcessMessage() == 0)
	{
		//裏画面消す
		ClearDrawScreen();
		//描画先を裏画面に
		SetDrawScreen(DX_SCREEN_BACK);

		// 全てのUpdateメソッドを全て呼び出す
		HW.Update();

		// 各シーンを実行する
		sceneManager.Update();

		if (SceneManager::isEnd)
			break;


		//裏画面を表画面にコピー
		ScreenFlip();
	}

	// ソフトの終了 
	HandlerWaltan::End();

	return 0;
}