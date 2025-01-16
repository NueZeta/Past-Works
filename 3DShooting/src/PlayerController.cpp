#include "PlayerController.h"

/**
* @author   Suzuki N
* @date     24/10/02
* @note		PlayerController�̎����t�@�C��
*/


PlayerController::PlayerController(std::shared_ptr<InputSystem> _input)
	: collision_start(-1), collision_end(-1), muzzle_1(-1), muzzle_2(-1),
	booster_1(-1), booster_2(-1)
{
	// �X�e�[�^�X�Ȃǂ̏������ݒ�
	maxHp = hp = PLAYER_DEFAULR_MAXHP;
	// ���������ŏ��̂ق��̓G��1���œ|���邮�炢�̍U����
	attackPower = PLAYER_DEFAULT_ATTACKPOWER;
	// �㉺�ړ��͍��E�ړ��������x��
	verticalSpeed = PLAYER_DEFAULT_SPEED_VERTICAL;
	// ���E�ړ��͑�P�ɑ��������ق������������H
	horizonSpeed = PLAYER_DEFAULT_SPEED_HORIZON;
	isShootingDown = true;

	// ���͌n�̐ݒ�
	{
		input = _input;
		// ���͂����m����L�[�R�[�h��o�^
		input->AddKeyCode("move", { KEY_INPUT_W, KEY_INPUT_S, KEY_INPUT_D, KEY_INPUT_A, KEY_INPUT_SPACE });
		// ���͊��m���ɌĂ΂��R�[���o�b�N�֐���ݒ�
		input->AddCallBack("move", [&](InputAction::CallBackContext context)
			{
				if (GameManager::isStop || isCrushing) return;

				for (auto it = context.key.begin(); it != context.key.end(); ++it)
					if (it->inputState != InputState::Waiting)
						switch (it->keyCode)
						{
						case KEY_INPUT_W:
							Move(VGet(0, verticalSpeed, 0));
							break;

						case KEY_INPUT_S:
							Move(VGet(0, -verticalSpeed, 0));
							break;

						case KEY_INPUT_D:
							Move(VGet(horizonSpeed, 0, 0));
							break;

						case KEY_INPUT_A:
							Move(VGet(-horizonSpeed, 0, 0));
							break;

						case KEY_INPUT_SPACE:
							if(it->inputState == InputState::Started)
							{
								// �U��
								Firing(MV1GetFramePosition(modelHandle, muzzle_1));
								Firing(MV1GetFramePosition(modelHandle, muzzle_2));
							}
							break;
						}
			});
	}
}

PlayerController::~PlayerController()
{
	gunSightObj.reset();
	auto effect1 = boosterEf_1->GetComponent<HWEffect>();
	effect1->Stop();
	boosterEf_1.reset();
	auto effect2 = boosterEf_2->GetComponent<HWEffect>();
	effect2->Stop();
	boosterEf_2.reset();

	for (auto it = bulletVec.begin(); it != bulletVec.end(); ++it)
		delete* it;
}

void PlayerController::Awake()
{
	// �������W�̐ݒ�
	gameObject->transform->position = PLAYER_DEFAULT_POSISION;
	gameObject->transform->rotate = PLAYER_DEFAULT_ROTATE;

	// �K���T�C�g�I�u�W�F�N�g�̍쐬
	gunSightObj = std::make_unique<HWGameObject>("GunSight");
	sightCp = gunSightObj->AddComponent<GunSight>();
	// �K���T�C�g�I�u�W�F�N�g�����g�̎q�I�u�W�F�N�g�ɂ���
	gunSightObj->SetParent(gameObject);
}

