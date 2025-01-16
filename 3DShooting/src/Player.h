#pragma once
#include "Airframe.h"
#include "PlayerController.h"

/**
* @author   Suzuki N
* @date     24/10/02
* @note		�v���C���[�����삷��Player�N���X�̒�`�t�@�C��
*/


/**
 * @class	Player
 * @brief   �v���C���[�����삷��@�̃N���X
 */
class Player
{
public:
	// �����o�ϐ�

	//! Player��GameObject
	std::unique_ptr<HWGameObject> player;
	//! �v���C���[�R���g���[��
	PlayerController* controller;
	//! �v���C���[�̓����蔻��(�J�v�Z���^)
	HWCapsuleCollider* capsuleCol;
	//! Camera��GameObject
	std::unique_ptr<HWGameObject> camera;
	//! �L�����N�^�[����p��InputSystem
	std::shared_ptr<InputSystem> input;
	

public:
	// ���\�b�h

	// �R���X�g���N�^
	Player();

	// �f�X�g���N�^
	~Player();
};

