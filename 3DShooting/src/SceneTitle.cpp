#include "SceneTitle.h"

/**
* @author   Suzuki N
* @date     24/10/01
* @note		SceneTitle�̎����t�@�C��
*/


SceneTitle::SceneTitle(InputSystem* _Input)
{
	// ���s���̃V�[���^�O
	sceneTag = SceneTag::Title;

	// SceneManager�̃V�X�e���nInputSystem���󂯎��
	sysInput = _Input;
	// �V�[���J�ڗp�R�[���o�b�N�֐���o�^
	// R �L�[�ŃV�[���J��
	{
		sysInput->AddKeyCode("sceneChange", KEY_INPUT_R);
		callBackId = sysInput->AddCallBack("sceneChange", [&](InputAction::CallBackContext context)
			{
				if (context.state == InputState::Started)
					SceneChange(SceneTag::Game);
			});
	}
}

SceneTitle::~SceneTitle()
{
	sysInput->DeleteCallBack("sceneChange", callBackId);
}

void SceneTitle::Update()
{
	DrawFormatString(10, 50, GetColor(0, 0, 0), "SceneTitle");
	DrawFormatString(10, 70, GetColor(0, 0, 0), "R ��Game");

	DrawFormatString(GameManager::ScreenSizeX / 2 - 10, 70, GetColor(0, 0, 0), "�������");
	DrawFormatString(GameManager::ScreenSizeX / 2 + 10, 130, GetColor(0, 0, 0), "W");
	DrawFormatString(GameManager::ScreenSizeX / 2 - 50, 170, GetColor(0, 0, 0), "A    �ړ�    S");
	DrawFormatString(GameManager::ScreenSizeX / 2 + 10, 210, GetColor(0, 0, 0), "D");

	DrawFormatString(GameManager::ScreenSizeX / 2 - 10, 250, GetColor(0, 0, 0), "�U�� : SPACE");

}
