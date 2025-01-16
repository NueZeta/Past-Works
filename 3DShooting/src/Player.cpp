#include "Player.h"

/**
* @author   Suzuki N
* @date     24/10/02
* @note		Player�̎����t�@�C��
*/


Player::Player()
{
	input = std::make_shared<InputSystem>();

	// Player�I�u�W�F�N�g�̐ݒ�
	{
		player = std::make_unique<HWGameObject>("�h�E�_�C");
		player->tag = (int)Tag::player;
		// �K�v�ȃR���|�[�l���g���A�^�b�`����
		player->AddComponent<HWRenderer>("Assets/Player/do�Edai.mv1");
		// �L�����N�^�[����̃R���|�[�l���g���A�^�b�`����
		controller = player->AddComponent<PlayerController>(input);
		// �J�v�Z���R���C�_�[���A�^�b�`
		capsuleCol = player->AddComponent<HWCapsuleCollider>();
		capsuleCol->radius = PLAYER_COLLIDR_RADIUS;
		capsuleCol->isTrigger = true;
		// �R���g���[���[�̐ݒ�
		controller->capsuleCol = capsuleCol;
		controller->modelHandle = player->GetComponent<HWRenderer>()->GetModelHandle();
	}
	

	// �J�����I�u�W�F�N�g�̐ݒ�
	{
		camera = std::make_unique<HWGameObject>("Camera");
		//camera->AddComponent<HWCamera>();
		// player�I�u�W�F�N�g�̎q�I�u�W�F�N�g�ɂ���
		camera->SetParent(player.get());
		// �J�����̏������W�̐ݒ�
		camera->transform->position = VAdd(player->transform->position, CAMERA_DEFAULT_POSITION);
	}
}

Player::~Player()
{
	camera.reset();
	player.reset();
}
