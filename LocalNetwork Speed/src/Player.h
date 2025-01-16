/**
 * @file	Player.h
 * @brief	プレイヤーの入力等の管理
 * @author	NS
 * @date	2024/1/2
 */

#pragma once
#include "UdpConnection.h"


 /**
  * @class	Player
  * @brief  プレイヤーのインプットを管理するクラス
  */
class Player : public HWComponent
{
	//
	// メンバ変数
	//

public:

	//! UDPの送受信
	std::unique_ptr<UdpConnection> udpConnection;
	//! 入力系
	std::unique_ptr<InputSystem> input;

	//
	// メソッド
	//

public:

	/**
	 * @brief		コンストラクタ
	 */
	Player();

	/**
	 * @brief		デストラクタ
	 */
	~Player();

	/**
	 * @brief		決定キー入力時のコールバック
	 * @param[out]	キー入力情報
	 */
	void SelectInputCallback(InputAction::CallBackContext);

	/**
	 * @brief		移動キー入力時のコールバック
	 * @param[out]	キー入力情報
	 */
	void MoveInputCallback(InputAction::CallBackContext);

	/**
	 * @brief		データ受信時のコールバック
	 * @param[out]	受信データ
	 */
	void ReceiveCallback(SendData&);

	/**
	 * @brief		初期化関数
	 */
	void Awake()override;

	/**
	 * @brief		更新処理
	 */
	void Update()override;
};

