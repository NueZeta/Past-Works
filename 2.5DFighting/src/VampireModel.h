#pragma once
#include "GameManager.h"


/**
* @author   Suzuki N
* @date     24/10/29
* @note		VampireModel�̒�`�t�@�C��
*/


class AttackPresenter;
class ProjectilePresenter;


/**
 * @class	VampireModel
 * @brief   �L�����N�^�[1�̃��f���N���X
 */
class VampireModel
{
public:
	//  �����o�ϐ�

	//! �v���C���[ID
	int playerId;
	//! �L�����N�^�[�̃p�����[�^
	Parameter param;
	//! ���݂�F������1F�ڂ̃R�}���h
	Parameter crrInputParam;
	//! �ő�HP
	int maxHp;
	//! ����HP
	int hp;
	//! �W�����v��
	float jumpPower;
	//! �㔼�g�̓����蔻��
	HWCapsuleCollider* upCollider;
	//! �㔼�g�̓����蔻��̎n�_
	int upColStartPos;
	//! �㔼�g�̓����蔻��̏I�_
	int upColendPos;
	//! �㔼�g�̓����蔻��̔��a
	float upColRadius;
	//! �����g�̓����蔻��
	HWCapsuleCollider* lowCollider;
	//! �����g�̃R���C�_�[�̒��S
	int lowCenterFrame;
	//! �����g�̓����蔻��̔��a
	float lowColRadius;
	//! ���͌n
	std::unique_ptr<InputSystem> input;
	//! �ߋ�30F���̓��͋L�^
	std::vector<InputKey> keyHistory;

	//! StLa�̍U������
	std::unique_ptr<HWGameObject> stLaAttack;
	AttackPresenter* stLaAttackPresenter;
	//! StHa�̍U������
	std::unique_ptr<HWGameObject> stHaAttack;
	AttackPresenter* stHaAttackPresenter;
	//! CtLa�̍U������
	std::unique_ptr<HWGameObject> crLaAttack;
	AttackPresenter* crLaAttackPresenter;
	//! CtHa�̍U������
	std::unique_ptr<HWGameObject> crHaAttack;
	AttackPresenter* crHaAttackPresenter;


	//! ��ѓ���̃G�t�F�N�g�n���h��
	static int projectileEffectHandle;
	//! ��ѓ���
	HWGameObject* projectile = nullptr;
	ProjectilePresenter* projectileCp;

	//! Sp2�̍U������
	std::unique_ptr<HWGameObject> sp2Attack;
	AttackPresenter* sp2AttackPresenter;
 

public:
	// �����o�֐�

	// �R���X�g���N�^
	VampireModel();


	/**
	 * @brief		�����I�ɌĂԕK�v�̂���X�V���\�b�h
	 * @author      Suzuki N
	 * @date        24/10/29
	 */
	void ExplicitUpdate();
};

