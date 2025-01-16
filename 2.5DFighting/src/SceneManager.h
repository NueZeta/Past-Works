#pragma once
#include "SceneTitle.h"
#include "SceneGame.h"
#include "SceneResult.h"

/**
* @author   Suzuki N
* @date     24/10/01
* @note		SceneManager�̒�`�t�@�C��
*/


/**
 * @class	SceneManager
 * @brief   �V�[���̎��s�A�J�ڂ��s���N���X
 * @detail	�V���O���g���Ő݌v����Ă��邽�߁A�C���X�^���X���쐬�ł��܂���
 */
class SceneManager
{
private:
	// �����o�ϐ�

	//! ���s���̃V�[���^�O
	SceneTag crrSceneTag;
	//! ���s���̃V�[���̃C���X�^���X
	SceneBase* crrScene;
	//! �V�[���J�ځA�Q�[���I���p�̓���
	InputSystem* input;

public:

	//! �V�X�e���I���t���O
	bool isEnd = false;


public:
	// �����o�֐�

	// �C���X�^���X���擾����
	static SceneManager& Instance()
	{
		static SceneManager* instance = new SceneManager();
		return *instance;
	}

	// ���s���̃V�[���̃^�O���擾
	const SceneTag& GetCrrSceneTag()const { return crrSceneTag; }

	// ��F�Ă΂��֐�
	void Update();

	// �V�[����ύX����
	void SceneChange(const SceneTag& _nextSceneTag);

private:
	// �R���X�g���N�^�͖����I�ɍ폜
	SceneManager();
};

