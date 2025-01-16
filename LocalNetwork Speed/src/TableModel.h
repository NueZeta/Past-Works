/**
 * @file	TableModel.h
 * @brief	�e�[�u���I�u�W�F�N�g�̃p�����[�^�֌W
 * @author	NS
 * @date	2024/12/28
 */

#pragma once
#include "Define.h"

 /**
  * @union	TableModel
  * @brief  �e�[�u���I�u�W�F�N�g�̃��f���N���X
  */
class TableModel
{
	//
	// �����o�ϐ�
	//

public:

	//! �e�[�u���̃��f���n���h��
	int tableModelHandle;


	//
	// ���\�b�h
	//

public:

	/**
	 * @brief		�R���X�g���N�^
	 */
	TableModel();

	/**
	 * @brief		�����I�ɌĂяo���������֐�
	 */
	void Initialize();
};

