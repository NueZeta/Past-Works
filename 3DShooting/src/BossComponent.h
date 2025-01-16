#pragma once
#include "Define.h"
#include "Airframe.h"
#include "Bullet.h"
#include "Score.h"

/**
* @author   Suzuki N
* @date     24/10/09
* @note		Bossを操作するコンポーネントの定義ファイル
*/


/**
 * @class	BossMoveType
 * @brief   ボスの行動の種類
 */
enum class BossMoveType
{
	//! エントリー時(0)
	Entry,
	//! その場にとどまる(1)
	Wait,
	//! 移動(2)
	Move,
	//! 攻撃(3)
	Fire,
};



/**
 * @class	BossComponent
 * @brief   Bossを操作するコンポーネント
 */
class BossComponent : public HWComponent, Airframe
{
public:
	// メンバ変数

	//! Playerオブジェクト
	HWGameObject* player;
	//! モデルハンドル
	int modelHandle;
	//! 当たり判定のコンポーネント
	HWCapsuleCollider* capsuleCol;
	//! 攻撃による撃破フラグ
	bool isCrushing;
	//! 弾丸のインスタンスのコンテナ
	std::vector<HWGameObject*> bulletVec;

private:
	//! ターゲットの位置
	VECTOR targetPos;
	//! 現在とっている行動タイプ 
	BossMoveType moveType;
	//! 前回行動を取った時刻
	int moveTime;
	//! 移動メソッドによる移動方向
	int moveDirection;
	//! 前に射撃した時刻
	int shootingTime;


public:
	// メソッド

	// コンストラクタ
	BossComponent(HWGameObject* _player);

	// デストラクタ
	~BossComponent()override;


	// エントリー時の行動
	void Entry();
	// 待機
	void Wait();
	// 移動
	void Move();
	// 攻撃
	void Fire();
	// 行動タイプをランダムに決める
	void MoveTypeSelect();


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
	* 
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
};

