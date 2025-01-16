#pragma once
#include "SceneBase.h"
#include "Score.h"

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
	int highestScore = -1;


public:
	// ���\�b�h

	// �R���X�g���N�^
	SceneResult(InputSystem* _Input);

	// �f�X�g���N�^
	~SceneResult() override;

	// ��F�Ă΂��֐�
	// �I�[�o���C�h���\�b�h
	void Update() override;
};

