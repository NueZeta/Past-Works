#pragma once
#include "SceneBase.h"
#include "Score.h"

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


public:
	// ���\�b�h

	// �R���X�g���N�^
	SceneTitle(InputSystem* _Input);

	// �f�X�g���N�^
	~SceneTitle() override;

	// ��F�Ă΂��֐�
	// �I�[�o���C�h���\�b�h
	void Update() override;
};

