/**
 * @file	TablePresenter.h
 * @brief	テーブルオブジェクトを管理
 * @author	NS
 * @date	2024/12/28
 */

#pragma once
#include "TableModel.h"
#include "TableView.h"
#include "UdpConnection.h"

 /**
  * @union	TablePresenter
  * @brief  テーブルオブジェクトのプレゼンタークラス
  */
class TablePresenter : public HWComponent
{
	//
	// メンバ変数
	//

public:

	//! モデル
	std::unique_ptr<TableModel> model;
	//! ビュー
	TableView* view;


	//
	// メソッド
	//

public:

	/**
	 * @brief		コンストラクタ
	 */
	TablePresenter();

	/**
	 * @brief		初期化関数
	 */
	void Awake()override;

	/**
	 * @brief		更新処理
	 */
	void Update()override;
};

