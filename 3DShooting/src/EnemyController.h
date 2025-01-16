#pragma once
#include "Define.h"
#include "Airframe.h"
#include "Bullet.h"
#include "GunSight.h"
#include "Score.h"
#include "BossComponent.h"

/**
* @author   Suzuki N
* @date     24/10/03
* @note		Enemyを操作するコンポーネントの定義ファイル
*/


/**
 * @enum	EnemyType
 * @brief   Enemyの行動パターン
 */
enum class EnemyType
{
	//! まっすぐ進む(0)
	straight,
	//! Playerに向かってくる(1)
	Chase,
};


/**
 * @class	EnemyController
 * @brief   Enemyを操作するコンポーネント
 */
class EnemyController : public HWComponent, Airframe
{
public:
	// メンバ変数

	//! Playerオブジェクト
	HWGameObject* player;
	//! モデルハンドル
	int modelHandle;
	//! 当たり判定のコンポーネント
	HWCapsuleCollider* capsuleCol;
	//! マップ移動による消滅フラグ
	bool isErase;
	//! 攻撃による撃破フラグ
	bool isCrushing;
	//! 行動タイプ
	EnemyType type;
	//! 弾丸のインスタンスのコンテナ
	std::vector<HWGameObject*> bulletVec;
	//! 前に射撃した時刻
	int shootingTime;


	// ターゲットの位置
	VECTOR targetPos;

public:
	// メソッド

	// コンストラクタ
	EnemyController(const EnemyType& _type);

	// デストラクタ
	~EnemyController()override;


	/**
	 * @brief		攻撃がHitした
	 * @author      Suzuki N
	 * @date        24/10/05
	 */
	void Damage(int _damage);

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

	/**
	 * @brief		コライダーHit時に呼ばれるメソッド
	 * @param[out]	Hitしたコライダー
	 * @author      Suzuki N
	 * @date        24/10/02
	 */
	void OnTriggerEnter(HWCollider& other)override;

private:

	/**
	 * @brief		追うタイプの敵の行動ルーチン
	 * @author      Suzuki N
	 * @date        24/10/05
	 */
	void Chase();

	/**
	 * @brief		直進するタイプの敵の行動ルーチン
	 * @author      Suzuki N
	 * @date        24/10/05
	 */
	void Straight();

	/**
	 * @brief		銃を撃つ
	 * @author      Suzuki N
	 * @date        24/10/05
	 */
	void Firing(const VECTOR& _pos);

};

