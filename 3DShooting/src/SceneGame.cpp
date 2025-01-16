#include "SceneGame.h"

/**
* @author   Suzuki N
* @date     24/10/01
* @note		SceneGameの実装ファイル
*/


void SceneGame::Init()
{
	// 複製もとになるGameObjectのオリジナルを作成する --------------------------------------------

	//! Enemyオブジェクトのオリジナル(複製元)を作成する
	Enemy::enemyOrigin = new HWGameObject("Enemy_Type.1(origin)");
	// 初期座標をずらさないとなぜかHitする
	Enemy::enemyOrigin->transform->position = VGet(-10000, -10000, -10000);
	Enemy::enemyOrigin->active = false;
	Enemy::enemyOrigin->tag = (int)Tag::Enemy;
	// 必要なコンポーネントをアタッチする
	Enemy::enemyOrigin->AddComponent<HWRenderer>("Assets/Enemy/No.1/Ene_No1_mesh.mv1");
	// 非アクティブに設定

	//! Bulletオブジェクトのオリジナル(複製元)を作成する
	Bullet::bulletOrigin = new HWGameObject("Bullet_origin");
	// 初期座標をずらさないとなぜかHitする
	Bullet::bulletOrigin->transform->position = VGet(-10000, -10000, -10000);
	Bullet::bulletOrigin->active = false;
	Bullet::bulletOrigin->tag = (int)Tag::Bullet;
	Bullet::bulletOrigin->AddComponent<HWRenderer>("Assets/Bullet/Bullet.mv1");
	Bullet::bulletOrigin->transform->scale = BULLET_DEFAULT_SCALE;
	Bullet::bulletOrigin->transform->rotate = BULLET_DEFAULT_ROTATE;

	// -------------------------------------------------------------------------------------------
}

SceneGame::SceneGame(InputSystem* _Input) : crashTime(0), clearTime(0)
{
	// 実行中のシーンタグ
	sceneTag = SceneTag::Game; 

	// ロードに時間がかかるため、最初はEnemyを生成しないようにする
	GameManager::isStop = true;

	// 各オブジェクトの初期化
	player = std::make_unique<Player>();
	enemyManager = std::make_unique<HWGameObject>();
	eneManagerCp = enemyManager->AddComponent<EnemyManager>(player.get());

	// Stage
	{
		stage = std::make_unique<HWGameObject>("stage");
		stage->AddComponent<Stage>(player.get());
	}

	// SceneManagerのシステム系InputSystemを受け取る
	sysInput = _Input;
	// シーン遷移用コールバック関数を登録
	// R キーでシーン遷移
	{
		sysInput->AddKeyCode("sceneChange", KEY_INPUT_R);
		callBackId = sysInput->AddCallBack("sceneChange", [&](InputAction::CallBackContext context)
			{
				if (context.state == InputState::Started)
					SceneChange(SceneTag::Result);
			});
	}

	GameManager::isStop = false;
}

SceneGame::~SceneGame()
{
	sysInput->DeleteCallBack("sceneChange", callBackId);
}

void SceneGame::Update()
{
	// 自機が倒された
	if (player->controller->GetIsCrushing())
	{
		// 倒された時間を記録
		if (crashTime == 0)
			crashTime = GetNowCount();

		// 演出として、破壊されたら一定時間スピードを緩める
		if(GetNowCount() - crashTime > PLAYER_CRASH_TIME)
		{
			Time::SetTargetFPS(60);
			SceneChange(SceneTag::Result);
			GameManager::isStop = true;
		}
	}
	// クリアフラグ
	else if(GameManager::isClear)
	{
		// クリアした時間を記録
		if (clearTime == 0)
			clearTime = GetNowCount();

		// 演出として、クリアしたら一定時間スピードを緩める
		if (GetNowCount() - clearTime > BOSS_CRASH_TIME)
		{
			Time::SetTargetFPS(60);
			SceneChange(SceneTag::Result);
			GameManager::isStop = true;
			// スコア加算
			if (player->controller->GetHp() == player->controller->GetMaxHp())
			{
				// ノーダメージボーナス
				Score::score += NO_DAMAGE_SCORE;
				GameManager::isNoDamage = true;
			}
			if (player->controller->GetHp() <= player->controller->GetMaxHp() / 20)
			{
				// ぎりぎりクリアボーナス
				Score::score += MORTAL_COMBAT_SCORE;
				GameManager::isMortalCombat = true;
			}
		}
	}

	// スコアを表示
	DrawFormatString(GameManager::ScreenSizeX / 2 - 20, 20, GetColor(255, 0, 255), "%d", Score::score);
}
