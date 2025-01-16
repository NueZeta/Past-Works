
#pragma comment(lib,"�v���W�F�N�g�ɒǉ����ׂ��t�@�C��/HandlerWaltanForDxLib_d.lib")


#include "SceneManager.h"


GameParameter GameManager::param = GameParameter::SetUp;
bool GameManager::isWin = false;
bool GameManager::isLose = false;
PlayerType GameManager::playerType = PlayerType::Host;
IPDATA GameManager::ip = {0,0,0};
int GameManager::port = -2;



int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// DX���C�u�����̏��������������˂Ă���
	if (HandlerWaltan::Instance().Init() == -1)
	{
		return 0;
	}


	SetUseZBuffer3D(TRUE);     // �f�v�X�o�b�t�@�iZ�o�b�t�@�j��L���ɂ���
	SetWriteZBuffer3D(TRUE);   // Z�o�b�t�@�ւ̏������݂�L���ɂ���

	SetGraphMode(1920, 1080, 16);
	ChangeWindowMode(TRUE);

	SetFontSize(30);


	//! �n���h���[�⃉�C�t�T�C�N���Ɋ�Â����^�C�~���O�Ń��\�b�h�������I�ɌĂяo���I�u�W�F�N�g
	//! �V���O���g���Ő݌v����Ă��邽�߁A�ȉ��̕��@�ȊO�ŃC���X�^���X���擾���邱�Ƃ͂ł��Ȃ�
	HandlerWaltan& HW = HandlerWaltan::Instance();

	//! �V�[���}�l�[�W���[
	SceneManager& SM = SceneManager::Instance();
	SM.SceneChangeSync(SceneTag::Title);

	// ���C�����[�v
	while (ProcessMessage() == 0)
	{
		//����ʏ���
		ClearDrawScreen();
		//�`���𗠉�ʂ�
		SetDrawScreen(DX_SCREEN_BACK);

		SM.Update();

		// �S�Ă�Update���\�b�h��S�ČĂяo��
		HW.Update();

		if (GameManager::isWin)
			DrawFormatString(500, 300, GetColor(255, 255, 255), "����");
		if (GameManager::isLose)
			DrawFormatString(500, 300, GetColor(255, 255, 255), "�s�k");

		//����ʂ�\��ʂɃR�s�[
		ScreenFlip();
	}

	// �\�t�g�̏I�� 
	HandlerWaltan::End();

	return 0;
}