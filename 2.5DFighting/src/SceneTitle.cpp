#include "SceneTitle.h"

/**
* @author   Suzuki N
* @date     24/10/01
* @note		SceneTitle�̎����t�@�C��
*/


SceneTitle::SceneTitle(InputSystem* _input)
{
	// ���s���̃V�[���^�O
	sceneTag = SceneTag::Title;

	// �J�n������ۑ�
	flashingInterval = GetNowCount();


	// ���͌n��ݒ�
	{
		input = _input;
		// �L�[�������̃R�[���o�b�N��ݒ�
		callBackId = input->AddCallBack("Change", [&](InputAction::CallBackContext c) {
			if (c.state == InputState::Started) SceneChange(SceneTag::Game);
			});
	}


	// �t�H���g�f�[�^�ǂݍ���
	logoFontHandle = CreateFontToHandle(NULL, 32, 2, DX_FONTTYPE_ANTIALIASING_8X8);
	SetBackgroundColor(255, 255, 255);
}

SceneTitle::~SceneTitle()
{
	input->DeleteCallBack("Change", callBackId);
}

void SceneTitle::Update()
{
	DrawFormatStringToHandle(10, 50, GetColor(0, 0, 0), logoFontHandle, "Title");

	DrawFormatStringToHandle(880, 400, GetColor(0, 0, 0), logoFontHandle, "������@");
	DrawFormatStringToHandle(700, 500, GetColor(0, 0, 0), logoFontHandle, "X    :  ��U��       Y    : ���U��");
	DrawFormatStringToHandle(700, 550, GetColor(0, 0, 0), logoFontHandle, "���� :  �g����       ���� : ������");
	DrawFormatStringToHandle(700, 700, GetColor(0, 0, 0), logoFontHandle, "�U����Hit�������ɕK�E�Z�ŃL�����Z���\");

	//
	// �������_�ŕ\������
	//
	if(GetNowCount() - flashingInterval < 500)
		DrawFormatStringToHandle(750, 1000, GetColor(0, 0, 0), logoFontHandle, "---- Press START button ----");
	else
		if (GetNowCount() - flashingInterval > 1000)
			flashingInterval = GetNowCount();
}
