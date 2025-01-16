/**
 * @file	GameManager.h
 * @brief	�Q�[���S�̂̊Ǘ�
 * @author	NS
 * @date	2024/1/2
 */

#pragma once
#include "Define.h"


 /**
  * @class	GameManager
  * @brief  �Q�[���S�̂��Ǘ�����N���X
  */

class GameManager
{
	//
	// �����o�ϐ�
	//

public:

	//! �Q�[���p�����[�^
	static GameParameter param;
	//! �Q�[�������t���O
	static bool isWin;
	//! �Q�[���s�k�t���O
	static bool isLose;
	//! �v���C���[�^�C�v
	static PlayerType playerType;
	//! �ʐM�����IP�A�h���X
	static IPDATA ip;
	//! ����M�Ɏg���|�[�g�ԍ�
	static int port;
};