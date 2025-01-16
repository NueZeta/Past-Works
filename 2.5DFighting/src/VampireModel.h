#pragma once
#include "GameManager.h"


/**
* @author   Suzuki N
* @date     24/10/29
* @note		VampireModelの定義ファイル
*/


class AttackPresenter;
class ProjectilePresenter;


/**
 * @class	VampireModel
 * @brief   キャラクター1のモデルクラス
 */
class VampireModel
{
public:
	//  メンバ変数

	//! プレイヤーID
	int playerId;
	//! キャラクターのパラメータ
	Parameter param;
	//! 現在のFが入力1F目のコマンド
	Parameter crrInputParam;
	//! 最大HP
	int maxHp;
	//! 現在HP
	int hp;
	//! ジャンプ力
	float jumpPower;
	//! 上半身の当たり判定
	HWCapsuleCollider* upCollider;
	//! 上半身の当たり判定の始点
	int upColStartPos;
	//! 上半身の当たり判定の終点
	int upColendPos;
	//! 上半身の当たり判定の半径
	float upColRadius;
	//! 下半身の当たり判定
	HWCapsuleCollider* lowCollider;
	//! 下半身のコライダーの中心
	int lowCenterFrame;
	//! 下半身の当たり判定の半径
	float lowColRadius;
	//! 入力系
	std::unique_ptr<InputSystem> input;
	//! 過去30F分の入力記録
	std::vector<InputKey> keyHistory;

	//! StLaの攻撃判定
	std::unique_ptr<HWGameObject> stLaAttack;
	AttackPresenter* stLaAttackPresenter;
	//! StHaの攻撃判定
	std::unique_ptr<HWGameObject> stHaAttack;
	AttackPresenter* stHaAttackPresenter;
	//! CtLaの攻撃判定
	std::unique_ptr<HWGameObject> crLaAttack;
	AttackPresenter* crLaAttackPresenter;
	//! CtHaの攻撃判定
	std::unique_ptr<HWGameObject> crHaAttack;
	AttackPresenter* crHaAttackPresenter;


	//! 飛び道具のエフェクトハンドル
	static int projectileEffectHandle;
	//! 飛び道具
	HWGameObject* projectile = nullptr;
	ProjectilePresenter* projectileCp;

	//! Sp2の攻撃判定
	std::unique_ptr<HWGameObject> sp2Attack;
	AttackPresenter* sp2AttackPresenter;
 

public:
	// メンバ関数

	// コンストラクタ
	VampireModel();


	/**
	 * @brief		明示的に呼ぶ必要のある更新メソッド
	 * @author      Suzuki N
	 * @date        24/10/29
	 */
	void ExplicitUpdate();
};

