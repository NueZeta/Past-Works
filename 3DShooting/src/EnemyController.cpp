#include "EnemyController.h"

/**
* @author   Suzuki N
* @date     24/10/03
* @note		EnemyController�̎����t�@�C��
*/



EnemyController::EnemyController(const EnemyType& _type) : isErase(false), isCrushing(false), type(_type)
{
	// �X�e�[�^�X�Ȃǂ̏������ݒ�
	maxHp = hp = ENEMY_DEFAULR_MAXHP;
	// ���������ŏ��̂ق��̓G��1���œ|���邮�炢�̍U����
	attackPower = ENEMY_DEFAULT_ATTACKPOWER;
	// �㉺�ړ��͍��E�ړ��������x��
	verticalSpeed = ENEMY_DEFAULT_SPEED_VERTICAL;
	// ���E�ړ��͑�P�ɑ��������ق������������H
	horizonSpeed = ENEMY_DEFAULT_SPEED_HORIZON;
	isShootingDown = true;

	priority = -20;
}

EnemyController::~EnemyController()
{
	for (auto it = bulletVec.begin(); it != bulletVec.end(); ++it)
		delete* it;
}

void EnemyController::Awake()
{
	gameObject->active = true;
	shootingTime = GetNowCount();

	// �A�j���[�V�������A�^�b�`
	{
		auto animator = gameObject->AddComponent<HWAnimator>();
		auto& info = animator->AnimLoad("Assets/Enemy/No.1/Anim/Ene_No1_anim.mv1");
		info.isLoop = true;
		info.playSpeed = 700.0f;
		animator->AnimChange(0);
	}
}

void EnemyController::Start()
{
	transform->scale = ENEMY_DEFAULT_SCALE;


	float random_value_X, random_value_Y;

	// �������擾
	while(true)
	{
		random_value_X = Random::GetRandomFloat(-ENEMY_POSITION_TREMOR_X, ENEMY_POSITION_TREMOR_X);
		if (random_value_X + player->transform->position.x > MOVE_LEFT_LIMIT &&
			random_value_X + player->transform->position.x < MOVE_RIGHT_LIMIT)
			break;
	}

	// �������擾
	while (true)
	{
	random_value_Y = Random::GetRandomFloat(-ENEMY_POSITION_TREMOR_Y, ENEMY_POSITION_TREMOR_Y);
		if (random_value_Y + player->transform->position.y < MOVE_UP_LIMIT &&
			random_value_Y + player->transform->position.y > MOVE_DOWN_LIMIT)
			break;
	}


	// �������W���w�肷��
	transform->position = VAdd(player->transform->position,
		VAdd(ENEMY_DEFAULT_POSITION, VGet(random_value_X, random_value_Y, 0)));

	capsuleCol = gameObject->GetComponent<HWCapsuleCollider>();
	modelHandle = gameObject->GetComponent<HWRenderer>()->GetModelHandle();

	// �s���^�C�v�ŕ���
	switch (type)
	{
	case EnemyType::straight:
		break;

	case EnemyType::Chase:
		targetPos.x = player->transform->position.x + transform->velocity.x * 1 * 60;
		targetPos.y = player->transform->position.y + transform->velocity.y * 1 * 60;
		targetPos.z = player->transform->position.z + PLAYER_AUTOACROLL_SPEED * 1 * 60;
		// �^�[�Q�b�g�̕�������
		transform->LookAt(targetPos);

		break;
	}
}

