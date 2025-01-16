#include "SceneManager.h"

/**
* @author   Suzuki N
* @date     24/11/20
* @note		SceneManager�̎����t�@�C��
*/


SceneManager::SceneManager()
{
	// �G���[�l�����Ă���
	crrSceneTag = SceneTag::NotFound;
	// ���[�h�X�e�[�^�X�̏�����
	atomicLoadState = SceneLoadState::Wait;

	// �Q�[���I���p�̓���
	{
		input = new InputSystem();
		// �L�[��o�^
		// �L�[�{�[�h�� Escape
		input->AddKeyCode("sys", KEY_INPUT_ESCAPE, InputType::Key);
		// Pad�� Start
		input->AddKeyCode("sys", PAD_INPUT_11, InputType::Pad1);
		// �R�[���o�b�N
		input->AddCallBack("sys", [&](InputAction::CallBackContext context) { HandlerWaltan::End(); exit(0); });
	}
	// �V�[���J�ڗp
	{
		// ����̃L�[�Ŏ��̃V�[���ֈڍs����悤�ɂ���
		// �L�[�{�[�h�� R
		input->AddKeyCode("Change", KEY_INPUT_RETURN, InputType::Key);
		// Pad�� BACK
		input->AddKeyCode("Change", PAD_INPUT_8, InputType::Pad1);
		// Pad�� BACK
		input->AddKeyCode("Change", PAD_INPUT_8, InputType::Pad2);
	}


	// �ŏ��̃V�[��
	SceneChangeSync(SceneTag::Title);
}


void SceneManager::Update()
{
	crrScene->Update();

	// �񓯊��ŃV�[����ǂݍ���ł���Œ�
	if (atomicLoadState.load() == SceneLoadState::Loading)
	{
		DrawFormatString(100, 300, GetColor(0, 255, 0), "Loading...");
	}


	// �񓯊��̓ǂݍ��݂���������
	if (atomicLoadState.load() == SceneLoadState::Completed)
	{
		// �V�[�����㏑��
		std::swap(crrScene, loadScene);
		// �^�O���ύX
		crrSceneTag = loadScene->sceneTag;
		crrScene->nextSceneTagAsync = SceneTag::NotFound;
		//�@�ǂݍ��݃f�[�^���폜
		delete loadScene;
		// �X���b�h���J��
		sceneLoadThread.detach();
		// �ǂݍ��݃X�e�[�^�X��ύX
		atomicLoadState.store(SceneLoadState::Wait);
	}

	// �V�[�����őJ�ڎw���������ꍇ
	if (!(crrScene->nextSceneTag == SceneTag::NotFound ||
		crrScene->nextSceneTag == crrSceneTag))
		SceneChangeSync(crrScene->nextSceneTag);

	// �V�[�����Ŕ񓯊��ōs���J�ڎw���������ꍇ
	if (!(crrScene->nextSceneTagAsync == SceneTag::NotFound ||
		crrScene->nextSceneTagAsync == crrSceneTag))
		SceneChangeAsync(crrScene->nextSceneTagAsync);
}


void SceneManager::SceneChangeSync(const SceneTag& _nextSceneTag)
{
	// �J�ڎw���̗����^�O�����s���̃V�[���Ɠ������ANotFound�������ꍇ�͂��̂܂܏I��
	if (_nextSceneTag == crrSceneTag || _nextSceneTag == SceneTag::NotFound)
		return;

	// ! �J�ڐ�̃V�[���^�O���L�����Ă���(�Q�ƌ^�Ŏ����Ă��邽��)
	const SceneTag nextSceneTag = _nextSceneTag;

	// ���s���̃V�[�����폜
	if(crrScene != nullptr)
		delete(crrScene);

	// �^�O�ɂ���đJ�ڐ�̃V�[����ύX����
	switch (nextSceneTag)
	{

	case SceneTag::Title:
		crrScene = new SceneTitle();
		break;

	case SceneTag::Game:
		crrScene = new SceneGame();
		break;

	case SceneTag::Result:
		crrScene = new SceneResult();
		break;

		/*
		// Scene�𑝂₷�ۂ́A������SceneBase.h�ɂ���SceneTag�ɒǉ��ŋL�q����

	case SceneTag:: :
		crrScene = new �ǉ��V�[��();
		break;
		*/
	}


	// �V�[���^�O���X�V
	crrSceneTag = nextSceneTag;
}


void SceneManager::SceneChangeAsync(const SceneTag& _nextSceneTag)
{
	// �V�[���ǂݍ��ݒ��̏ꍇ�A�w���𖳌�
	if (sceneLoadThread.joinable() || atomicLoadState.load() != SceneLoadState::Wait) return;
	// �J�ڎw���̗����^�O�����s���̃V�[���Ɠ������ANotFound�������ꍇ�͂��̂܂܏I��
	if (_nextSceneTag == crrSceneTag || _nextSceneTag == SceneTag::NotFound) return;

	// �V�[���ǂݍ��݊J�n
	sceneLoadThread = std::thread(&SceneManager::SceneLoad, this, _nextSceneTag);
}


void SceneManager::SceneLoad(const SceneTag& _nextSceneTag)
{
	// �V�[���ǂݍ��݊����̃t���O��܂��Ă���
	atomicLoadState.store(SceneLoadState::Loading);

	//! �J�ڐ�̃V�[���^�O���L�����Ă���(�Q�ƌ^�Ŏ����Ă��邽��)
	const SceneTag nextSceneTag = _nextSceneTag;

	// �^�O�ɂ���đJ�ڐ�̃V�[����ύX����
	switch (nextSceneTag)
	{

	case SceneTag::Title:
		loadScene = new SceneTitle();
		break;

	case SceneTag::Game:
		loadScene = new SceneGame();
		break;

	case SceneTag::Result:
		loadScene = new SceneResult();
		break;
	}

	// �ǂݍ��݊���
	atomicLoadState.store(SceneLoadState::Completed);
}