void PlayerController::Start()
{
	collision_start = MV1SearchFrame(modelHandle, "Collision_Start");
	collision_end = MV1SearchFrame(modelHandle, "Collision_End");

	muzzle_1 = MV1SearchFrame(modelHandle, "Muzzle_1");
	muzzle_2 = MV1SearchFrame(modelHandle, "Muzzle_2");

	booster_1 = MV1SearchFrame(modelHandle, "Booster_1");
	booster_2 = MV1SearchFrame(modelHandle, "Booster_2");


	// �u�[�X�^�[�̃G�t�F�N�g�̐ݒ�
	{
		{
			boosterEf_1 = std::make_unique<HWGameObject>("booster_1");
			boosterEf_1->SetParent(gameObject);
			auto effect = boosterEf_1->AddComponent<HWEffect>("Assets/Effect/booster.efkefc", BOOSTER_EFFECT_SIZE);
			// �I�����̃A�N�V���������[�v�ɐݒ�
			effect->stopAction = StopAction::Loop;
			// �G�t�F�N�g�̍Đ�
			effect->Play();
		}
		{
			boosterEf_2 = std::make_unique<HWGameObject>("booster_2");
			boosterEf_2->SetParent(gameObject);
			auto effect = boosterEf_2->AddComponent<HWEffect>("Assets/Effect/booster.efkefc", BOOSTER_EFFECT_SIZE);
			// �I�����̃A�N�V���������[�v�ɐݒ�
			effect->stopAction = StopAction::Loop;
			// �G�t�F�N�g�̍Đ�
			effect->Play();
		}
	}
}

void PlayerController::Update()
{
	// �v���C���[�̋@�������őO�ɐi�ނ悤�ɂ���
	gameObject->transform->velocity = VAdd(gameObject->transform->velocity, VScale(transform->forward, PLAYER_AUTOACROLL_SPEED));

	// �ړ��ɂ��@�̂��X�Ă���ꍇ�A���s�ɖ߂��͂�������
	if (gameObject->transform->rotate.z != PLAYER_DEFAULT_ROTATE.z)
		gameObject->transform->rotate.z += -gameObject->transform->rotate.z / POWER_RETURN_PARALLEL_Z;
	if (gameObject->transform->rotate.x != PLAYER_DEFAULT_ROTATE.x)
		gameObject->transform->rotate.x += -gameObject->transform->rotate.x / POWER_RETURN_PARALLEL_X;


	// ��莞�Ԃ��o�߂����e�ۂ̃C���X�^���X���폜����
	for (auto it = bulletVec.begin(); it != bulletVec.end();)
	{
		// �e�ۊǗ��p�̃R���|�[�l���g���擾
		auto bulletCp = (*it)->GetComponent<Bullet>();

		// ��莞�Ԍo�߁A��������Enemy�Ƀq�b�g���Ă����ꍇ�͍폜����
		if (GetNowCount() - bulletCp->startTyme > BULLET_TIME_TO_LIVE ||
			bulletCp->isHit)
		{
			delete *it;
			it = bulletVec.erase(it);  // erase�̖߂�l��iterator���X�V
		}
		else
			++it;  // �폜���Ȃ������ꍇ�̂ݎ��̗v�f�ɐi��
	}


	// ��莞�Ԃ��o�߂����e�ۂ̃C���X�^���X���폜����
	for (auto it = bulletVec.begin(); it != bulletVec.end(); /* �����ł͍X�V���Ȃ� */)
	{
		// �e�ۊǗ��p�̃R���|�[�l���g���擾
		auto bulletCp = (*it)->GetComponent<Bullet>();

		// ��莞�Ԍo�߁A��������Enemy�Ƀq�b�g���Ă����ꍇ�͍폜����
		if (GetNowCount() - bulletCp->startTyme > BULLET_TIME_TO_LIVE ||
			bulletCp->isHit)
		{
			delete *it;
			it = bulletVec.erase(it);  // erase�̖߂�l��iterator���X�V
		}
		else
			++it;  // �폜���Ȃ������ꍇ�̂ݎ��̗v�f�ɐi��
	}


	// �J�����ݒ�
	auto& pos = gameObject->GetChild(1)->transform->position;
	SetCameraPositionAndTarget_UpVecY(pos, VAdd(transform->position, CAMERA_POSITION));

	// �R���C�_�[�̍��W�X�V
	capsuleCol->UsStartPos = MV1GetFramePosition(modelHandle, collision_start);
	capsuleCol->UsEndPos = MV1GetFramePosition(modelHandle, collision_end);

	// �u�[�X�^�[�̃G�t�F�N�g�̍��W�X�V
	boosterEf_1->transform->position = MV1GetFramePosition(modelHandle, booster_1);
	boosterEf_2->transform->position = MV1GetFramePosition(modelHandle, booster_2);


	DrawFormatString(10, 20, GetColor(0, 255, 0), "%d / %d", hp,maxHp);
}

