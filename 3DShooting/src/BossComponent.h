#pragma once
#include "Define.h"
#include "Airframe.h"
#include "Bullet.h"
#include "Score.h"

/**
* @author   Suzuki N
* @date     24/10/09
* @note		Boss�𑀍삷��R���|�[�l���g�̒�`�t�@�C��
*/


/**
 * @class	BossMoveType
 * @brief   �{�X�̍s���̎��
 */
enum class BossMoveType
{
	//! �G���g���[��(0)
	Entry,
	//! ���̏�ɂƂǂ܂�(1)
	Wait,
	//! �ړ�(2)
	Move,
	//! �U��(3)
	Fire,
};



/**
 * @class	BossComponent
 * @brief   Boss�𑀍삷��R���|�[�l���g
 */
class BossComponent : public HWComponent, Airframe
{
public:
	// �����o�ϐ�

	//! Player�I�u�W�F�N�g
	HWGameObject* player;
	//! ���f���n���h��
	int modelHandle;
	//! �����蔻��̃R���|�[�l���g
	HWCapsuleCollider* capsuleCol;
	//! �U���ɂ�錂�j�t���O
	bool isCrushing;
	//! �e�ۂ̃C���X�^���X�̃R���e�i
	std::vector<HWGameObject*> bulletVec;

private:
	//! �^�[�Q�b�g�̈ʒu
	VECTOR targetPos;
	//! ���݂Ƃ��Ă���s���^�C�v 
	BossMoveType moveType;
	//! �O��s�������������
	int moveTime;
	//! �ړ����\�b�h�ɂ��ړ�����
	int moveDirection;
	//! �O�Ɏˌ���������
	int shootingTime;


public:
	// ���\�b�h

	// �R���X�g���N�^
	BossComponent(HWGameObject* _player);

	// �f�X�g���N�^
	~BossComponent()override;


	// �G���g���[���̍s��
	void Entry();
	// �ҋ@
	void Wait();
	// �ړ�
	void Move();
	// �U��
	void Fire();
	// �s���^�C�v�������_���Ɍ��߂�
	void MoveTypeSelect();


	/**
	 * @brief		�U����Hit����
	 * @author      Suzuki N
	 * @date        24/10/05
	 */
	void Damage(int _damage);

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
	* 
	 * @brief		��F�Ă΂�郁�\�b�h
	 * @author      Suzuki N
	 * @date        24/10/02
	 */
	void Update()override;

	/**
	 * @brief		�R���C�_�[Hit���ɌĂ΂�郁�\�b�h
	 * @param[out]	Hit�����R���C�_�[
	 * @author      Suzuki N
	 * @date        24/10/02
	 */
	void OnTriggerEnter(HWCollider& other)override;
};

