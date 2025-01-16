#pragma once
#include "Define.h"

/**
* @author   Suzuki N
* @date     24/10/01
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
	//! �V�X�e���̓��͌n
	InputSystem* sysInput;
	//! �o�^�����V�[���`�F���W�p�R�[���o�b�N�֐���ID
	int callBackId;

	// �����o�֐�

	// �R���X�g���N�^
	SceneBase() : nextSceneTag(SceneTag::NotFound), callBackId(-1)
	{}

	// �V�[�������ŃV�[����J�ڂ���
	void SceneChange(const SceneTag _nextSceneTag)
	{
		nextSceneTag = _nextSceneTag;
	}

public:
	// �f�X�g���N�^
	// ���z�֐�
	virtual ~SceneBase() {};

	// ��F�Ă΂�郁�\�b�h
	// ���z�֐�
	virtual void Update() {};
};