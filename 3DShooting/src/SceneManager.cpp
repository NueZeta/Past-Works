#include "SceneManager.h"

/**
* @author   Suzuki N
* @date     24/10/01
* @note		SceneManager�̎����t�@�C��
*/

bool SceneManager::isEnd = false;

SceneManager::SceneManager()
{
	// �G���[�l�����Ă���
	crrSceneTag = SceneTag::NotFound;

	// ���͌n�̏�����
	{
		sysInput = new InputSystem();
		// escape�L�[�ŏI��
		{
			sysInput->AddKeyCode("close", KEY_INPUT_ESCAPE);
			sysInput->AddCallBack("close", [&](InputAction::CallBackContext context) { isEnd = true; });
		}
	}

	// �ŏ��̃V�[��
	SceneChange(SceneTag::Title);
}

SceneManager::~SceneManager()
{
	delete sysInput;
}

void SceneManager::Update()
{
	crrScene->Update();

	// �V�[�����őJ�ڎw���������ꍇ
	if (!(crrScene->nextSceneTag == SceneTag::NotFound ||
		crrScene->nextSceneTag == crrSceneTag))
		SceneChange(crrScene->nextSceneTag);
}

void SceneManager::SceneChange(const SceneTag& _nextSceneTag)
{
	// �J�ڎw���̗����^�O�����s���̃V�[���Ɠ������ANotFound�������ꍇ�͂��̂܂܏I��
	if (_nextSceneTag == crrSceneTag || _nextSceneTag == SceneTag::NotFound)
		return;

	// �^�O�ɂ���đJ�ڐ�̃V�[����ύX����
	switch (_nextSceneTag)
	{
	case SceneTag::Title:
		// �����I�Ɍ��݂̃V�[����delete����
		delete(crrScene);
		crrScene = new SceneTitle(sysInput);
		break;

	case SceneTag::Game:
		// �����I�Ɍ��݂̃V�[����delete����
		delete(crrScene);
		crrScene = new SceneGame(sysInput);
		break;

	case SceneTag::Result:
		// �����I�Ɍ��݂̃V�[����delete����
		delete(crrScene);
		crrScene = new SceneResult(sysInput);
		break;

		/*
		// Scene�𑝂₷�ۂ́A������SceneBase.h�ɂ���SceneTag�ɒǉ��ŋL�q����

	case SceneTag:: :
		crrScene = new �ǉ��V�[��();
		break;
		*/
	}

	// �V�[���^�O���X�V
	crrSceneTag = _nextSceneTag;
}

