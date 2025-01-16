#pragma once
#include "Define.h"
#include "PlayerController.h"
#include "EnemyController.h"
#include "BossComponent.h"

/**
* @author   Suzuki N
* @date     24/10/04
* @note		攻撃時に発射される銃弾コンポーネントの定義ファイル
*/


/**
 * @class	Bullet
 * @brief   攻撃時に発射される銃弾コンポーネント
 */
class Bullet : public HWComponent
{
	friend class SceneGame;
	friend class PlayerController;
	friend class EnemyController;
	friend class BossComponent;

public:
	// メンバ変数

	//! hitしたときに与えるダメージ
	int damage;
	//! Hitを無視してほしいオブジェクトのタグ
	Tag ignoreTag;
	//! 弾の発射角
	VECTOR FiringDirection;
	//! インスタンスが生成された時間
	int startTyme;
	//! Hitフラグ
	bool isHit;
	// エフェクト再生
	std::unique_ptr<HWGameObject> bulletEf;


private:

	// オリジナルのモデルの情報をコピーコンストラクタで複製する
	static HWGameObject* bulletOrigin;


public:
	// メソッド

	// コンストラクタ
	Bullet(const int _damage, const VECTOR& _dir);

	// デストラクタ
	~Bullet();


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
};

