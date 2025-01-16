#pragma once
#include "Define.h"
#include "Player.h"
#include "Enemy.h"


/**
* @author   Suzuki N
* @date     24/10/03
* @note		Enemyを管理するクラスの定義ファイル
*/


/**
 * @class	EnemyManager
 * @brief   Enemyの管理、リポップなどを行うクラス
 */
class EnemyManager : public HWComponent
{
public:
	// メンバ変数

	//! インスタンス化したEnemyのコンテナ
	std::vector<Enemy*> enemyVec;
	//! Playerのオブジェクト
	Player* player;
	//! Enemyのメモリアロケーター
	PoolAllocator<Enemy, ENEMY_MAX_NUM> allocator;
	//! Bossが出現しているか
	bool isBossEntry;
	//! Bossが出現した時間
	int bossEntryTime;
	//! BossのGameObject
	HWGameObject* boss;
	//! Bossのコンポーネント
	BossComponent* bossCp;


private:
	//! 前回Enemyを生成した時刻
	int generatedTime;
	//! 開始時間
	int startTime;


public:
	// メソッド

	// コンストラクタ
	EnemyManager(Player* _player);

	// デストラクタ
	~EnemyManager();

	/**
	 * @brief		敵オブジェクトをポップさせる
	 * @author      Suzuki N
	 * @date        24/10/03
	 */
	void EnemyPop();

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

