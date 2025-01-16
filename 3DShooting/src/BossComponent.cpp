#include "BossComponent.h"

BossComponent::BossComponent(HWGameObject* _player) : player(_player), moveType(BossMoveType::Entry),
	moveTime(GetNowCount()), shootingTime(GetNowCount())
{
	// �X�e�[�^�X�Ȃǂ̏������ݒ�
	maxHp = hp = BOSS_DEFAULR_MAXHP;
	attackPower = BOSS_DEFAULT_ATTACKPOWER;
	isShootingDown = false;
}

BossComponent::~BossComponent()
{
	for (auto it = bulletVec.begin(); it != bulletVec.end(); ++it)
		delete* it;
}

void BossComponent::Entry()
{
	if (transform->position.y < player->transform->position.y)
		MoveTypeSelect();

	// ���X�ɉ��ɍ~��Ă���
	transform->velocity.y -= BOSS_MOVE_SPEED * 2;
}

void BossComponent::Wait()
{
	 // ��莞�Ԍo�߂����玟�̍s���ֈڍs����
	if (GetNowCount() - moveTime > BOSS_TIME_UNTIL_NEXT_ACTION)
		MoveTypeSelect();
}

void BossComponent::Move()
{
	// ��莞�Ԍo�߂����玟�̍s���ֈڍs����
	if (GetNowCount() - moveTime > BOSS_TIME_UNTIL_NEXT_ACTION)
		MoveTypeSelect();

	// �ړ����������܂��Ă��Ȃ��ꍇ�A�����_���Ɍ��߂�
	if(moveDirection == -1)
		moveDirection = Random::GetRandomInt(0, 3);

	switch (moveDirection)
	{
		// ��
	case 0:
		if (transform->position.y > MOVE_UP_LIMIT)
		{
			moveDirection = -1;
			break;
		}
		transform->velocity.y += BOSS_MOVE_SPEED;
		break;

		// ��
	case 1:
		if (transform->position.y < MOVE_DOWN_LIMIT)
		{
			moveDirection = -1;
			break;
		}
		transform->velocity.y -= BOSS_MOVE_SPEED;
		break;

		// ��
	case 2:
		if (transform->position.x < MOVE_LEFT_LIMIT)
		{
			moveDirection = -1;
			break;
		}
		transform->velocity.x -= BOSS_MOVE_SPEED;
		break;

		// ��
	case 3:
		if (transform->position.x > MOVE_RIGHT_LIMIT)
		{
			moveDirection = -1;
			break;
		}
		transform->velocity.x += BOSS_MOVE_SPEED;
		break;
	}
}

void BossComponent::Fire()
{
	// ��莞�Ԍo�߂����玟�̍s���ֈڍs����
	if (GetNowCount() - moveTime > BOSS_TIME_UNTIL_NEXT_ACTION * 2)
		MoveTypeSelect();

	// ���Ԋu��Player�Ɍ����čU������
	if (GetNowCount() - shootingTime > BOSS_FIRE_SPAN)
	{
		// �ڕW�n�_
		VECTOR targetPos = player->transform->position;

		targetPos = VAdd(player->transform->position, VScale(player->transform->velocity, 1 * 60));
		targetPos.y += 20;

		HWGameObject* bullet = new HWGameObject(*Bullet::bulletOrigin);
		// �e�ۂ̏������W
		bullet->transform->position = transform->position;
		bullet->active = true;
		bullet->name = "Bullet_Boss";
		bullet->transform->scale = VScale(bullet->transform->scale, 1);

		bullet->transform->LookAt(targetPos);
		bullet->transform->rotate = VAdd(bullet->transform->rotate, VGet(0, 190,0));


		// Boss -> Player �Ɍ����������x�N�g��
		VECTOR dir = VNorm(VSub(targetPos, bullet->transform->position));

		auto bulletCp = bullet->AddComponent<Bullet>(attackPower, dir);
		bulletCp->ignoreTag = Tag::Boss;
		HWCapsuleCollider* col = bullet->AddComponent<HWCapsuleCollider>();
		// �R���C�_�[�̏���������
		col->height = 0;
		col->radius = BULLET_COLLIDR_RADIUS * 3;
		col->isTrigger = true;

		// �R���e�i�ɒǉ�����
		bulletVec.push_back(bullet);
		// �U�����Ԃ��㏑��
		shootingTime = GetNowCount();
	}
}

void BossComponent::MoveTypeSelect()
{
	// Entry���̂������s�����烉���_���Ɍ��߂�
	moveType = (BossMoveType)Random::GetRandomInt(1, 3);
	moveTime = GetNowCount();
	moveDirection = -1;
}

void BossComponent::Damage(int _damage)
{
	// �̗͂����炷
	hp -= _damage;

	// �̗͂�0�ɂȂ����猂�j�t���O�𗧂Ă�
	if (hp <= 0)
	{
		hp = 0;
		// �{�X�p�̃X�R�A�����Z
		Score::score += BOSS_CRASH_SCORE;

		isCrushing = true;
		// ���j���̃G�t�F�N�g���Đ�
		HWGameObject* effect = new HWGameObject("CrushingEf");
		auto info = effect->AddComponent<HWEffect>("Assets/Effect/CrushingEffect.efkefc", CRUSHING_EFFECT_SIZE * 2);
		effect->transform->position = transform->position;
		info->stopAction = StopAction::Destroy;
		info->Play();
		info->SetPlaySpeed(2.f);
	}
}

void BossComponent::Awake()
{
	gameObject->tag = (int)Tag::Boss;
	gameObject->name = "Boss";
	gameObject->active = true;

	// �A�j���[�V�������A�^�b�`
	{
		auto animator = gameObject->AddComponent<HWAnimator>();
		auto& info = animator->AnimLoad("Assets/Enemy/No.1/Anim/Ene_No1_anim.mv1");
		info.isLoop = true;
		info.playSpeed = 700.0f;
		animator->AnimChange(0);
	}

	// �����蔻���t�^
	capsuleCol = gameObject->AddComponent<HWCapsuleCollider>();
	// �����蔻��̏�����
	capsuleCol->radius = BOSS_COLLIDR_RADIUS;
	capsuleCol->isTrigger = true;
	modelHandle = gameObject->GetComponent<HWRenderer>()->GetModelHandle();
}

void BossComponent::Start()
{
	transform->scale = BOSS_DEFAULT_SCALE;

	// �������W���w�肷��
	transform->position = VAdd(player->transform->position, BOSS_DEFAULT_POSITION);
	transform->rotate = BOSS_DEFAULT_ROTATE;
}

void BossComponent::Update()
{
	if (GameManager::isStop) return;

	// �v���C���[�̋@�������őO�ɐi�ނ悤�ɂ���
	gameObject->transform->velocity = VAdd(gameObject->transform->velocity, VScale(transform->forward, PLAYER_AUTOACROLL_SPEED));

	// ���݂̍s���^�C�v�ɂ���ĕ���
	switch (moveType)
	{
	case BossMoveType::Entry:
		Entry();
		break;
	case BossMoveType::Wait:
		Wait();
		break;
	case BossMoveType::Move:
		Move();
		break;
	case BossMoveType::Fire:
		Fire();
		break;
	}

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

	// �R���C�_�[�̍��W�X�V
	capsuleCol->UsStartPos = MV1GetFramePosition(modelHandle, 4);
	capsuleCol->UsEndPos = MV1GetFramePosition(modelHandle, 3);


}

void BossComponent::OnTriggerEnter(HWCollider& other)
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
