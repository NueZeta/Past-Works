/**
 * @file	UdpConnection.h
 * @brief	UDP通信による通信関係
 * @author	NS
 * @date	2024/12/27
 */

#pragma once
#include "CardManager.h"


 /**
  * @struct	SendData
  * @brief  送受信するデータをパッケージングしたデータ群
  */
struct SendData
{
	//! 送信時の時刻
	int sendTime;
	//! 文字列
	std::string str;
	//! カード情報
	Card* cards;
};


 /**
  * @class	UdpConnection
  * @brief  UDP通信による送受信を行うクラス
  */
class UdpConnection
{
	//
	// メンバ変数
	//

public:

	//! 送信先のIPアドレス
	IPDATA ip;
	//! 送信専用のソケットハンドル
	int sendOnlyUdpHandle;
	//! 受信用のソケットハンドル
	int receptionUdpHandle;
	//! 受信に使うポート番号
	int port;
	//! データバッファ
	char strBuf[256];
	//! 受信時のコールバック関数
	std::function<void(SendData&)> receiveCallback;

	//
	// メソッド
	//

public:

	/**
	 * @brief		コンストラクタ
	 * @param[in]	IPDATA	送信先のIPアドレス
	 * @param[in]	int		受信に使うポート番号
	 */
	UdpConnection(IPDATA, int);

	/**
	 * @brief		デストラクタ
	 */
	~UdpConnection();

	/**
	 * @brief		データの受信があったかを監視する
	 */
	void RxSurveillance();

	/**
	 * @brief		受信時に呼ばれるコールバック関数を登録する
	 * @param[in]	コールバック関数
	 */
	void SubscribeReceiveCallback(std::function<void(SendData&)> _callback)
	{
		receiveCallback = _callback;
	}

	/**
	 * @brief		データを送信する
	 * @param[in]	SendData 送信するデータ
	 */
	void Send(SendData&);

private:

	/**
	 * @brief		データを受信した際に呼ばれるメソッド
	 * @param[in]	SendData 受信したデータ
	 */
	void Receive();
};

