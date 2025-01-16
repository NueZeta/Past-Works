#pragma once
#include "Define.h"
#include<iostream>
#include<fstream>

/**
* @author   Suzuki N
* @date     24/10/08
* @note		Score�̒�`�t�@�C��
*/


/**
 * @class	Score
 * @brief   �X�R�A�Ǘ��p�̐ÓI�N���X
 */class Score
{
public:
	// �����o�ϐ�

	//! �X�R�A
	static int score;


	// �e�L�X�g�ɋL�^����
	static void ScoreSave(const std::string& _path)
	{
		// �t�@�C�����쐬
		std::ofstream file(_path.c_str());

		// �X�R�A���L�^
		file << std::to_string(score);
		file.close();
	}

	// �X�R�A��ǂݍ���
	static int ScoreLoad(const std::string& _path)
	{
		// �t�@�C����ǂݍ���
		std::ifstream file(_path.c_str());
		if (!file)  return -1;

		//! �e�L�X�g�̕�����̓��͐�
		std::string line;

		// �X�R�A��ǂݍ���
		while (std::getline(file, line))
			// ������𐔎��ɒu��������
			return std::stoi(line);

		return -1;
	}
};
 
 /**
 * @class	GameManager
 * @brief   �X�R�A�Ǘ��p�̐ÓI�N���X
 */
 class GameManager
{
public:
	// �����o�ϐ�

	//! �X�N���[���T�C�Y
	static int ScreenSizeX;
	static int ScreenSizeY;
	//! �N���A�t���O
	static bool isClear;
	//! �Q�[���X�g�b�v
	static bool isStop;
	//! �m�[�_���[�W�N���A
	static bool isNoDamage;
	//! ���肬��ŃN���A
	static bool isMortalCombat;
	//! �X�R�A�ō��L�^�X�V
	static bool isHighestScoreUpdated;
};