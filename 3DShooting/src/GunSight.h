#pragma once
#include "Define.h"

/**
* @author   Suzuki N
* @date     24/10/04
* @note		�e�e��ł��������߂�Ə��R���|�[�l���g�̒�`�t�@�C��
*/


/**
 * @class	GunSight
 * @brief   �e�e��ł��������߂�Ə��R���|�[�l���g
 */
class GunSight : public HWComponent
{
public:
	// �����o�ϐ�

	//! hit�����Ƃ��ɗ^����_���[�W


public:
	// ���\�b�h

	// �f�X�g���N�^
	~GunSight();


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

