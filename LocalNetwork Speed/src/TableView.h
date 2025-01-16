/**
 * @file	TableView.h
 * @brief	�e�[�u���I�u�W�F�N�g�̃O���t�B�b�N�֌W
 * @author	NS
 * @date	2024/12/28
 */

#pragma once
#include "Define.h"

 /**
  * @class	TableView
  * @brief  �e�[�u���I�u�W�F�N�g�̃r���[�R���|�[�l���g
  */
class TableView : public HWComponent
{
	//
	// �����o�ϐ�
	//

public:

	//! �e�[�u���̃��f���n���h��
	int tableModelHandle;
	//! �����_���[
	HWRenderer* renderer;


	//
	// ���\�b�h
	//

public:

	/**
	 * @brief		�R���X�g���N�^
	 */
	TableView();

	/**
	 * @brief		�����I�ɌĂяo���������֐�
	 * @param[in]	�J�[�h�̃��f���n���h��
	 * @param[in]	�e�[�u���̃��f���n���h��
	 */
	void Initialize(int);

	/**
	 * @brief		�X�V����
	 */
	void Update()override;
};

