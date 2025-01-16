#include "EnemyManager.h"

/**
* @author   Suzuki N
* @date     24/10/03
* @note		EnemyManagerの実装ファイル
*/



int Score::score = 0;
int GameManager::ScreenSizeX = 0;
int GameManager::ScreenSizeY = 0;
bool GameManager::isClear = false;
bool GameManager::isStop = false;
bool GameManager::isNoDamage = false;
bool GameManager::isMortalCombat = false;
bool GameManager::isHighestScoreUpdated = false;


EnemyManager::EnemyManager(Player* _player) : startTime(GetNowCount()), 
	player(_player), isBossEntry(false), boss(nullptr), bossEntryTime(0)
{
	generatedTime = GetNowCount();
	Score::score = 0;
	GameManager::isClear = false;
	GameManager::isStop = false;
	GameManager::isNoDamage = false;
	GameManager::isMortalCombat = false;
	GameManager::isHighestScoreUpdated = false;
}

EnemyManager::~EnemyManager()
{
	for (auto it = enemyVec.begin(); it != enemyVec.end(); ++it)
		allocator.Free(*it);

	if (boss != nullptr)
		delete boss;
}

void EnemyManager::EnemyPop()
{
	// マップ上のEnemyの総数が既定の値を超える場合はそのまま終了
	if (enemyVec.size() >= ENEMY_MAX_NUM) return;

	// Enemyの行動タイプを決める
	const EnemyType enemyType = (EnemyType)Random::GetRandomInt(0, 1);

	// メモリアロケーターで動的にメモリを確保する
	Enemy* newEnemy = allocator.Alloc(enemyType);

	// キャラクター操作のコンポーネントをアタッチする
	newEnemy->controller = newEnemy->enemy->AddComponent<EnemyController>(enemyType);

	// 最初に非アクティブにしないと、なぜか画面上に1Fだけ表示される
	newEnemy->enemy->transform->position = VGet(-10000, -10000, -10000);

	// Enemyの初期座標を決める
	newEnemy->controller->player = player->player.get();

	newEnemy->enemy->name = "Enemy_No.1[" + std::to_string(enemyVec.size()) + "]";

	// コンテナにプッシュする
	enemyVec.push_back(newEnemy);

	// 敵を生成した時間を更新する
	generatedTime = GetNowCount();
}

void EnemyManager::Awake()
{
	gameObject->priority = -10;
}

void EnemyManager::Start()
{
}

void EnemyManager::Update()
{
	if (GameManager::isStop) return;

	// 一定時間ごとにEnemyを生成する
	if (GetNowCount() - generatedTime >= ENEMY_POP_SPAN && !isBossEntry)
		EnemyPop();

	for (auto it = enemyVec.begin(); it != enemyVec.end();)
	{
		// マップ移動による消滅
		if ((*it)->controller->isErase)
		{
			allocator.Free(*it);
			it = enemyVec.erase(it);  // eraseの戻り値でiteratorを更新

			// スコアを減少
			Score::score += ENEMY_ERASE_SCORE;
			if (Score::score < 0)
				Score::score = 0;
		}
		// 攻撃により撃破された
		else if ((*it)->controller->isCrushing)
		{
			allocator.Free(*it);
			it = enemyVec.erase(it);  // eraseの戻り値でiteratorを更新
		}
		else
			++it;  // 削除しなかった場合のみ次の要素に進む
	}

	// ボスを倒したときの処理
	if (boss != nullptr)
	{
		if (bossCp->isCrushing)
		{
			delete boss;
			boss = nullptr;
			GameManager::isClear = true;
			Time::SetTargetFPS(12);
		}
	}

	if (GetNowCount() - startTime > TIMER_FOR_BOSS_TO_ENTRY)
	{
		isBossEntry = true;
		// ボスの出現時間を記録
		if (bossEntryTime == 0)
			bossEntryTime = GetNowCount();

		// Bossオブジェクトを生成する
		if (boss == nullptr && GetNowCount() - bossEntryTime > BOSS_ENTRY && !GameManager::isClear)
		{
			// オリジナルのモデルの情報をコピーコンストラクタで複製する
			boss = new HWGameObject(*Enemy::enemyOrigin);
			bossCp = boss->AddComponent<BossComponent>(player->player.get());
		}
	}
}
