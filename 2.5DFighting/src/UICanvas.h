#pragma once
#include "GameManager.h"


/**
* @author   Suzuki N
* @date     24/11/11
* @note		UICanvas�̒�`�t�@�C��
*/


/**
 * @class	UICanvas
 * @brief   HUD�Ǘ��N���X
 */
class UICanvas
{
public:
	//  �����o�ϐ�

	//! 1P��HP�Q�[�W�摜(�w�i)
	int hpGaugeBackScreen_1p;
	//! 1P��HP�Q�[�W�摜(MAX��)
	int maxHpGauge_1p;
	//! 1P��HP�Q�[�W�摜(100%����)
	int hpGauge_1p;

	//! 2P��HP�Q�[�W�摜(�w�i)
	int hpGaugeBackScreen_2p;
	//! 2P��HP�Q�[�W�摜(MAX��)
	int maxHpGauge_2p;
	//! 2P��HP�Q�[�W�摜(100%����)
	int hpGauge_2p;

	//! FontHandle
	int fontHandle;
	//! KO���̕�����default�̃t�H���g�T�C�Y
	int defaultFontSize = 350;
	//! �t�H���g�T�C�Y
	double fontSize = 1;
	//! Fight��\����������
	int showFightTime = 0;
	//! KO��\����������
	int showKoTime = 0;
	//! Result��\����������
	int showResultTime = 0;


	// �����o�֐�
public:

	// �R���X�g���N�^
	UICanvas() : 
		hpGaugeBackScreen_1p(LoadGraph("Assets/UI/Gauge/HpGaugeBackScreen.png")), 
		maxHpGauge_1p(LoadGraph("Assets/UI/Gauge/MaxHpGauge.png")),
		hpGauge_1p(LoadGraph("Assets/UI/Gauge/hpGauge.png")),
		hpGaugeBackScreen_2p(LoadGraph("Assets/UI/Gauge/HpGaugeBackScreen.png")), 
		maxHpGauge_2p(LoadGraph("Assets/UI/Gauge/MaxHpGauge.png")),
		hpGauge_2p(LoadGraph("Assets/UI/Gauge/hpGauge.png"))
	{
		// �摜�t�@�C���̓ǂݍ��݂Ɏ��s����
		if (hpGaugeBackScreen_1p == -1 || maxHpGauge_1p == -1 || hpGauge_1p == -1 ||
			hpGaugeBackScreen_2p == -1 || maxHpGauge_2p == -1 || hpGauge_2p == -1)
			throw std::runtime_error("�����ꂩ�̉摜�t�@�C���̓ǂݍ��݂Ɏ��s���܂���");

		// ��ʃT�C�Y�̎擾
		GetWindowSize(&GameManager::screenWidth, &GameManager::screenHeight);

		// �t�H���g�n���h�����쐬(KO)
		fontHandle = CreateFontToHandle(NULL, defaultFontSize, 30, DX_FONTTYPE_ANTIALIASING_8X8);
		fontSize = 1;
	}


	/**
	 * @brief		��F�Ă΂�郁�\�b�h
	 * @author      Suzuki N
	 * @date        24/10/29
	 */
	void ManualUpdate(int _maxHp_1p, int _hp_1p, int _maxHp_2p, int _hp_2p)
	{
#pragma region HUD�̕\��

#pragma region 1P

		//! �摜�T�C�Y�擾�p
		int x, y;

		// HP��MAX�̏ꍇ
		if (_hp_1p == _maxHp_1p)
		{
			GetGraphSize(maxHpGauge_1p, &x, &y);

			DrawExtendGraph(20, 50, GameManager::screenWidth / 2 - 20,
				20 + GameManager::screenHeight / 10, maxHpGauge_1p, TRUE);
		}
		// HP��MAX�ł͂Ȃ��ꍇ�A�w�i�����킹�ĕ\������
		else
		{
			//! ����HP�̊���
			float hpRate = (float)_hp_1p / (float)_maxHp_1p;

			// ��ɔw�i�p�̉摜��\��
			GetGraphSize(hpGaugeBackScreen_1p, &x, &y);

			DrawExtendGraph(20, 50, GameManager::screenWidth / 2 - 20,
				20 + GameManager::screenHeight / 10, hpGaugeBackScreen_1p, TRUE);

			// ���̏�Ɍ��ݑ̗͂̉摜���������̈���w�肵�ĕ\��
			GetGraphSize(hpGauge_1p, &x, &y);

			DrawRectExtendGraph(20 + ((GameManager::screenWidth / 2 - 40) - (GameManager::screenWidth / 2 - 40) * hpRate),
				50, GameManager::screenWidth / 2 - 20, 20 + GameManager::screenHeight / 10,
				0, 0, (int)((float)x * hpRate), y, hpGauge_1p, TRUE);
		}

#pragma endregion

#pragma region 2P

		// HP��MAX�̏ꍇ
		if (_hp_2p == _maxHp_2p)
		{
			GetGraphSize(maxHpGauge_2p, &x, &y);

			DrawExtendGraph((GameManager::screenWidth / 2 + 20), 50, (GameManager::screenWidth - 20),
				20 + GameManager::screenHeight / 10, maxHpGauge_2p, TRUE);
		}
		// HP��MAX�ł͂Ȃ��ꍇ�A�w�i�����킹�ĕ\������
		else
		{
			//! ����HP�̊���
			float hpRate = (float)_hp_2p / (float)_maxHp_2p;

			// ��ɔw�i�p�̉摜��\��
			GetGraphSize(hpGaugeBackScreen_2p, &x, &y);

			DrawExtendGraph((GameManager::screenWidth / 2 + 20), 50, (GameManager::screenWidth - 20),
				20 + GameManager::screenHeight / 10, hpGaugeBackScreen_2p, TRUE);

			// ���̏�Ɍ��ݑ̗͂̉摜���������̈���w�肵�ĕ\��
			GetGraphSize(hpGauge_1p, &x, &y);

			DrawRectExtendGraph((GameManager::screenWidth / 2 + 20), 50, (GameManager::screenWidth / 2 + 20) +
				(int)((float)((GameManager::screenWidth - 20) - (GameManager::screenWidth / 2 + 20)) * hpRate),
				20 + GameManager::screenHeight / 10, 0, 0, (int)((float)x * hpRate), y, hpGauge_2p, TRUE);
		}
#pragma endregion

#pragma endregion


		if ((GameManager::param & GameParam::SetUp) == GameParam::SetUp)
			SetUp();

		if ((GameManager::param & GameParam::KO) == GameParam::KO)
			KO();

		if ((GameManager::param & GameParam::Result) == GameParam::Result)
			Result(_hp_1p, _hp_2p);
	}


