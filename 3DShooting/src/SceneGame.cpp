#include "SceneGame.h"

/**
* @author   Suzuki N
* @date     24/10/01
* @note		SceneGame�̎����t�@�C��
*/


void SceneGame::Init()
{
	// �������ƂɂȂ�GameObject�̃I���W�i�����쐬���� --------------------------------------------

	//! Enemy�I�u�W�F�N�g�̃I���W�i��(������)���쐬����
	Enemy::enemyOrigin = new HWGameObject("Enemy_Type.1(origin)");
	// �������W�����炳�Ȃ��ƂȂ���Hit����
	Enemy::enemyOrigin->transform->position = VGet(-10000, -10000, -10000);
	Enemy::enemyOrigin->active = false;
	Enemy::enemyOrigin->tag = (int)Tag::Enemy;
	// �K�v�ȃR���|�[�l���g���A�^�b�`����
	Enemy::enemyOrigin->AddComponent<HWRenderer>("Assets/Enemy/No.1/Ene_No1_mesh.mv1");
	// ��A�N�e�B�u�ɐݒ�

	//! Bullet�I�u�W�F�N�g�̃I���W�i��(������)���쐬����
	Bullet::bulletOrigin = new HWGameObject("Bullet_origin");
	// �������W�����炳�Ȃ��ƂȂ���Hit����
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
	// ���s���̃V�[���^�O
	sceneTag = SceneTag::Game; 

	// ���[�h�Ɏ��Ԃ������邽�߁A�ŏ���Enemy�𐶐����Ȃ��悤�ɂ���
	GameManager::isStop = true;

	// �e�I�u�W�F�N�g�̏�����
	player = std::make_unique<Player>();
	enemyManager = std::make_unique<HWGameObject>();
	eneManagerCp = enemyManager->AddComponent<EnemyManager>(player.get());

	// Stage
	{
		stage = std::make_unique<HWGameObject>("stage");
		stage->AddComponent<Stage>(player.get());
	}

	// SceneManager�̃V�X�e���nInputSystem���󂯎��
	sysInput = _Input;
	// �V�[���J�ڗp�R�[���o�b�N�֐���o�^
	// R �L�[�ŃV�[���J��
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
	// ���@���|���ꂽ
	if (player->controller->GetIsCrushing())
	{
		// �|���ꂽ���Ԃ��L�^
		if (crashTime == 0)
			crashTime = GetNowCount();

		// ���o�Ƃ��āA�j�󂳂ꂽ���莞�ԃX�s�[�h���ɂ߂�
		if(GetNowCount() - crashTime > PLAYER_CRASH_TIME)
		{
			Time::SetTargetFPS(60);
			SceneChange(SceneTag::Result);
			GameManager::isStop = true;
		}
	}
	// �N���A�t���O
	else if(GameManager::isClear)
	{
		// �N���A�������Ԃ��L�^
		if (clearTime == 0)
			clearTime = GetNowCount();

		// ���o�Ƃ��āA�N���A�������莞�ԃX�s�[�h���ɂ߂�
		if (GetNowCount() - clearTime > BOSS_CRASH_TIME)
		{
			Time::SetTargetFPS(60);
			SceneChange(SceneTag::Result);
			GameManager::isStop = true;
			// �X�R�A���Z
			if (player->controller->GetHp() == player->controller->GetMaxHp())
			{
				// �m�[�_���[�W�{�[�i�X
				Score::score += NO_DAMAGE_SCORE;
				GameManager::isNoDamage = true;
			}
			if (player->controller->GetHp() <= player->controller->GetMaxHp() / 20)
			{
				// ���肬��N���A�{�[�i�X
				Score::score += MORTAL_COMBAT_SCORE;
				GameManager::isMortalCombat = true;
			}
		}
	}

	// �X�R�A��\��
	DrawFormatString(GameManager::ScreenSizeX / 2 - 20, 20, GetColor(255, 0, 255), "%d", Score::score);
}
