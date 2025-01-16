
#pragma comment(lib,"プロジェクトに追加すべきファイル/HandlerWaltanForDxLib_d.lib")


#include "SceneManager.h"


GameParameter GameManager::param = GameParameter::SetUp;
bool GameManager::isWin = false;
bool GameManager::isLose = false;
PlayerType GameManager::playerType = PlayerType::Host;
IPDATA GameManager::ip = {0,0,0};
int GameManager::port = -2;



int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// DXライブラリの初期化処理も兼ねている
	if (HandlerWaltan::Instance().Init() == -1)
	{
		return 0;
	}


	SetUseZBuffer3D(TRUE);     // デプスバッファ（Zバッファ）を有効にする
	SetWriteZBuffer3D(TRUE);   // Zバッファへの書き込みを有効にする

	SetGraphMode(1920, 1080, 16);
	ChangeWindowMode(TRUE);

	SetFontSize(30);


	//! ハンドラーやライフサイクルに基づいたタイミングでメソッドを自動的に呼び出すオブジェクト
	//! シングルトンで設計されているため、以下の方法以外でインスタンスを取得することはできない
	HandlerWaltan& HW = HandlerWaltan::Instance();

	//! シーンマネージャー
	SceneManager& SM = SceneManager::Instance();
	SM.SceneChangeSync(SceneTag::Title);

	// メインループ
	while (ProcessMessage() == 0)
	{
		//裏画面消す
		ClearDrawScreen();
		//描画先を裏画面に
		SetDrawScreen(DX_SCREEN_BACK);

		SM.Update();

		// 全てのUpdateメソッドを全て呼び出す
		HW.Update();

		if (GameManager::isWin)
			DrawFormatString(500, 300, GetColor(255, 255, 255), "勝利");
		if (GameManager::isLose)
			DrawFormatString(500, 300, GetColor(255, 255, 255), "敗北");

		//裏画面を表画面にコピー
		ScreenFlip();
	}

	// ソフトの終了 
	HandlerWaltan::End();

	return 0;
}