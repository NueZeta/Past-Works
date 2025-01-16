#pragma once
#include "Define.h"
#include "Player.h"
#include "Enemy.h"


/**
* @author   Suzuki N
* @date     24/10/03
* @note		Enemy���Ǘ�����N���X�̒�`�t�@�C��
*/


/**
 * @class	EnemyManager
 * @brief   Enemy�̊Ǘ��A���|�b�v�Ȃǂ��s���N���X
 */
class EnemyManager : public HWComponent
{
public:
	// �����o�ϐ�

	//! �C���X�^���X������Enemy�̃R���e�i
	std::vector<Enemy*> enemyVec;
	//! Player�̃I�u�W�F�N�g
	Player* player;
	//! Enemy�̃������A���P�[�^�[
	PoolAllocator<Enemy, ENEMY_MAX_NUM> allocator;
	//! Boss���o�����Ă��邩
	bool isBossEntry;
	//! Boss���o����������
	int bossEntryTime;
	//! Boss��GameObject
	HWGameObject* boss;
	//! Boss�̃R���|�[�l���g
	BossComponent* bossCp;


private:
	//! �O��Enemy�𐶐���������
	int generatedTime;
	//! �J�n����
	int startTime;


public:
	// ���\�b�h

	// �R���X�g���N�^
	EnemyManager(Player* _player);

	// �f�X�g���N�^
	~EnemyManager();

	/**
	 * @brief		�G�I�u�W�F�N�g���|�b�v������
	 * @author      Suzuki N
	 * @date        24/10/03
	 */
	void EnemyPop();

	/**
	 * @brief		�I�u�W�F�N�g�ɃA�^�b�`���ꂽ�Ƃ��ɓ������\�b�h
	 * @author      Suzuki N
	 * @date        24/10/02
	 */
	void Awake()override;

	/**
	 * @brief		�ŏ���Update���\�b�h�̒��O�ɓ���
	 * @author      Suzuki N
	 * @date        24/10/04
	 */
	void Start()override;

	/**
	 * @brief		��F�Ă΂�郁�\�b�h
	 * @author      Suzuki N
	 * @date        24/10/02
	 */
	void Update()override;
};

