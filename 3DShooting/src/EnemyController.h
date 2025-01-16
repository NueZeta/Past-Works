#pragma once
#include "Define.h"
#include "Airframe.h"
#include "Bullet.h"
#include "GunSight.h"
#include "Score.h"
#include "BossComponent.h"

/**
* @author   Suzuki N
* @date     24/10/03
* @note		Enemy�𑀍삷��R���|�[�l���g�̒�`�t�@�C��
*/


/**
 * @enum	EnemyType
 * @brief   Enemy�̍s���p�^�[��
 */
enum class EnemyType
{
	//! �܂������i��(0)
	straight,
	//! Player�Ɍ������Ă���(1)
	Chase,
};


/**
 * @class	EnemyController
 * @brief   Enemy�𑀍삷��R���|�[�l���g
 */
class EnemyController : public HWComponent, Airframe
{
public:
	// �����o�ϐ�

	//! Player�I�u�W�F�N�g
	HWGameObject* player;
	//! ���f���n���h��
	int modelHandle;
	//! �����蔻��̃R���|�[�l���g
	HWCapsuleCollider* capsuleCol;
	//! �}�b�v�ړ��ɂ����Ńt���O
	bool isErase;
	//! �U���ɂ�錂�j�t���O
	bool isCrushing;
	//! �s���^�C�v
	EnemyType type;
	//! �e�ۂ̃C���X�^���X�̃R���e�i
	std::vector<HWGameObject*> bulletVec;
	//! �O�Ɏˌ���������
	int shootingTime;


	// �^�[�Q�b�g�̈ʒu
	VECTOR targetPos;

public:
	// ���\�b�h

	// �R���X�g���N�^
	EnemyController(const EnemyType& _type);

	// �f�X�g���N�^
	~EnemyController()override;


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

private:

	/**
	 * @brief		�ǂ��^�C�v�̓G�̍s�����[�`��
	 * @author      Suzuki N
	 * @date        24/10/05
	 */
	void Chase();

	/**
	 * @brief		���i����^�C�v�̓G�̍s�����[�`��
	 * @author      Suzuki N
	 * @date        24/10/05
	 */
	void Straight();

	/**
	 * @brief		�e������
	 * @author      Suzuki N
	 * @date        24/10/05
	 */
	void Firing(const VECTOR& _pos);

};