void PlayerController::Move(const VECTOR& _velocity)
{
	// �ړ��x�N�g�������Z
	transform->velocity = VAdd(transform->velocity, _velocity);

	if (transform->position.x + transform->velocity.x < MOVE_LEFT_LIMIT ||
		transform->position.x + transform->velocity.x > MOVE_RIGHT_LIMIT)
		transform->velocity.x = 0.f;
	if (transform->position.y + transform->velocity.y < MOVE_DOWN_LIMIT ||
		transform->position.y + transform->velocity.y > MOVE_UP_LIMIT)
		transform->velocity.y = 0.f;


	// �ړ��ʂɉ����ċ@�̂��X����
	transform->rotate.z += _velocity.x * AIRFRAME_SLOPE_SPEED_Z;

	if(transform->rotate.z > AIRFRAME_MAX_SLOPE_Z ||
		transform->rotate.z < -AIRFRAME_MAX_SLOPE_Z)
	{
		transform->rotate.z -= _velocity.x * AIRFRAME_SLOPE_SPEED_Z;
	}

	transform->rotate.x -= _velocity.y * AIRFRAME_SLOPE_SPEED_X;

	if(transform->rotate.x > AIRFRAME_MAX_SLOPE_X ||
		transform->rotate.x < -AIRFRAME_MAX_SLOPE_X)
	{
		transform->rotate.x += _velocity.y * AIRFRAME_SLOPE_SPEED_X;
	}
}

void PlayerController::Firing(const VECTOR& _pos)
{
	HWGameObject* bullet = new HWGameObject(*Bullet::bulletOrigin);
	// �e�ۂ̏������W
	bullet->transform->position = _pos;
	bullet->active = true;
	bullet->name = "Bullet_player";

	auto bulletCp = bullet->AddComponent<Bullet>(attackPower, transform->forward);
	bulletCp->ignoreTag = Tag::player;
	HWCapsuleCollider* col = bullet->AddComponent<HWCapsuleCollider>();
	// �R���C�_�[�̏���������
	col->height = 0;
	col->radius = BULLET_COLLIDR_RADIUS;
	col->isTrigger = true;

	bulletVec.push_back(bullet);
}

void PlayerController::Damage(int _damage)
{
	// �̗͂����炷
	hp -= _damage;

	// �̗͂�0�ɂȂ����猂�j�t���O�𗧂Ă�
	if (hp <= 0)
	{
		hp = 0;
		// �X�R�A�����Z
		Score::score += PLAYER_CRASH_SCORE;
		if (Score::score)
			Score::score = 0;

		isCrushing = true;
		Time::SetTargetFPS(10);

		// ���j�p�̃G�t�F�N�g���Đ�
		HWGameObject* effect = new HWGameObject("CrushingEf");
		auto info = effect->AddComponent<HWEffect>("Assets/Effect/CrushingEffect.efkefc", CRUSHING_EFFECT_SIZE);
		effect->transform->position = transform->position;
		info->stopAction = StopAction::Destroy;
		info->Play();
		info->SetPlaySpeed(2.f);
	}
}
