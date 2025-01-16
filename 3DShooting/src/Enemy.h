#pragma once
#include "Define.h"
#include "EnemyController.h"

/**
* @author   Suzuki N
* @date     24/10/03
* @note		Enemy�N���X�̒�`�t�@�C��
*/


/**
 * @class	Enemy
 * @brief   Enemy�̋@�̃N���X
 */
class Enemy
{
	friend class EnemyManager;
	friend class SceneGame;

public:
	// �����o�ϐ�

	//! Enemy��GameObject
	HWGameObject* enemy;
	//! �G�l�~�[�R���g���[��
	EnemyController* controller;
	//! �J�v�Z���^�̓����蔻��
	HWCapsuleCollider* capsuleCol;

private:

	//! �G�I�u�W�F�N�g�̃R�s�[��
	static HWGameObject* enemyOrigin;
	//! �s���^�C�v
	EnemyType type;


public:
	// ���\�b�h

	// �R���X�g���N�^
	Enemy(const EnemyType& _type);

	// �f�X�g���N�^
	~Enemy();
};

