#pragma once
#include "SceneBase.h"

/**
* @author   Suzuki N
* @date     24/10/01
* @note		SceneTitle�̒�`�t�@�C��
*/


/**
 * @class	SceneTitle
 * @brief   �^�C�g���V�[��
 */
class SceneTitle : public SceneBase
{
private:
	// �����o�ϐ�

	//! �^�C�g�����S�̃t�H���g�f�[�^
	int logoFontHandle;
	//! �������_�ł�����
	int flashingInterval;


public:
	// ���\�b�h

	// �R���X�g���N�^
	SceneTitle(InputSystem* _input);

	// �f�X�g���N�^
	~SceneTitle() override;

	// ��F�Ă΂��֐�
	// �I�[�o���C�h���\�b�h
	void Update() override;
};

