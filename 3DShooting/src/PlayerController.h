#pragma once
#include "Define.h"
#include "Airframe.h"
#include "Bullet.h"
#include "GunSight.h"
#include "Score.h"

/**
* @author   Suzuki N
* @date     24/10/02
* @note		PlayerController�R���|�[�l���g�̒�`�t�@�C��
*/


/**
 * @class	PlayerController
 * @brief   �v���C���[�L�����N�^�[�̃A�j���[�V�����Ȃǂ��Ǘ�����R���|�[�l���g
 */
class PlayerController : public HWComponent, public Airframe
{
	friend class Player;

private:
	// �����o�ϐ�

	//! �@�̑���p�̓���
	std::shared_ptr<InputSystem> input;
	//! �����蔻��
	HWCapsuleCollider* capsuleCol;

	//! �R���W�����̎n�_
	int collision_start;
	//! �R���W�����̏I�_
	int collision_end;
	//! �e��1
	int muzzle_1;
	//! �e��2
	int muzzle_2;
	//! �u�[�X�^�[1
	int booster_1;
	//! �u�[�X�^�[2
	int booster_2;

	//! ���f���n���h��
	int modelHandle;
	//! �e�ۂ̃C���X�^���X�̃R���e�i
	std::vector<HWGameObject*> bulletVec;
	//! �K���T�C�g�I�u�W�F�N�g
	std::unique_ptr<HWGameObject> gunSightObj;
	//! �K���T�C�g�R���|�[�l���g
	GunSight* sightCp;
	//! �U���ɂ�錂�j�t���O
	bool isCrushing;

	//! �u�[�X�^�[�̃G�t�F�N�g1
	std::unique_ptr<HWGameObject> boosterEf_1;
	//! �u�[�X�^�[�̃G�t�F�N�g2
	std::unique_ptr<HWGameObject> boosterEf_2;


public:
	// ���\�b�h

	// �R���X�g���N�^
	PlayerController(std::shared_ptr<InputSystem>);

	// �f�X�g���N�^
	~PlayerController();

	/**
	 * @brief		�U����Hit����
	 * @author      Suzuki N
	 * @date        24/10/05
	 */
	void Damage(int _damage);

	/**
	 * @brief		�U����Hit����
	 * @author      Suzuki N
	 * @date        24/10/05
	 */
	bool GetIsCrushing() const { return isCrushing; }


	/**
	 * @brief		�I�u�W�F�N�g�ɃA�^�b�`���ꂽ�Ƃ��ɓ������\�b�h
	 * @author      Suzuki N
	 * @date        24/10/02
	 */
	void Awake()override;

	/**
	 * @brief		�ŏ���Update���\�b�h�̒��O�ɓ������\�b�h
	 * @author      Suzuki N
	 * @date        24/10/02
	 */
	void Start()override;

	/**
	 * @brief		��F�Ă΂�郁�\�b�h
	 * @author      Suzuki N
	 * @date        24/10/02
	 */
	void Update()override;

private:

	/**
	 * @brief		�ړ����\�b�h
	 * @author      Suzuki N
	 * @date        24/10/02
	 */
	void Move(const VECTOR&);

	/**
	 * @brief		�e������
	 * @author      Suzuki N
	 * @date        24/10/04
	 */
	void Firing(const VECTOR& _pos);
};

