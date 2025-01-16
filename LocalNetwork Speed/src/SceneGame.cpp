#include "SceneGame.h"

/**
* @author   Suzuki N
* @date     24/11/20
* @note		SceneGameの実装ファイル
*/


SceneGame::SceneGame()
{
	// 実行中のシーンタグ
	sceneTag = SceneTag::Game;

	// デバッグ用 (1.5秒待機)
	//Sleep(1500);

	CM = new HWGameObject();
	CM->AddComponent<CardManager>();

	table = new HWGameObject();
	table->AddComponent<TablePresenter>();

	player = new HWGameObject();
	player->AddComponent<Player>();


	if (GameManager::playerType == PlayerType::Client)
		PreparationListenNetWork(GameManager::port);
}

SceneGame::~SceneGame()
{
	GameManager::isLose = false;
	GameManager::isWin = false;

	delete(CM);
	delete(table);
	delete(player);

	SetFontSize(30);
}

void SceneGame::Update()
{
	if (GameManager::param == GameParameter::Result)
	{
		if (resultTime == 0) 
		{
			resultTime = GetNowCount();
			SetFontSize(64);
		}

		if (GetNowCount() - resultTime > 1500)
			SceneChange(SceneTag::Title);
	}

	if (GameManager::param != GameParameter::SetUp)
		return;

	//
	// ホストは初期状態をClientに投げる
	//

	if (GameManager::playerType == PlayerType::Host)
	{
		if(!isConnected)
		{
			if (netHandle == -2)
				netHandle = ConnectNetWork(GameManager::ip, GameManager::port);

			// 接続した
			if (netHandle != -1)
			{
				isConnected = true;
				// 接続時刻を送信
				NetWorkSend(netHandle, &connectTime, sizeof(int));
			}
		}

		if (isConnected)
		{
#pragma pack(1)
			CardData data[CardTotalNumber];
#pragma pack(0)

			auto CM = CardManager::Instance();

			for (int i = 0; i < CardTotalNumber; ++i)
			{
				data[i].data = (int)CM.cards[i]->suit * 13 + CM.cards[i]->number - 1;
				data[i].area = (int)CM.cards[i]->area;
				data[i].areaNumber = CM.cards[i]->areaNumber;
			}
			unsigned char block[250];
			unsigned char* b = block;

			std::memcpy(b, data, sizeof(data));
			NetWorkSend(netHandle, &block, 250);

			GameManager::param = GameParameter::Game;
		}
	}
	// クライアントの場合
	else if (GameManager::playerType == PlayerType::Client)
	{
		if(!isConnected)
		{
			// 新しい接続があったらそのネットワークハンドルを得る
			netHandle = GetNewAcceptNetWork();

			// 接続した
			if (netHandle != -1)
				isConnected = true;
		}

		if (isConnected && (GetNetWorkDataLength(netHandle) != 0))
		{
			//! 受信データ
			unsigned char block[250];

			// データ受信
			auto DataLength = GetNetWorkDataLength(netHandle);    // データの量を取得
			NetWorkRecv(netHandle, block, DataLength);    // データをバッファに取得

			//! 受け取ったカードデータ
			CardData* cdp = (CardData*)(block + sizeof(int));

			//! 受け取ったカードデータのデコード先
			Card decodeData[CardTotalNumber];

			// カードデータをデコードする
			for (int i = 0; i < CardTotalNumber; ++i)
			{
				decodeData[i].suit = (Suit)(cdp[i].data / 13);
				decodeData[i].number = cdp[i].data % 13 + 1;
				decodeData[i].area = static_cast<Area>(cdp[i].area);
				decodeData[i].areaNumber = cdp[i].areaNumber;
			}

			CardManager::Instance().SetUpCliant(decodeData);

			GameManager::param = GameParameter::Game;
		}
	}
}
