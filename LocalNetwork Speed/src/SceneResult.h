#pragma once
#include "SceneBase.h"

/**
* @author   Suzuki N
* @date     24/11/20
* @note		SceneResult�̒�`�t�@�C��
*/


/**
 * @class	SceneResult
 * @brief   ���U���g�V�[��
 */
class SceneResult : public SceneBase
{
private:
	// �����o�ϐ�


public:
	// ���\�b�h

	/**
	 * @brief       �R���X�g���N�^
	 * @author      Suzuki N
	 * @date        24/11/20
	 */
	SceneResult();

	/**
	 * @brief       �f�X�g���N�^
	 * @author      Suzuki N
	 * @date        24/11/20
	 */
	~SceneResult() override;

	/**
	 * @brief       ��F�Ă΂�郁�\�b�h
	 * @author      Suzuki N
	 * @date        24/11/20
	 */
	void Update() override;
};

