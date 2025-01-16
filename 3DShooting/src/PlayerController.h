#pragma once
#include "Define.h"
#include "Airframe.h"
#include "Bullet.h"
#include "GunSight.h"
#include "Score.h"

/**
* @author   Suzuki N
* @date     24/10/02
* @note		PlayerControllerコンポーネントの定義ファイル
*/


/**
 * @class	PlayerController
 * @brief   プレイヤーキャラクターのアニメーションなどを管理するコンポーネント
 */
class PlayerController : public HWComponent, public Airframe
{
	friend class Player;

private:
	// メンバ変数

	//! 機体操作用の入力
	std::shared_ptr<InputSystem> input;
	//! 当たり判定
	HWCapsuleCollider* capsuleCol;

	//! コリジョンの始点
	int collision_start;
	//! コリジョンの終点
	int collision_end;
	//! 銃口1
	int muzzle_1;
	//! 銃口2
	int muzzle_2;
	//! ブースター1
	int booster_1;
	//! ブースター2
	int booster_2;

	//! モデルハンドル
	int modelHandle;
	//! 弾丸のインスタンスのコンテナ
	std::vector<HWGameObject*> bulletVec;
	//! ガンサイトオブジェクト
	std::unique_ptr<HWGameObject> gunSightObj;
	//! ガンサイトコンポーネント
	GunSight* sightCp;
	//! 攻撃による撃破フラグ
	bool isCrushing;

	//! ブースターのエフェクト1
	std::unique_ptr<HWGameObject> boosterEf_1;
	//! ブースターのエフェクト2
	std::unique_ptr<HWGameObject> boosterEf_2;


public:
	// メソッド

	// コンストラクタ
	PlayerController(std::shared_ptr<InputSystem>);

	// デストラクタ
	~PlayerController();

	/**
	 * @brief		攻撃がHitした
	 * @author      Suzuki N
	 * @date        24/10/05
	 */
	void Damage(int _damage);

	/**
	 * @brief		攻撃がHitした
	 * @author      Suzuki N
	 * @date        24/10/05
	 */
	bool GetIsCrushing() const { return isCrushing; }


	/**
	 * @brief		オブジェクトにアタッチされたときに働くメソッド
	 * @author      Suzuki N
	 * @date        24/10/02
	 */
	void Awake()override;

	/**
	 * @brief		最初のUpdateメソッドの直前に働くメソッド
	 * @author      Suzuki N
	 * @date        24/10/02
	 */
	void Start()override;

	/**
	 * @brief		毎F呼ばれるメソッド
	 * @author      Suzuki N
	 * @date        24/10/02
	 */
	void Update()override;

private:

	/**
	 * @brief		移動メソッド
	 * @author      Suzuki N
	 * @date        24/10/02
	 */
	void Move(const VECTOR&);

	/**
	 * @brief		銃を撃つ
	 * @author      Suzuki N
	 * @date        24/10/04
	 */
	void Firing(const VECTOR& _pos);
};

