#pragma once
#include "GameManager.h"

/**
* @author   Suzuki N
* @date     24/10/29
* @note		VampireViewの定義ファイル
*/


/**
 * @class	VampireView
 * @brief   キャラクター1のビューコンポーネント
 */
class VampireView : public HWComponent
{
public:
	//  メンバ変数

	//! モデルハンドル
	int modelHandle;
	//! アニメーション制御コンポーネント
	HWAnimator* animator;
	//! デフォルトのアニメーションブレンドスピード
	float defaultBlendSpeed = 0.3f;

	//! 立ち強攻撃の発生時に呼ばれるメソッド
	std::function<void()> stHaOccursCallback;
	//! 立ち強攻撃の発生終了時に呼ばれるメソッド
	std::function<void()> stHaFinishedCallback;
	//! 立ち弱攻撃の発生時に呼ばれるメソッド
	std::function<void()> stLaOccursCallback;
	//! 立ち弱攻撃の発生終了時に呼ばれるメソッド
	std::function<void()> stLaFinishedCallback;
	//! 屈強攻撃の発生時に呼ばれるメソッド
	std::function<void()> crHaOccursCallback;
	//! 屈強攻撃の発生終了時に呼ばれるメソッド
	std::function<void()> crHaFinishedCallback;
	//! 屈弱攻撃の発生時に呼ばれるメソッド
	std::function<void()> crLaOccursCallback;
	//! 屈弱攻撃の発生終了時に呼ばれるメソッド
	std::function<void()> crLaFinishedCallback;

	//! 波動拳の発生時に呼ばれるメソッド
	std::function<void()> sp1OccursCallback;
	//! 昇竜拳の発生時に呼ばれるメソッド
	std::function<void()> sp2OccursCallback;
	//! 昇竜拳の発生終了時に呼ばれるメソッド
	std::function<void()> sp2FinishedCallback;

	//! 攻撃アニメーション終了時に呼ばれるコールバック
	std::function<void()> attackEndCallBack;
	//! ガードアニメーション終了時に呼ばれるコールバック
	std::function<void()> guardEndCallBack;
	//! ヒットアニメーション終了時に呼ばれるコールバック
	std::function<void()> hitEndCallBack;
	//! 着地時に呼ばれるコールバック
	std::function<void()> landingCallBack;


public:
	// メンバ関数

	/**
	 * @brief		明示的に呼ぶ必要のある初期化メソッド
	 * @author      Suzuki N
	 * @date        24/10/29
	 */
	void Initialize();
};

