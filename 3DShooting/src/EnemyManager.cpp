#include "EnemyManager.h"

/**
* @author   Suzuki N
* @date     24/10/03
* @note		EnemyManager�̎����t�@�C��
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
	// �}�b�v���Enemy�̑���������̒l�𒴂���ꍇ�͂��̂܂܏I��
	if (enemyVec.size() >= ENEMY_MAX_NUM) return;

	// Enemy�̍s���^�C�v�����߂�
	const EnemyType enemyType = (EnemyType)Random::GetRandomInt(0, 1);

	// �������A���P�[�^�[�œ��I�Ƀ��������m�ۂ���
	Enemy* newEnemy = allocator.Alloc(enemyType);

	// �L�����N�^�[����̃R���|�[�l���g���A�^�b�`����
	newEnemy->controller = newEnemy->enemy->AddComponent<EnemyController>(enemyType);

	// �ŏ��ɔ�A�N�e�B�u�ɂ��Ȃ��ƁA�Ȃ�����ʏ��1F�����\�������
	newEnemy->enemy->transform->position = VGet(-10000, -10000, -10000);

	// Enemy�̏������W�����߂�
	newEnemy->controller->player = player->player.get();

	newEnemy->enemy->name = "Enemy_No.1[" + std::to_string(enemyVec.size()) + "]";

	// �R���e�i�Ƀv�b�V������
	enemyVec.push_back(newEnemy);

	// �G�𐶐��������Ԃ��X�V����
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

	// ��莞�Ԃ��Ƃ�Enemy�𐶐�����
	if (GetNowCount() - generatedTime >= ENEMY_POP_SPAN && !isBossEntry)
		EnemyPop();

	for (auto it = enemyVec.begin(); it != enemyVec.end();)
	{
		// �}�b�v�ړ��ɂ�����
		if ((*it)->controller->isErase)
		{
			allocator.Free(*it);
			it = enemyVec.erase(it);  // erase�̖߂�l��iterator���X�V

			// �X�R�A������
			Score::score += ENEMY_ERASE_SCORE;
			if (Score::score < 0)
				Score::score = 0;
		}
		// �U���ɂ�茂�j���ꂽ
		else if ((*it)->controller->isCrushing)
		{
			allocator.Free(*it);
			it = enemyVec.erase(it);  // erase�̖߂�l��iterator���X�V
		}
		else
			++it;  // �폜���Ȃ������ꍇ�̂ݎ��̗v�f�ɐi��
	}

	// �{�X��|�����Ƃ��̏���
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
		// �{�X�̏o�����Ԃ��L�^
		if (bossEntryTime == 0)
			bossEntryTime = GetNowCount();

		// Boss�I�u�W�F�N�g�𐶐�����
		if (boss == nullptr && GetNowCount() - bossEntryTime > BOSS_ENTRY && !GameManager::isClear)
		{
			// �I���W�i���̃��f���̏����R�s�[�R���X�g���N�^�ŕ�������
			boss = new HWGameObject(*Enemy::enemyOrigin);
			bossCp = boss->AddComponent<BossComponent>(player->player.get());
		}
	}
}
