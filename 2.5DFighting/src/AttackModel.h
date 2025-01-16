#pragma once
#include "GameManager.h"
#include "VampireModel.h"

/**
* @author   Suzuki N
* @date     24/10/31
* @note		AttackModel�̒�`�t�@�C��
*/


/**
 * @class	AttackModel
 * @brief   �U������̃��f���N���X
 */
class AttackModel
{
public:
	//  �����o�ϐ�

	//! �t�^����Ă��鑮��
	AttackAttribute attribute;
	//! �U������
	HWCapsuleCollider* attackCol;
	//! �E�����̏ꍇ�̍U������̒��S���W�̃t���[��
	int attackColCenterFrame_right;
	//! �������̏ꍇ�̍U������̒��S���W�̃t���[��
	int attackColCenterFrame_left;
	//! �U������̔��a
	float attackColRadius;
	//! Hit���̃_���[�W
	int damage;
	//! Hit�d��
	int hitStun;
	//! Guard�d��
	int guardStun;
	//! ���f���n���h��
	int modelHandle;
	//! ���f��
	VampireModel* vampireModel;


public:
	// �����o�֐�

	// �R���X�g���N�^
	AttackModel();	
};

