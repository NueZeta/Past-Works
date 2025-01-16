#pragma once
#include "VampireModel.h"
#include "VampireView.h"
#include "AttackPresenter.h"
#include "ProjectilePresenter.h"
#include "StageModel.h"


/**
* @author   Suzuki N
* @date     24/10/29
* @note		VampirePresenter�̒�`�t�@�C��
*/


/**
 * @class	VampirePresenter
 * @brief   �L�����N�^�[1�̊Ǘ��N���X
 */
class VampirePresenter : public HWComponent
{
public:
	//  �����o�ϐ�

	//! ���f���N���X
	std::unique_ptr<VampireModel> model;
	//! �r���[�R���|�[�l���g
	VampireView* view;
	//! �����GameObject
	HWGameObject* opponent;

	
	// �����o�֐�
private:

	/**
	 * @brief		���݂̃p�����[�^���Q�Ƃ��āA�A�j���[�V�������Z�b�g����
	 * @author      Suzuki N
	 * @date        24/10/29
	 */
	void AnimChange();

	/**
	 * @brief		�ŐV�̓��͂��Q�Ƃ��ăp�����[�^���Z�b�g����
	 * @author      Suzuki N
	 * @date        24/10/29
	 */
	void ParameterSet();

	/**
	 * @brief		�R�}���h�K�E�Z���������Ă��邩�𒲂ׂ�
	 * @param[in]	const Parameter&  �������L�[
	 * @return		const Parameter�@���������A�N�V����
	 * @author      Suzuki N
	 * @date        24/10/31
	 */
	const Parameter CommandCheck(const Parameter& _param);

	/**
	 * @brief		���݂̃p�����[�^���Q�Ƃ��āA�ړ��������s��
	 * @author      Suzuki N
	 * @date        24/10/29
	 */
	void Move();

	/**
	 * @brief		���݂̃p�����[�^���W�����v���Ȃ�΍s���鏈��
	 * @author      Suzuki N
	 * @date        24/11/11
	 */
	void Jump();

	/**
	 * @brief		�U���A�j���[�V�����I�����ɌĂ΂�郁�\�b�h
	 * @author      Suzuki N
	 * @date        24/10/29
	 */
	void AttackAnimEnd();

	/**
	 * @brief		�K�[�h�A�j���[�V�����I�����ɌĂ΂�郁�\�b�h
	 * @author      Suzuki N
	 * @date        24/10/29
	 */
	void GuardAnimEnd();

	/**
	 * @brief		�q�b�g�A�j���[�V�����I�����ɌĂ΂�郁�\�b�h
	 * @author      Suzuki N
	 * @date        24/10/29
	 */
	void HitAnimEnd();

	/**
	 * @brief		�L�[���͎��ɌĂ΂��R�[���o�b�N
	 * @author      Suzuki N
	 * @date        24/10/29
	 */
	void OnKeyCheck(InputAction::CallBackContext& context);

	/**
	 * @brief		�̗͂�0�ɂȂ����ۂ̏���
	 * @author      Suzuki N
	 * @date        24/10/29
	 */
	void Dead();


	void Debug();

public:

	/**
	 * @brief		�U�����󂯂��ۂ̏���
	 * @param[in]	const AttackPresenter* Hit�����U�����
	 * @return		bool ? Hit����(true) : Guard���ꂽ(false)
	 * @author      Suzuki N
	 * @date        24/10/29
	 */
	bool AttackHit(const AttackPresenter* _attackPresenter);

	/**
	 * @brief		�U�����󂯂��ۂ̏���
	 * @param[in]	const ProjectilePresenter* Hit�����U�����
	 * @return		bool ? Hit����(true) : Guard���ꂽ(false)
	 * @author      Suzuki N
	 * @date        24/10/29
	 */
	bool AttackHit(const ProjectilePresenter* _attackPresenter);



#pragma region �I�[�o���C�h�֐�


	/**
	 * @brief		�C���X�^���X�������Ƃ��ɌĂ΂�郁�\�b�h
	 * @author      Suzuki N
	 * @date        24/10/29
	 */
	void Awake() override;

	/**
	 * @brief		��F�Ă΂�郁�\�b�h
	 * @author      Suzuki N
	 * @date        24/10/29
	 */
	void Update() override;

	/**
	 * @brief		�g���K�[�R���C�_�[�ƏՓ˂����u�ԂɌĂ΂�郁�\�b�h
	 * @author      Suzuki N
	 * @date        24/10/29
	 */
	void OnTriggerStay(HWCollider& other)override;

#pragma endregion

};

