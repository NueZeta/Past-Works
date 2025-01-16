#pragma once
#include "GameManager.h"
#include "VampirePresenter.h"

/**
* @author   Suzuki N
* @date     24/11/05
* @note		StageModelの定義ファイル
*/

class VampirePresenter;

/**
 * @class	StageModel
 * @brief   ステージオブジェクトのモデル
 */
class StageModel
{
public:
	// メンバ変数

	//! Player1のプレゼンターコンポーネント
	VampirePresenter* player1_presenter;
	//! Player2のプレゼンターコンポーネント
	VampirePresenter* player2_presenter;
	//! カメラの注視点
	VECTOR viewPoint;

	//! 左画面端
	static float leftCorner;
	//! 右画面端
	static float rightCorner;
};