	private:


		/**
		 * @brief		��F�Ă΂�郁�\�b�h
		 * @author      Suzuki N
		 * @date        24/10/29
		 */
		void SetUp()
		{
			if (fontSize > 0.5)
				fontSize -= 0.03;
			else
			{
				if (showFightTime == 0)
					showFightTime = GetNowCount();

				// KO��\�����Ă����莞�Ԍ�ɏ��҂�\������
				if (GetNowCount() - showFightTime > 1000)
				{
					GameManager::param = GameParam::Game;
					fontSize = 1;
					return;
				}
			}

#pragma region Fight�̕\��

			DrawExtendStringToHandle(GameManager::screenWidth / 2 - 300, GameManager::screenHeight / 2 - 50, fontSize, fontSize,
				"Fight!", GetColor(255, 0, 0), fontHandle);

#pragma endregion
		}

		/**
		 * @brief		��F�Ă΂�郁�\�b�h
		 * @author      Suzuki N
		 * @date        24/10/29
		 */
		void KO()
		{
			if (fontSize > 0.5)
				fontSize -= 0.03;
			else
			{
				if (showKoTime == 0)
					showKoTime = GetNowCount();

				// KO��\�����Ă����莞�Ԍ�ɏ��҂�\������
				if (GetNowCount() - showKoTime > 1500)
					GameManager::param = GameParam::Result;
			}

#pragma region KO�̕\��

			DrawExtendStringToHandle(GameManager::screenWidth / 2 - 100, GameManager::screenHeight / 2 - 50, fontSize, fontSize, 
				"K", GetColor(255, 0, 0), fontHandle);
			DrawExtendStringToHandle(GameManager::screenWidth / 2 + 10, GameManager::screenHeight / 2 - 50, fontSize, fontSize, 
				"O", GetColor(255, 0, 0), fontHandle);

#pragma endregion
		}


		/**
		 * @brief		��F�Ă΂�郁�\�b�h
		 * @author      Suzuki N
		 * @date        24/10/29
		 */
		void Result(int _hp_1p, int _hp_2p)
		{
			if (GetNowCount() - showKoTime < 2000)
				return;

			if (showResultTime == 0)
				showResultTime = GetNowCount();

			if (GetNowCount() - showResultTime > 3000)
			{
				GameManager::param = GameParam::Title;
				return;
			}


#pragma region ���҂̕\��

			if (_hp_1p <= 0 && _hp_2p <= 0)
			{
				DrawExtendStringToHandle(GameManager::screenWidth / 2 - 100, GameManager::screenHeight / 2 - 50, 0.2, 0.2,
					"Draw", GetColor(255, 0, 0), fontHandle);
			}
			else if(_hp_1p <= 0)
			{
				DrawExtendStringToHandle(GameManager::screenWidth / 2 - 300, GameManager::screenHeight / 2 - 50, 0.2, 0.2,
					"Winner ", GetColor(255, 0, 0), fontHandle);
				DrawExtendStringToHandle(GameManager::screenWidth / 2, GameManager::screenHeight / 2 - 50, 0.2, 0.2,
					"Player2", GetColor(255, 0, 0), fontHandle);
			}
			else if(_hp_2p <= 0)
			{
				DrawExtendStringToHandle(GameManager::screenWidth / 2 - 300, GameManager::screenHeight / 2 - 50, 0.2, 0.2,
					"Winner ", GetColor(255, 0, 0), fontHandle);
				DrawExtendStringToHandle(GameManager::screenWidth / 2, GameManager::screenHeight / 2 - 50, 0.2, 0.2,
					"Player1", GetColor(255, 0, 0), fontHandle);
			}

#pragma endregion
		}
};