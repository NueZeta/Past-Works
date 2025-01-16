#pragma once
#include "GameManager.h"
#include "VampireModel.h"

/**
* @author   Suzuki N
* @date     24/10/31
* @note		AttackModelの定義ファイル
*/


/**
 * @class	AttackModel
 * @brief   攻撃判定のモデルクラス
 */
class AttackModel
{
public:
	//  メンバ変数

	//! 付与されている属性
	AttackAttribute attribute;
	//! 攻撃判定
	HWCapsuleCollider* attackCol;
	//! 右向きの場合の攻撃判定の中心座標のフレーム
	int attackColCenterFrame_right;
	//! 左向きの場合の攻撃判定の中心座標のフレーム
	int attackColCenterFrame_left;
	//! 攻撃判定の半径
	float attackColRadius;
	//! Hit時のダメージ
	int damage;
	//! Hit硬直
	int hitStun;
	//! Guard硬直
	int guardStun;
	//! モデルハンドル
	int modelHandle;
	//! モデル
	VampireModel* vampireModel;


public:
	// メンバ関数

	// コンストラクタ
	AttackModel();	
};

