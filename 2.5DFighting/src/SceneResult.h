#pragma once
#include "SceneBase.h"

/**
* @author   Suzuki N
* @date     24/10/01
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

	//! �t�H���g�f�[�^
	int fontHandle;
	//! �������_�ł�����
	int flashingInterval;


public:
	// ���\�b�h

	// �R���X�g���N�^
	SceneResult(InputSystem* _input);

	// �f�X�g���N�^
	~SceneResult() override;

	// ��F�Ă΂��֐�
	// �I�[�o���C�h���\�b�h
	void Update() override;
};

