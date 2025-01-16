#pragma once
#include "GameManager.h"

/**
* @author   Suzuki N
* @date     24/11/05
* @note		StageView�̒�`�t�@�C��
*/


/**
 * @class	StageView
 * @brief   �X�e�[�W�I�u�W�F�N�g�̃r���[�R���|�[�l���g
 */
class StageView : public HWComponent
{
public:
	// �����o�ϐ�

	//! ���f���n���h��
	int modelHandle;
	//! �����_���[
	HWRenderer* renderer;


	// ���\�b�h

	/**
	 * @brief		�����I�ɌĂԕK�v�̂��鏉�������\�b�h
	 * @author      Suzuki N
	 * @date        24/11/05
	 */
	void Initialize();
};

