#pragma once
#include "GameManager.h"

/**
* @author   Suzuki N
* @date     24/11/05
* @note		ProjectileViewの定義ファイル
*/


/**
 * @class	AttackView
 * @brief   飛び道具の攻撃判定のビューコンポーネント
 */
class ProjectileView : public HWComponent
{
public:
	// メンバ変数



	// メンバ関数

	/**
	 * @brief		明示的に呼ぶ必要のある初期化メソッド
	 * @author      Suzuki N
	 * @date        24/11/05
	 */
	void Initialize();
};

