#pragma once
#include "Define.h"

/**
* @author   Suzuki N
* @date     24/10/02
* @note		すべての機体の基底クラスとなるAirframeクラスの定義ファイル
*/


/**
 * @class	Airframe
 * @brief   機体に必要な値を持つ基底クラス
 */
class Airframe
{
public:
	// メンバ変数

	//! 最大HP
	int maxHp;
	//! HP
	int hp;
	//! 攻撃力(1HIT当たり)
	int attackPower;
	//! 上下の移動速度
	float verticalSpeed;
	//! 左右の移動速度
	float horizonSpeed;
	//! 撃墜フラグ
	bool isShootingDown;


protected:
	// メソッド

	// コンストラクタ
	// 基底クラスのため、インスタンスを作成できないようにする
	Airframe() : maxHp(-1), hp(-1), attackPower(-1), verticalSpeed(0.0f),
		horizonSpeed(0.0f), isShootingDown(false)
	{}

public:

	// HPを取得する
	inline int GetHp()const { return hp; }
	// 最大HPを取得する
	inline int GetMaxHp()const { return maxHp; }

	// デストラクタ
	// 仮想関数
	virtual ~Airframe(){}
};