/**
 * @file	Player.h
 * @brief	�v���C���[�̓��͓��̊Ǘ�
 * @author	NS
 * @date	2024/1/2
 */

#pragma once
#include "UdpConnection.h"


 /**
  * @class	Player
  * @brief  �v���C���[�̃C���v�b�g���Ǘ�����N���X
  */
class Player : public HWComponent
{
	//
	// �����o�ϐ�
	//

public:

	//! UDP�̑���M
	std::unique_ptr<UdpConnection> udpConnection;
	//! ���͌n
	std::unique_ptr<InputSystem> input;

	//
	// ���\�b�h
	//

public:

	/**
	 * @brief		�R���X�g���N�^
	 */
	Player();

	/**
	 * @brief		�f�X�g���N�^
	 */
	~Player();

	/**
	 * @brief		����L�[���͎��̃R�[���o�b�N
	 * @param[out]	�L�[���͏��
	 */
	void SelectInputCallback(InputAction::CallBackContext);

	/**
	 * @brief		�ړ��L�[���͎��̃R�[���o�b�N
	 * @param[out]	�L�[���͏��
	 */
	void MoveInputCallback(InputAction::CallBackContext);

	/**
	 * @brief		�f�[�^��M���̃R�[���o�b�N
	 * @param[out]	��M�f�[�^
	 */
	void ReceiveCallback(SendData&);

	/**
	 * @brief		�������֐�
	 */
	void Awake()override;

	/**
	 * @brief		�X�V����
	 */
	void Update()override;
};

