#pragma once
#include "GameManager.h"
#include "VampireModel.h"

/**
* @author   Suzuki N
* @date     24/11/05
* @note		ProjectileModel�̒�`�t�@�C��
*/


/**
 * @class	ProjectileModel
 * @brief   ��ѓ���̍U������̃��f���N���X
 */
class ProjectileModel
{
public:
	//  �����o�ϐ�

	//! �t�^����Ă��鑮��
	AttackAttribute attribute;
	//! �U������
	HWCapsuleCollider* attackCol;
	//! �G�t�F�N�g��path
	std::string effectPath;
	//! �G�t�F�N�g�R���|�[�l���g
	HWEffect* effectCp;
	//! �U������̔��a
	float attackColRadius;
	//! Hit���̃_���[�W
	int damage;
	//! Hit�d��
	int hitStun;
	//! Guard�d��
	int guardStun;
	//! ���f��
	VampireModel* vampireModel;
	//! ? �E�ɂƂ�(true) : ���ɂƂ�(false)
	bool flyingDirection;
	//! �ړ��X�s�[�h
	float speed;
	//! ��������
	int generateTime;


public:
	// �����o�֐�

	// �R���X�g���N�^
	ProjectileModel();
};

