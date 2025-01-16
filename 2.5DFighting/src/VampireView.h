#pragma once
#include "GameManager.h"

/**
* @author   Suzuki N
* @date     24/10/29
* @note		VampireView�̒�`�t�@�C��
*/


/**
 * @class	VampireView
 * @brief   �L�����N�^�[1�̃r���[�R���|�[�l���g
 */
class VampireView : public HWComponent
{
public:
	//  �����o�ϐ�

	//! ���f���n���h��
	int modelHandle;
	//! �A�j���[�V��������R���|�[�l���g
	HWAnimator* animator;
	//! �f�t�H���g�̃A�j���[�V�����u�����h�X�s�[�h
	float defaultBlendSpeed = 0.3f;

	//! �������U���̔������ɌĂ΂�郁�\�b�h
	std::function<void()> stHaOccursCallback;
	//! �������U���̔����I�����ɌĂ΂�郁�\�b�h
	std::function<void()> stHaFinishedCallback;
	//! ������U���̔������ɌĂ΂�郁�\�b�h
	std::function<void()> stLaOccursCallback;
	//! ������U���̔����I�����ɌĂ΂�郁�\�b�h
	std::function<void()> stLaFinishedCallback;
	//! �����U���̔������ɌĂ΂�郁�\�b�h
	std::function<void()> crHaOccursCallback;
	//! �����U���̔����I�����ɌĂ΂�郁�\�b�h
	std::function<void()> crHaFinishedCallback;
	//! ����U���̔������ɌĂ΂�郁�\�b�h
	std::function<void()> crLaOccursCallback;
	//! ����U���̔����I�����ɌĂ΂�郁�\�b�h
	std::function<void()> crLaFinishedCallback;

	//! �g�����̔������ɌĂ΂�郁�\�b�h
	std::function<void()> sp1OccursCallback;
	//! �������̔������ɌĂ΂�郁�\�b�h
	std::function<void()> sp2OccursCallback;
	//! �������̔����I�����ɌĂ΂�郁�\�b�h
	std::function<void()> sp2FinishedCallback;

	//! �U���A�j���[�V�����I�����ɌĂ΂��R�[���o�b�N
	std::function<void()> attackEndCallBack;
	//! �K�[�h�A�j���[�V�����I�����ɌĂ΂��R�[���o�b�N
	std::function<void()> guardEndCallBack;
	//! �q�b�g�A�j���[�V�����I�����ɌĂ΂��R�[���o�b�N
	std::function<void()> hitEndCallBack;
	//! ���n���ɌĂ΂��R�[���o�b�N
	std::function<void()> landingCallBack;


public:
	// �����o�֐�

	/**
	 * @brief		�����I�ɌĂԕK�v�̂��鏉�������\�b�h
	 * @author      Suzuki N
	 * @date        24/10/29
	 */
	void Initialize();
};

