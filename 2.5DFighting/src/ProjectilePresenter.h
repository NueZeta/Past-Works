#pragma once
#include "ProjectileModel.h"
#include "ProjectileView.h"
#include "VampirePresenter.h"

/**
* @author   Suzuki N
* @date     24/11/05
* @note		ProjectilePresenter�̒�`�t�@�C��
*/


/**
 * @class	ProjectilePresenter
 * @brief   ��ѓ���̍U������̊Ǘ��N���X
 */
class ProjectilePresenter : public HWComponent
{
public:
	//  �����o�ϐ�

	//! ���f���N���X
	std::unique_ptr <ProjectileModel> model;
	//! �r���[�R���|�[�l���g
	ProjectileView* view;


public:
	// �����o�֐�

	/**
	 * @brief		�R���W��������ݒ肷��
	 * @param[in]	VampireModel*	���g�̃��f��
	 * @param[in]	const int	���f���n���h��
	 * @param[in]	const int	�G�t�F�N�g�n���h��
	 * @param[in]	const VECTOR ���W
	 * @param[in]	const float	�����蔻��̔��a
	 * @param[in]	const int	Hit���̃_���[�W
	 * @param[in]	const int	Hit���̍d��
	 * @param[in]	const int	Guard���̍d��
	 * @param[in]	const float	�ړ��X�s�[�h
	 * @author      Suzuki N
	 * @date        24/10/31
	 */
	void CollisionSet(VampireModel* _model, const int _effecthandle, const VECTOR _pos, const float _attackColRadius,
		const int _damage, const int hitStun, const int guardStun, const float _speed, AttackAttribute _attribute);

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
	 * @brief		�폜���ɌĂ΂�郁�\�b�h
	 * @author      Suzuki N
	 * @date        24/10/31
	 */
	void OnDestroy() override;


	/**
	 * @brief		�g���K�[�R���C�_�[�ƏՓ˂����u�ԂɌĂ΂�郁�\�b�h
	 * @author      Suzuki N
	 * @date        24/10/31
	 */
	void OnTriggerEnter(HWCollider& other)override;

#pragma endregion

};

