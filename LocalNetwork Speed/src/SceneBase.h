#pragma once
#include "GameManager.h"

/**
* @author   Suzuki N
* @date     24/11/20
* @note		SceneBase�̒�`�t�@�C��
*/


/**
 * @enum	SceneTag
 * @brief   �V�[���̃^�O
 */
enum class SceneTag
{
	//! �^�C�g���V�[��(0)
	Title,
	//! �Q�[���V�[��(1)
	Game,
	//! ���U���g�V�[��(2)
	Result,

	/*
		�ǉ�����ꍇ�́A�����Ƀ^�O��ǉ����ASceneManager��SceneChange���\�b�h�ɒǋL����
	*/

	//! ���g�p (��ɖ���)
	NotFound = -1,
};


/**
 * @enum	SceneLoadState
 * @brief   �V�[�����[�h�̃X�e�[�^�X
 */
enum class SceneLoadState
{
	//! �ҋ@��(0)
	Wait,
	//! ���[�h��(1)
	Loading,
	//! ���[�h����(2)
	Completed,
};


/**
 * @class	SceneBase
 * @brief   �e�V�[���̂��ƂɂȂ���N���X
 * @detail	���z�N���X�̂��߁A�C���X�^���X���쐬�ł��Ȃ�
 */
class SceneBase
{
	friend class SceneManager;

protected:
	//  �����o�ϐ�

	//! �V�[���̃^�O
	SceneTag sceneTag;
	//! �J�ڐ�̃V�[���^�O
	SceneTag nextSceneTag;
	//! �񓯊��œǂݍ��ޑJ�ڐ�̃V�[���^�O
	SceneTag nextSceneTagAsync;
	//! SceneManager������InputSystem
	InputSystem* input;
	//! �V�[���J�ڂ̃R�[���o�b�N�֐���ID
	int callBackId;


	// �����o�֐�

	/**
	 * @brief       �R���X�g���N�^
	 * @author      Suzuki N
	 * @date        24/11/20
	 */
	SceneBase() : nextSceneTag(SceneTag::NotFound), nextSceneTagAsync(SceneTag::NotFound)
	{}

	/**
	 * @brief       �V�[��������V�[����ύX����
	 * @param[in]	const SceneTag �ύX��̃V�[���^�O
	 * @author      Suzuki N
	 * @date        24/11/20
	 */
	void SceneChange(const SceneTag _nextSceneTag)
	{
		nextSceneTag = _nextSceneTag;
	}
	/**
	 * @brief       �񓯊��ŃV�[��������V�[����ύX����
	 * @param[in]	const SceneTag �ύX��̃V�[���^�O
	 * @author      Suzuki N
	 * @date        24/11/20
	 */
	void SceneChangeAsync(const SceneTag _nextSceneTag)
	{
		nextSceneTagAsync = _nextSceneTag;
	}

public:

	/**
	 * @brief       �f�X�g���N�^
	 * @author      Suzuki N
	 * @date        24/11/20
	 */
	virtual ~SceneBase() {};

	/**
	 * @brief       ��F�Ă΂�郁�\�b�h
	 * @author      Suzuki N
	 * @date        24/11/20
	 */
	virtual void Update() {};
};