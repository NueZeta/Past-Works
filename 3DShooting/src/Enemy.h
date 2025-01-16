#pragma once
#include "Define.h"
#include "EnemyController.h"

/**
* @author   Suzuki N
* @date     24/10/03
* @note		Enemyクラスの定義ファイル
*/


/**
 * @class	Enemy
 * @brief   Enemyの機体クラス
 */
class Enemy
{
	friend class EnemyManager;
	friend class SceneGame;

public:
	// メンバ変数

	//! EnemyのGameObject
	HWGameObject* enemy;
	//! エネミーコントローラ
	EnemyController* controller;
	//! カプセル型の当たり判定
	HWCapsuleCollider* capsuleCol;

private:

	//! 敵オブジェクトのコピー元
	static HWGameObject* enemyOrigin;
	//! 行動タイプ
	EnemyType type;


public:
	// メソッド

	// コンストラクタ
	Enemy(const EnemyType& _type);

	// デストラクタ
	~Enemy();
};

