#pragma once
#include "SceneTitle.h"
#include "SceneGame.h"
#include "SceneResult.h"

/**
* @author   Suzuki N
* @date     24/11/20
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

	//! �񓯊��ŃV�[���̓ǂݍ��݂��s���X���b�h
	std::thread sceneLoadThread;
	//! �V�[�����[�h���������Ă��邩
	std::atomic<SceneLoadState> atomicLoadState;
	//! �񓯊��œǂݍ��񂾃V�[���̃C���X�^���X
	SceneBase* loadScene;


public:
	// �����o�֐�

	/**
	 * @brief       �V���O���g���C���X�^���X���擾����
	 * @detail		�C���X�^���X���������̏ꍇ�A�V���ɍ쐬����
	 * @author      Suzuki N
	 * @date        24/11/20
	 */
	static SceneManager& Instance()
	{
		static SceneManager* instance = new SceneManager();
		return *instance;
	}

	/**
	 * @brief       ���s���̃V�[���^�O���擾����
	 * @author      Suzuki N
	 * @date        24/11/20
	 */
	const SceneTag& GetCrrSceneTag()const { return crrSceneTag; }

	/**
	 * @brief       �����I�ɌĂяo���K�v�̂���Update����
	 * @author      Suzuki N
	 * @date        24/11/20
	 */
	void Update();

	/**
	 * @brief       ���������ŃV�[����ύX����
	 * @param[in]	const SceneTag& �J�ڐ�̃V�[���^�O
	 * @author      Suzuki N
	 * @date        24/11/20
	 */
	void SceneChangeSync(const SceneTag& _nextSceneTag);

	/**
	 * @brief       �񓯊������ŃV�[����ύX����
	 * @param[in]	const SceneTag& �J�ڐ�̃V�[���^�O
	 * @author      Suzuki N
	 * @date        24/11/20
	 */
	void SceneChangeAsync(const SceneTag& _nextSceneTag);

private:

	/**
	 * @brief       �V�[���ǂݍ���
	 * @param[in]	const SceneTag& �J�ڐ�̃V�[���^�O
	 * @author      Suzuki N
	 * @date        24/11/20
	 */
	void SceneLoad(const SceneTag& _nextSceneTag);


	// �R���X�g���N�^�͖����I�ɍ폜
	SceneManager();
};

