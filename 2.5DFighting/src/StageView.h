#pragma once
#include "GameManager.h"

/**
* @author   Suzuki N
* @date     24/11/05
* @note		StageViewの定義ファイル
*/


/**
 * @class	StageView
 * @brief   ステージオブジェクトのビューコンポーネント
 */
class StageView : public HWComponent
{
public:
	// メンバ変数

	//! モデルハンドル
	int modelHandle;
	//! レンダラー
	HWRenderer* renderer;


	// メソッド

	/**
	 * @brief		明示的に呼ぶ必要のある初期化メソッド
	 * @author      Suzuki N
	 * @date        24/11/05
	 */
	void Initialize();
};

