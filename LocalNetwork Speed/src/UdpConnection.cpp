/**
 * @file	UdpConnection.cpp
 * @brief	UDP�ʐM�ɂ��ʐM�֌W
 * @author	NS
 * @date	2024/12/27
 */

#include "UdpConnection.h"


UdpConnection::UdpConnection(IPDATA _ip, int _recvPort)
	: ip(_ip), port(_recvPort), receptionUdpHandle(MakeUDPSocket(_recvPort)), sendOnlyUdpHandle(MakeUDPSocket(-1))
{
}

UdpConnection::~UdpConnection()
{
	DeleteUDPSocket(receptionUdpHandle);
	DeleteUDPSocket(sendOnlyUdpHandle);
}

void UdpConnection::RxSurveillance()
{
	if(CheckNetWorkRecvUDP(receptionUdpHandle) == TRUE)
	{
		//
		// ��M�f�[�^��������
		//

		Receive();
	}
}

void UdpConnection::Send(SendData& _sendData)
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

	std::memcpy(b, &_sendData.sendTime, sizeof(int));

	b += sizeof(int);

	std::memcpy(b, data, sizeof(data));


	// �f�[�^�𑗐M����
	int ret = NetWorkSendUDP(sendOnlyUdpHandle, ip, port, block, 250);

	//
	// �G���[�`�F�b�N
	//
	switch (ret)
	{
	case -1:
		throw std::runtime_error("�G���[����");
		break;

	case -2:
		throw std::runtime_error("���M�f�[�^���傫������");
		break;

	case -3:
		throw std::runtime_error("���M�������������Ă��Ȃ�");
		break;
	}
}

void UdpConnection::Receive()
{
	//! ��M�f�[�^�̃A�E�g�v�b�g��
	SendData data;

	//! ��M�f�[�^
	unsigned char block[250];

	// ��M�f�[�^���󂯎��
	int ret = NetWorkRecvUDP(receptionUdpHandle, NULL, NULL, block, 250, FALSE);

	// ���M��������������
	data.sendTime = *(int*)block;

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

	// �f�R�[�h�����f�[�^���L�^
	data.cards = decodeData;

	//
	// �G���[�`�F�b�N
	//
	switch (ret)
	{
	case -1:
		throw std::runtime_error("�G���[����");
		break;

	case -2:
		throw std::runtime_error("��M�f�[�^���o�b�t�@�̃T�C�Y�̕���������");
		break;

	case -3:
		return;
		break;
	}

	// �o�^���ꂽ�R�[���o�b�N���Ăяo��
	if(receiveCallback)
		receiveCallback(data);
}
