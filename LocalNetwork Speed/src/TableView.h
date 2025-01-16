/**
 * @file	TableView.h
 * @brief	テーブルオブジェクトのグラフィック関係
 * @author	NS
 * @date	2024/12/28
 */

#pragma once
#include "Define.h"

 /**
  * @class	TableView
  * @brief  テーブルオブジェクトのビューコンポーネント
  */
class TableView : public HWComponent
{
	//
	// メンバ変数
	//

public:

	//! テーブルのモデルハンドル
	int tableModelHandle;
	//! レンダラー
	HWRenderer* renderer;


	//
	// メソッド
	//

public:

	/**
	 * @brief		コンストラクタ
	 */
	TableView();

	/**
	 * @brief		明示的に呼び出す初期化関数
	 * @param[in]	カードのモデルハンドル
	 * @param[in]	テーブルのモデルハンドル
	 */
	void Initialize(int);

	/**
	 * @brief		更新処理
	 */
	void Update()override;
};

