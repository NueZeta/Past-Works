/**
 * @file	TableModel.h
 * @brief	テーブルオブジェクトのパラメータ関係
 * @author	NS
 * @date	2024/12/28
 */

#pragma once
#include "Define.h"

 /**
  * @union	TableModel
  * @brief  テーブルオブジェクトのモデルクラス
  */
class TableModel
{
	//
	// メンバ変数
	//

public:

	//! テーブルのモデルハンドル
	int tableModelHandle;


	//
	// メソッド
	//

public:

	/**
	 * @brief		コンストラクタ
	 */
	TableModel();

	/**
	 * @brief		明示的に呼び出す初期化関数
	 */
	void Initialize();
};

