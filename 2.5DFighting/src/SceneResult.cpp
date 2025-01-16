#include "SceneResult.h"

/**
* @author   Suzuki N
* @date     24/10/01
* @note		SceneResult�̎����t�@�C��
*/


SceneResult::SceneResult(InputSystem* _input)
{
	// ���s���̃V�[���^�O
	sceneTag = SceneTag::Result;

	// �J�n������ۑ�
	flashingInterval = GetNowCount();



	// ���͌n��ݒ�
	{
		input = _input;
		// �L�[�������̃R�[���o�b�N��ݒ�
		callBackId = input->AddCallBack("Change", [&](InputAction::CallBackContext c) {
			if (c.state == InputState::Started) SceneChange(SceneTag::Title);
			});
	}

	// �t�H���g�f�[�^�ǂݍ���
	fontHandle = CreateFontToHandle(NULL, 32, 2, DX_FONTTYPE_ANTIALIASING_8X8);
}

SceneResult::~SceneResult()
{
	input->DeleteCallBack("Change", callBackId);
}

void SceneResult::Update()
{
	//
	// �������_�ŕ\������
	//
	if (GetNowCount() - flashingInterval < 500)
		DrawFormatStringToHandle(750, 1000, GetColor(0, 0, 0), fontHandle, "---- Press START button ----");
	else
		if (GetNowCount() - flashingInterval > 1000)
			flashingInterval = GetNowCount();
}
