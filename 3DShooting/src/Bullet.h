#pragma once
#include "Define.h"
#include "PlayerController.h"
#include "EnemyController.h"
#include "BossComponent.h"

/**
* @author   Suzuki N
* @date     24/10/04
* @note		�U�����ɔ��˂����e�e�R���|�[�l���g�̒�`�t�@�C��
*/


/**
 * @class	Bullet
 * @brief   �U�����ɔ��˂����e�e�R���|�[�l���g
 */
class Bullet : public HWComponent
{
	friend class SceneGame;
	friend class PlayerController;
	friend class EnemyController;
	friend class BossComponent;

public:
	// �����o�ϐ�

	//! hit�����Ƃ��ɗ^����_���[�W
	int damage;
	//! Hit�𖳎����Ăق����I�u�W�F�N�g�̃^�O
	Tag ignoreTag;
	//! �e�̔��ˊp
	VECTOR FiringDirection;
	//! �C���X�^���X���������ꂽ����
	int startTyme;
	//! Hit�t���O
	bool isHit;
	// �G�t�F�N�g�Đ�
	std::unique_ptr<HWGameObject> bulletEf;


private:

	// �I���W�i���̃��f���̏����R�s�[�R���X�g���N�^�ŕ�������
	static HWGameObject* bulletOrigin;


public:
	// ���\�b�h

	// �R���X�g���N�^
	Bullet(const int _damage, const VECTOR& _dir);

	// �f�X�g���N�^
	~Bullet();


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
};

