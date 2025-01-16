#pragma once
#include "Define.h"

/**
* @author   Suzuki N
* @date     24/10/04
* @note		銃弾を打つ方向を決める照準コンポーネントの定義ファイル
*/


/**
 * @class	GunSight
 * @brief   銃弾を打つ方向を決める照準コンポーネント
 */
class GunSight : public HWComponent
{
public:
	// メンバ変数

	//! hitしたときに与えるダメージ


public:
	// メソッド

	// デストラクタ
	~GunSight();


	/**
	 * @brief		オブジェクトにアタッチされたときに働くメソッド
	 * @author      Suzuki N
	 * @date        24/10/02
	 */
	void Awake()override;

	/**
	 * @brief		最初のUpdateメソッドの直前に働く
	 * @author      Suzuki N
	 * @date        24/10/04
	 */
	void Start()override;

	/**
	 * @brief		毎F呼ばれるメソッド
	 * @author      Suzuki N
	 * @date        24/10/02
	 */
	void Update()override;
};

