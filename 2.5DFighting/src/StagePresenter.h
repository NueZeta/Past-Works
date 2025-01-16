#pragma once
#include "GameManager.h"
#include "StageModel.h"
#include "StageView.h"
#include"VampirePresenter.h"

/**
* @author   Suzuki N
* @date     24/11/05
* @note		StagePresenter�̒�`�t�@�C��
*/


/**
 * @class	StagePresenter
 * @brief   �X�e�[�W�I�u�W�F�N�g�̃v���[���^�[�R���|�[�l���g
 */
class StagePresenter : public HWComponent
{
public:
	// �����o�ϐ�

	//! ���f��
	std::unique_ptr<StageModel> model;
	//! �r���[�R���|�[�l���g
	StageView* view;


	// ���\�b�h

	/**
	 * @brief		�����I�ɌĂԕK�v�̂��鏉�������\�b�h
	 * @author      Suzuki N
	 * @date        24/11/05
	 */
	void Initialize(VampirePresenter* _presenter1, VampirePresenter* _presenter2);



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

#pragma endregion

};

