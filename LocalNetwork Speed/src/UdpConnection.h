/**
 * @file	UdpConnection.h
 * @brief	UDP�ʐM�ɂ��ʐM�֌W
 * @author	NS
 * @date	2024/12/27
 */

#pragma once
#include "CardManager.h"


 /**
  * @struct	SendData
  * @brief  ����M����f�[�^���p�b�P�[�W���O�����f�[�^�Q
  */
struct SendData
{
	//! ���M���̎���
	int sendTime;
	//! ������
	std::string str;
	//! �J�[�h���
	Card* cards;
};


 /**
  * @class	UdpConnection
  * @brief  UDP�ʐM�ɂ�鑗��M���s���N���X
  */
class UdpConnection
{
	//
	// �����o�ϐ�
	//

public:

	//! ���M���IP�A�h���X
	IPDATA ip;
	//! ���M��p�̃\�P�b�g�n���h��
	int sendOnlyUdpHandle;
	//! ��M�p�̃\�P�b�g�n���h��
	int receptionUdpHandle;
	//! ��M�Ɏg���|�[�g�ԍ�
	int port;
	//! �f�[�^�o�b�t�@
	char strBuf[256];
	//! ��M���̃R�[���o�b�N�֐�
	std::function<void(SendData&)> receiveCallback;

	//
	// ���\�b�h
	//

public:

	/**
	 * @brief		�R���X�g���N�^
	 * @param[in]	IPDATA	���M���IP�A�h���X
	 * @param[in]	int		��M�Ɏg���|�[�g�ԍ�
	 */
	UdpConnection(IPDATA, int);

	/**
	 * @brief		�f�X�g���N�^
	 */
	~UdpConnection();

	/**
	 * @brief		�f�[�^�̎�M�������������Ď�����
	 */
	void RxSurveillance();

	/**
	 * @brief		��M���ɌĂ΂��R�[���o�b�N�֐���o�^����
	 * @param[in]	�R�[���o�b�N�֐�
	 */
	void SubscribeReceiveCallback(std::function<void(SendData&)> _callback)
	{
		receiveCallback = _callback;
	}

	/**
	 * @brief		�f�[�^�𑗐M����
	 * @param[in]	SendData ���M����f�[�^
	 */
	void Send(SendData&);

private:

	/**
	 * @brief		�f�[�^����M�����ۂɌĂ΂�郁�\�b�h
	 * @param[in]	SendData ��M�����f�[�^
	 */
	void Receive();
};

