#pragma once
#include "SceneBase.h"

// �ǉ��̓ǂݍ��� -------------------

#include "VampirePresenter.h"
#include "StagePresenter.h"
#include "UICanvas.h"

// ----------------------------------

/**
* @author   Suzuki N
* @date     24/10/01
* @note		SceneGame�̒�`�t�@�C��
*/


/**
 * @class	SceneGame
 * @brief   ���C���Q�[���V�[��
 */
class SceneGame : public SceneBase 
{
private:
	//�����o�ϐ�
	
	//! �X�e�[�W�I�u�W�F�N�g
	std::unique_ptr<HWGameObject> stage;
	//! �X�e�[�W�̊Ǘ��R���|�[�l���g
	StagePresenter* stagePresenter;
	//! �L�����N�^�[1
	std::unique_ptr<HWGameObject> player_1;
	//! �L�����N�^�[1�̊Ǘ��R���|�[�l���g
	VampirePresenter* player_1_presenter;
	//! �L�����N�^�[2
	std::unique_ptr<HWGameObject> player_2;
	//! �L�����N�^�[2�̊Ǘ��R���|�[�l���g
	VampirePresenter* player_2_presenter;
	//! UI�L�����o�X
	std::unique_ptr<UICanvas> canvas;

	//! �|�C���g���C�g�n���h��
	int pointLightHandle_1;
	//! �|�C���g���C�g�n���h��
	int pointLightHandle_2;
	//! �|�C���g���C�g�n���h��
	int pointLightHandle_3;
	//! �|�C���g���C�g�n���h��
	int pointLightHandle_4;
	//! �X�|�b�g���C�g�n���h��(Player�̏㕔�ɐݒu����)
	int spotLightHandle;


	//! �t�H���g�f�[�^
	int fontHandle;


public:
	// ���\�b�h

	// �R���X�g���N�^
	SceneGame(InputSystem* _input);

	// �f�X�g���N�^
	~SceneGame() override;

	// ��F�Ă΂��֐�
	// �I�[�o���C�h���\�b�h
	void Update() override;
};

