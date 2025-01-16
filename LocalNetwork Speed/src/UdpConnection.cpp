/**
 * @file	UdpConnection.cpp
 * @brief	UDP通信による通信関係
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
		// 受信データがあった
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


	// データを送信する
	int ret = NetWorkSendUDP(sendOnlyUdpHandle, ip, port, block, 250);

	//
	// エラーチェック
	//
	switch (ret)
	{
	case -1:
		throw std::runtime_error("エラー発生");
		break;

	case -2:
		throw std::runtime_error("送信データが大きすぎる");
		break;

	case -3:
		throw std::runtime_error("送信準備が完了していない");
		break;
	}
}

void UdpConnection::Receive()
{
	//! 受信データのアウトプット先
	SendData data;

	//! 受信データ
	unsigned char block[250];

	// 受信データを受け取る
	int ret = NetWorkRecvUDP(receptionUdpHandle, NULL, NULL, block, 250, FALSE);

	// 送信時刻を書き込み
	data.sendTime = *(int*)block;

	//! 受け取ったカードデータ
	CardData* cdp = (CardData*)(block + sizeof(int));

	//! 受け取ったカードデータのデコード先
	Card decodeData[CardTotalNumber];

	// カードデータをデコードする
	for (int i = 0; i < CardTotalNumber; ++i)
	{
		decodeData[i].suit = (Suit)(cdp[i].data / 13);
		decodeData[i].number = cdp[i].data % 13 + 1;
		decodeData[i].area = static_cast<Area>(cdp[i].area);
		decodeData[i].areaNumber = cdp[i].areaNumber;	
	}

	// デコードしたデータを記録
	data.cards = decodeData;

	//
	// エラーチェック
	//
	switch (ret)
	{
	case -1:
		throw std::runtime_error("エラー発生");
		break;

	case -2:
		throw std::runtime_error("受信データよりバッファのサイズの方が小さい");
		break;

	case -3:
		return;
		break;
	}

	// 登録されたコールバックを呼び出す
	if(receiveCallback)
		receiveCallback(data);
}
