#pragma once
#include "GameManager.h"
#include "VampireModel.h"

/**
* @author   Suzuki N
* @date     24/11/05
* @note		ProjectileModelの定義ファイル
*/


/**
 * @class	ProjectileModel
 * @brief   飛び道具の攻撃判定のモデルクラス
 */
class ProjectileModel
{
public:
	//  メンバ変数

	//! 付与されている属性
	AttackAttribute attribute;
	//! 攻撃判定
	HWCapsuleCollider* attackCol;
	//! エフェクトのpath
	std::string effectPath;
	//! エフェクトコンポーネント
	HWEffect* effectCp;
	//! 攻撃判定の半径
	float attackColRadius;
	//! Hit時のダメージ
	int damage;
	//! Hit硬直
	int hitStun;
	//! Guard硬直
	int guardStun;
	//! モデル
	VampireModel* vampireModel;
	//! ? 右にとぶ(true) : 左にとぶ(false)
	bool flyingDirection;
	//! 移動スピード
	float speed;
	//! 生成時刻
	int generateTime;


public:
	// メンバ関数

	// コンストラクタ
	ProjectileModel();
};

