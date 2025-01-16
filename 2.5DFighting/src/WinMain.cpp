#include "SceneManager.h"



// プログラムは WinMain から始まります
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// DXライブラリの初期化処理も兼ねている
	if (HandlerWaltan::Instance().Init() == -1)
		return 0;


#ifdef DEBUG

	// 幅: 1920, 高さ: 1080, ビット深度: 32
	SetGraphMode(1920 / 2, 1080 / 2, 32);
	ChangeWindowMode(TRUE);
	// デバッグモードで起動
	HandlerWaltan::debugMode = true;

#else

	// 幅: 1920, 高さ: 1080, ビット深度: 32
	SetGraphMode(1920, 1080, 32);
	// ウインドウモードで起動
	ChangeWindowMode(FALSE);
	// 非デバッグモードで起動
	HandlerWaltan::debugMode = false;

#endif // DEBUG


	// デプスバッファ（Zバッファ）を有効にする
	SetUseZBuffer3D(TRUE);
	// Zバッファへの書き込みを有効にする
	SetWriteZBuffer3D(TRUE);

	// FPSを固定
	Time::SetTargetFPS(60);


	//! ハンドラーやライフサイクルに基づいたタイミングでメソッドを自動的に呼び出すオブジェクト
	//! シングルトンで設計されているため、以下の方法以外でインスタンスを取得することはできない
	HandlerWaltan& HW = HandlerWaltan::Instance();

	//! シーンマネージャーのインスタンスを取得
	SceneManager& sceneMgr = SceneManager::Instance();


	// メインループ
	while (ProcessMessage() == 0)
	{
		//裏画面消す
		ClearDrawScreen();
		//描画先を裏画面に
		SetDrawScreen(DX_SCREEN_BACK);


		// 全てのUpdateメソッドを全て呼び出す
		HW.Update();

		// シーンを更新
		sceneMgr.Update();

		// システム終了のフラグが立ったら、そのまま終了
		if (sceneMgr.isEnd) break;


		//裏画面を表画面にコピー
		ScreenFlip();
	}

	// ソフトの終了 
	HandlerWaltan::End();

	return 0;
}