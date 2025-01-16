#pragma once
#include "SceneBase.h"
#include "Player.h"
#include "EnemyManager.h"
#include "Stage.h"

/**
* @author   Suzuki N
* @date     24/10/01
* @note		SceneGameの定義ファイル
*/


/**
 * @class	SceneGame
 * @brief   メインゲームシーン
 */
class SceneGame : public SceneBase 
{
private:
	//メンバ変数

	//! プレイヤーオブジェクト
	std::unique_ptr<Player> player;
	//! エネミー管理用のオブジェクト
	std::unique_ptr<HWGameObject> enemyManager;
	//! エネミー管理用のコンポーネント
	EnemyManager* eneManagerCp;
	//! ステージオブジェクト
	std::unique_ptr<HWGameObject> stage;

	//! Player機が破壊された時間
	int crashTime;
	//! クリアしたときの時間
	int clearTime;


public:
	// メソッド

	static void Init();

	// コンストラクタ
	SceneGame(InputSystem* _Input);

	// デストラクタ
	~SceneGame() override;

	// 毎F呼ばれる関数
	// オーバライドメソッド
	void Update() override;
};

