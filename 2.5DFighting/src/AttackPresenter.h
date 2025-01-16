#pragma once
#include "AttackModel.h"
#include "AttackView.h"
#include "VampirePresenter.h"

/**
* @author   Suzuki N
* @date     24/10/31
* @note		AttackPresenter�̒�`�t�@�C��
*/


/**
 * @class	AttackPresenter
 * @brief   �U������̊Ǘ��N���X
 */
class AttackPresenter : public HWComponent
{
public:
	//  �����o�ϐ�

	//! ���f���N���X
	std::unique_ptr<AttackModel> model;
	//! �r���[�R���|�[�l���g
	AttackView* view;


public:
	// �����o�֐�

	/**
	 * @brief		�R���W��������ݒ肷��
	 * @param[in]	VampireModel*	���g�̃��f��
	 * @param[in]	const int	���f���n���h��
	 * @param[in]	const int	�����蔻��̒��S�ɂȂ郂�f���̃t���[��(�E�����̏ꍇ)
	 * @param[in]	const int	�����蔻��̒��S�ɂȂ郂�f���̃t���[��(�������̏ꍇ)
	 * @param[in]	const float	�����蔻��̔��a
	 * @param[in]	const int	Hit���̃_���[�W
	 * @param[in]	const int	Hit���̍d��
	 * @param[in]	const int	Guard���̍d��
	 * @author      Suzuki N
	 * @date        24/10/31
	 */
	void CollisionSet(VampireModel* _model, const int _modelHandle, const int _centerFrame_right, const int _centerFrame_left, 
		const float _attackColRadius, const int _damage, const int hitStun, const int guardStun, AttackAttribute _attribute);

	/**
	 * @brief		�R���W������؂�
	 * @author      Suzuki N
	 * @date        24/10/31
	 */
	void CollisionDisable() { model->attackCol->active = false; }

	/**
	 * @brief		�R���W����������
	 * @author      Suzuki N
	 * @date        24/10/31
	 */
	void CollisionEnable() { model->attackCol->active = true; }


#pragma region �I�[�o���C�h�֐�


	/**
	 * @brief		�C���X�^���X�������Ƃ��ɌĂ΂�郁�\�b�h
	 * @author      Suzuki N
	 * @date        24/10/31
	 */
	void Awake() override;

	/**
	 * @brief		��F�Ă΂�郁�\�b�h
	 * @author      Suzuki N
	 * @date        24/10/31
	 */
	void Update() override;

	/**
	 * @brief		�g���K�[�R���C�_�[�ƏՓ˂����u�ԂɌĂ΂�郁�\�b�h
	 * @author      Suzuki N
	 * @date        24/10/31
	 */
	void OnTriggerEnter(HWCollider& other)override;

#pragma endregion

};

