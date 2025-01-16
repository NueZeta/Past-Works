#include "Enemy.h"

/**
* @author   Suzuki N
* @date     24/10/03
* @note		Enemyの実装ファイル
*/


HWGameObject* Enemy::enemyOrigin = nullptr;


Enemy::Enemy(const EnemyType& _type)
{
	// オリジナルのモデルの情報をコピーコンストラクタで複製する
	enemy = new HWGameObject(*enemyOrigin);

	// 初期化処理
	enemy->active = true;
	controller = enemy->GetComponent<EnemyController>();

	// 当たり判定を付与
	capsuleCol = enemy->AddComponent<HWCapsuleCollider>();
	// 当たり判定の初期化
	capsuleCol->radius = ENEMY_COLLIDR_RADIUS;
	capsuleCol->isTrigger = true;
}

Enemy::~Enemy()
{
	delete enemy;
}
