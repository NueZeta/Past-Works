#include "SceneGame.h"

/**
* @author   Suzuki N
* @date     24/11/20
* @note		SceneGame�̎����t�@�C��
*/


SceneGame::SceneGame()
{
	// ���s���̃V�[���^�O
	sceneTag = SceneTag::Game;

	// �f�o�b�O�p (1.5�b�ҋ@)
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
	// �z�X�g�͏�����Ԃ�Client�ɓ�����
	//

	if (GameManager::playerType == PlayerType::Host)
	{
		if(!isConnected)
		{
			if (netHandle == -2)
				netHandle = ConnectNetWork(GameManager::ip, GameManager::port);

			// �ڑ�����
			if (netHandle != -1)
			{
				isConnected = true;
				// �ڑ������𑗐M
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
	// �N���C�A���g�̏ꍇ
	else if (GameManager::playerType == PlayerType::Client)
	{
		if(!isConnected)
		{
			// �V�����ڑ����������炻�̃l�b�g���[�N�n���h���𓾂�
			netHandle = GetNewAcceptNetWork();

			// �ڑ�����
			if (netHandle != -1)
				isConnected = true;
		}

		if (isConnected && (GetNetWorkDataLength(netHandle) != 0))
		{
			//! ��M�f�[�^
			unsigned char block[250];

			// �f�[�^��M
			auto DataLength = GetNetWorkDataLength(netHandle);    // �f�[�^�̗ʂ��擾
			NetWorkRecv(netHandle, block, DataLength);    // �f�[�^���o�b�t�@�Ɏ擾

			//! �󂯎�����J�[�h�f�[�^
			CardData* cdp = (CardData*)(block + sizeof(int));

			//! �󂯎�����J�[�h�f�[�^�̃f�R�[�h��
			Card decodeData[CardTotalNumber];

			// �J�[�h�f�[�^���f�R�[�h����
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
