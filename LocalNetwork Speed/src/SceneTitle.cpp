#include "SceneTitle.h"

/**
* @author   Suzuki N
* @date     24/11/20
* @note		SceneTitle�̎����t�@�C��
*/


SceneTitle::SceneTitle()
{
	// ���s���̃V�[���^�O
	sceneTag = SceneTag::Title;

	//
	// CSV�t�@�C������Q�[���ݒ��ǂݍ���
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
	DrawFormatString(100, 200, GetColor(255, 255, 255), "���݂̐ݒ�");
	DrawFormatString(100, 250, GetColor(255, 255, 255), "�ʐM���IP : %d.%d.%d.%d", GameManager::ip.d1,
		GameManager::ip.d2, GameManager::ip.d3, GameManager::ip.d4);
	DrawFormatString(100, 300, GetColor(255, 255, 255), "�|�[�g�ԍ� : %d", GameManager::port);

	if (GameManager::playerType == PlayerType::Host)
		DrawFormatString(100, 350, GetColor(255, 255, 255), "���Ȃ����z�X�g�ł�");
	else
		DrawFormatString(100, 350, GetColor(255, 255, 255), "���Ȃ��̓N���C�A���g�ł�");


	DrawFormatString(100, 450, GetColor(255, 255, 255), "�ڑ����J�n���܂����H y/n");

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
		DrawFormatString(100, 500, GetColor(255, 255, 255), "�ڑ�����");
		if(GetNowCount() - connectTime > 1000)
		{
			// �ڑ���f��
			CloseNetWork(netHandle);
			SceneChange(SceneTag::Game);
		}
	}
	else
		DrawFormatString(100, 500, GetColor(255, 255, 255), "�ڑ���...");


	//
	// �z�X�g�ƃN���C�A���g�ŕ���
	//

	if (GameManager::playerType == PlayerType::Host)
	{
		if (netHandle != -1)
		{
			if (connectTime == 0)
			{
				connectTime = GetNowCount();
				isConnected = true;
				// �ڑ������𑗐M
				NetWorkSend(netHandle, &connectTime, sizeof(int));
			}
		}
	}
	else if (GameManager::playerType == PlayerType::Client)
	{
		// �V�����ڑ����������炻�̃l�b�g���[�N�n���h���𓾂�
		netHandle = GetNewAcceptNetWork();

		if (netHandle == -1) return;

		// �ڑ�����Ă����玟�ɐi��
		if (netHandle != -1)
		{
			isConnected = true;

			// �ڑ��̎�t���I������
			StopListenNetWork();

			if (connectTime == 0)
			{
				auto DataLength = GetNetWorkDataLength(netHandle);    // �f�[�^�̗ʂ��擾
				NetWorkRecv(netHandle, &connectTime, DataLength);    // �f�[�^���o�b�t�@�Ɏ擾
			}
		}
	}
}
