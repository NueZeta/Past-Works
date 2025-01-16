#pragma once
#include "Define.h"
#include "Player.h"

/**
* @author   Suzuki N
* @date     24/10/02
* @note		Stage�N���X�̒�`�t�@�C��
*/


/**
 * @class	Stage
 * @brief   �w�i�I�u�W�F�N�g�̃N���X
 * @detail	��̃}�b�v�I�u�W�F�N�g�����݂Ɉړ������ă}�b�v�����[�v������
 */
class Stage : public HWComponent
{
public:
	// �����o�ϐ�

	//! player�I�u�W�F�N�g
	Player* player;
	//! �X�J�C�{�b�N�X�̃��f���n���h��
	int skyBoxModelHandle;
	//! ���C�g�n���h��
	int lightHandle;


public:
	// ���\�b�h

	// �R���X�g���N�^
	Stage(Player* _player);
	// �f�X�g���N�^
	~Stage();

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

