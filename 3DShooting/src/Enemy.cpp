#include "Enemy.h"

/**
* @author   Suzuki N
* @date     24/10/03
* @note		Enemy�̎����t�@�C��
*/


HWGameObject* Enemy::enemyOrigin = nullptr;


Enemy::Enemy(const EnemyType& _type)
{
	// �I���W�i���̃��f���̏����R�s�[�R���X�g���N�^�ŕ�������
	enemy = new HWGameObject(*enemyOrigin);

	// ����������
	enemy->active = true;
	controller = enemy->GetComponent<EnemyController>();

	// �����蔻���t�^
	capsuleCol = enemy->AddComponent<HWCapsuleCollider>();
	// �����蔻��̏�����
	capsuleCol->radius = ENEMY_COLLIDR_RADIUS;
	capsuleCol->isTrigger = true;
}

Enemy::~Enemy()
{
	delete enemy;
}
