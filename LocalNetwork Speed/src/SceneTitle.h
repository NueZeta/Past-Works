#pragma once
#include "SceneBase.h"

/**
* @author   Suzuki N
* @date     24/11/20
* @note		SceneTitle�̒�`�t�@�C��
*/


/**
 * @class	SceneTitle
 * @brief   �^�C�g���V�[��
 */
class SceneTitle : public SceneBase
{
private:

	bool isConnect = false;
	bool isConnected = false;
	int netHandle;
	int connectTime = 0;

public:
	// ���\�b�h

	/**
	 * @brief       �R���X�g���N�^
	 * @author      Suzuki N
	 * @date        24/11/20
	 */
	SceneTitle();

	/**
	 * @brief       �f�X�g���N�^
	 * @author      Suzuki N
	 * @date        24/11/20
	 */
	~SceneTitle() override;

	/**
	 * @brief       ��F�Ă΂�郁�\�b�h
	 * @author      Suzuki N
	 * @date        24/11/20
	 */
	void Update() override;
};

