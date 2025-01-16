/**
 * @file	TablePresenter.h
 * @brief	�e�[�u���I�u�W�F�N�g���Ǘ�
 * @author	NS
 * @date	2024/12/28
 */

#pragma once
#include "TableModel.h"
#include "TableView.h"
#include "UdpConnection.h"

 /**
  * @union	TablePresenter
  * @brief  �e�[�u���I�u�W�F�N�g�̃v���[���^�[�N���X
  */
class TablePresenter : public HWComponent
{
	//
	// �����o�ϐ�
	//

public:

	//! ���f��
	std::unique_ptr<TableModel> model;
	//! �r���[
	TableView* view;


	//
	// ���\�b�h
	//

public:

	/**
	 * @brief		�R���X�g���N�^
	 */
	TablePresenter();

	/**
	 * @brief		�������֐�
	 */
	void Awake()override;

	/**
	 * @brief		�X�V����
	 */
	void Update()override;
};

