/**
 * @file	GameManager.h
 * @brief	ゲーム全体の管理
 * @author	NS
 * @date	2024/1/2
 */

#pragma once
#include "Define.h"


 /**
  * @class	GameManager
  * @brief  ゲーム全体を管理するクラス
  */

class GameManager
{
	//
	// メンバ変数
	//

public:

	//! ゲームパラメータ
	static GameParameter param;
	//! ゲーム勝利フラグ
	static bool isWin;
	//! ゲーム敗北フラグ
	static bool isLose;
	//! プレイヤータイプ
	static PlayerType playerType;
	//! 通信相手のIPアドレス
	static IPDATA ip;
	//! 送受信に使うポート番号
	static int port;
};