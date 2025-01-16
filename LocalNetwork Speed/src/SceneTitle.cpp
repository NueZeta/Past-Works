#include "SceneTitle.h"

/**
* @author   Suzuki N
* @date     24/11/20
* @note		SceneTitleの実装ファイル
*/


SceneTitle::SceneTitle()
{
	// 実行中のシーンタグ
	sceneTag = SceneTag::Title;

	//
	// CSVファイルからゲーム設定を読み込む
	//

	auto str = CsvLoader::Load("Assets/csv/config.csv");

	GameManager::ip.d1 = std::stoi(str[0][1]);
	GameManager::ip.d2 = std::stoi(str[0][2]);
	GameManager::ip.d3 = std::stoi(str[0][3]);
	GameManager::ip.d4 = std::stoi(str[0][4]);
	GameManager::port = std::stoi(str[1][1]);
	GameManager::playerType = (PlayerType)std::stoi(str[2][1]);
}

SceneTitle::~SceneTitle()
{
}

void SceneTitle::Update()
{
	DrawFormatString(100, 200, GetColor(255, 255, 255), "現在の設定");
	DrawFormatString(100, 250, GetColor(255, 255, 255), "通信先のIP : %d.%d.%d.%d", GameManager::ip.d1,
		GameManager::ip.d2, GameManager::ip.d3, GameManager::ip.d4);
	DrawFormatString(100, 300, GetColor(255, 255, 255), "ポート番号 : %d", GameManager::port);

	if (GameManager::playerType == PlayerType::Host)
		DrawFormatString(100, 350, GetColor(255, 255, 255), "あなたがホストです");
	else
		DrawFormatString(100, 350, GetColor(255, 255, 255), "あなたはクライアントです");


	DrawFormatString(100, 450, GetColor(255, 255, 255), "接続を開始しますか？ y/n");

	if (CheckHitKey(KEY_INPUT_Y))
	{
		isConnect = true;
		if (GameManager::playerType == PlayerType::Host)
			netHandle = ConnectNetWork(GameManager::ip, GameManager::port);
		else
			PreparationListenNetWork(GameManager::port);
	}
	if (CheckHitKey(KEY_INPUT_N))
	{
		HandlerWaltan::End();
		exit(0);
	}

	if (!isConnect)return;

	if (isConnected)
	{
		DrawFormatString(100, 500, GetColor(255, 255, 255), "接続完了");
		if(GetNowCount() - connectTime > 1000)
		{
			// 接続を断つ
			CloseNetWork(netHandle);
			SceneChange(SceneTag::Game);
		}
	}
	else
		DrawFormatString(100, 500, GetColor(255, 255, 255), "接続中...");


	//
	// ホストとクライアントで分岐
	//

	if (GameManager::playerType == PlayerType::Host)
	{
		if (netHandle != -1)
		{
			if (connectTime == 0)
			{
				connectTime = GetNowCount();
				isConnected = true;
				// 接続時刻を送信
				NetWorkSend(netHandle, &connectTime, sizeof(int));
			}
		}
	}
	else if (GameManager::playerType == PlayerType::Client)
	{
		// 新しい接続があったらそのネットワークハンドルを得る
		netHandle = GetNewAcceptNetWork();

		if (netHandle == -1) return;

		// 接続されていたら次に進む
		if (netHandle != -1)
		{
			isConnected = true;

			// 接続の受付を終了する
			StopListenNetWork();

			if (connectTime == 0)
			{
				auto DataLength = GetNetWorkDataLength(netHandle);    // データの量を取得
				NetWorkRecv(netHandle, &connectTime, DataLength);    // データをバッファに取得
			}
		}
	}
}