void EnemyController::Update()
{
	if (GameManager::isStop) return;

	// �s���^�C�v�ŕ���
	switch (type)
	{
	case EnemyType::straight:
		Straight();
		break;

	case EnemyType::Chase:
		Chase();
		break;
	}

	// ��莞�Ԃ��ƂɎˌ�����
	if (GetNowCount() - shootingTime > ENEMY_SHOOTING_SPAN)
		Firing(transform->position);


#ifdef DEBUG

	if (type == EnemyType::Chase)
		DrawLine3D(targetPos, transform->position, GetColor(0, 255, 0));

#endif // DEBUG


	// ��莞�Ԃ��o�߂����e�ۂ̃C���X�^���X���폜����
	for (auto it = bulletVec.begin(); it != bulletVec.end();)
	{
		// �e�ۊǗ��p�̃R���|�[�l���g���擾
		auto bulletCp = (*it)->GetComponent<Bullet>();

		// ��莞�Ԍo�߁A��������Enemy�Ƀq�b�g���Ă����ꍇ�͍폜����
		if (GetNowCount() - bulletCp->startTyme > BULLET_TIME_TO_LIVE ||
			bulletCp->isHit)
		{
			delete* it;
			it = bulletVec.erase(it);  // erase�̖߂�l��iterator���X�V
		}
		else
			++it;  // �폜���Ȃ������ꍇ�̂ݎ��̗v�f�ɐi��
	}

	// ���g��Z���W��Player�̔w��ɉ�������A���g�̏��Ńt���O�𗧂Ă�
	if (transform->position.z < player->transform->position.z - 300)
		isErase = true;

	// �R���C�_�[�̍��W�X�V
	capsuleCol->UsStartPos = MV1GetFramePosition(modelHandle, 4);
	capsuleCol->UsEndPos = MV1GetFramePosition(modelHandle, 3);

	// �u�[�X�^�[�̃G�t�F�N�g�̍��W�X�V
	//boosterEf->transform->position = MV1GetFramePosition(modelHandle, 4);
}

void EnemyController::OnTriggerEnter(HWCollider& other)
{
	if (other.gameObject->tag != (int)Tag::player) return;


		other.gameObject->GetComponent<PlayerController>()->Damage(10);

		// Hit���̃G�t�F�N�g���Đ�
		HWGameObject* effect = new HWGameObject("BulletEf");
		auto info = effect->AddComponent<HWEffect>("Assets/Effect/HitEffect.efkefc", HIT_EFFECT_SIZE);
		effect->transform->position = transform->position;
		info->stopAction = StopAction::Destroy;
		info->Play();
}

void EnemyController::Chase()
{
	// �G�@�������őO�ɐi�ނ悤�ɂ���
	gameObject->transform->velocity = VAdd(gameObject->transform->velocity, VScale(transform->forward, ENEMY_AUTOACROLL_SPEED));
}

void EnemyController::Straight()
{
	// �G�@�������őO�ɐi�ނ悤�ɂ���
	gameObject->transform->velocity = VAdd(gameObject->transform->velocity, VScale(transform->forward, ENEMY_AUTOACROLL_SPEED));
}

void EnemyController::Firing(const VECTOR& _pos)
{
	HWGameObject* bullet = new HWGameObject(*Bullet::bulletOrigin);
	// �e�ۂ̏������W
	bullet->transform->position = _pos;
	bullet->active = true;
	bullet->name = "Bullet_Ene";

	auto bulletCp = bullet->AddComponent<Bullet>(attackPower, transform->forward);
	bulletCp->ignoreTag = Tag::Enemy;
	HWCapsuleCollider* col = bullet->AddComponent<HWCapsuleCollider>();
	// �R���C�_�[�̏���������
	col->height = 0;
	col->radius = BULLET_COLLIDR_RADIUS;
	col->isTrigger = true;

	shootingTime = GetNowCount();

	bulletVec.push_back(bullet);
}

void EnemyController::Damage(int _damage)
{
	// �̗͂����炷
	hp -= _damage;

	// �̗͂�0�ɂȂ����猂�j�t���O�𗧂Ă�
	if (hp <= 0)
	{
		hp = 0;
		// �X�R�A�����Z
		Score::score += ENEMY_CRASH_SCORE;

		isCrushing = true;
		// ���j���̃G�t�F�N�g���Đ�
		HWGameObject* effect = new HWGameObject("CrushingEf");
		auto info = effect->AddComponent<HWEffect>("Assets/Effect/CrushingEffect.efkefc", CRUSHING_EFFECT_SIZE);
		effect->transform->position = transform->position;
		info->stopAction = StopAction::Destroy;
		info->Play();
		info->SetPlaySpeed(2.f);
	}
}
