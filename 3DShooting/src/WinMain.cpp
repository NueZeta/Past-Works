// �����C�u�����ŕK�{�ɂȂ�C���N���[�h�t�@�C��
// "DxLib.h" ��include�����
#include "HandlerWaltanForDxLib.h"

#include "SceneManager.h"


// �v���O������ WinMain ����n�܂�܂�
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// DX���C�u�����̏��������������˂Ă���
	if (HandlerWaltan::Instance().Init() == -1)
	{
		return 0;
	}

	// ��: 1920, ����: 1080, �r�b�g�[�x: 32
	SetGraphMode(1920, 1080, 32);  
	// �E�C���h�E���[�h�ŋN��
	ChangeWindowMode(FALSE);       

	// �w�i
	SetBackgroundColor(255, 255, 255);

	// �f�v�X�o�b�t�@�iZ�o�b�t�@�j��L���ɂ���
	SetUseZBuffer3D(TRUE);
	// Z�o�b�t�@�ւ̏������݂�L���ɂ���
	SetWriteZBuffer3D(TRUE);

	// FPS���Œ�
	Time::SetTargetFPS(60);


	// �X�N���[���T�C�Y���擾����
	GetWindowSize(&GameManager::ScreenSizeX, &GameManager::ScreenSizeY);


	//! �n���h���[�⃉�C�t�T�C�N���Ɋ�Â����^�C�~���O�Ń��\�b�h�������I�ɌĂяo���I�u�W�F�N�g
	//! �V���O���g���Ő݌v����Ă��邽�߁A�ȉ��̕��@�ȊO�ŃC���X�^���X���擾���邱�Ƃ͂ł��Ȃ�
	HandlerWaltan& HW = HandlerWaltan::Instance();

#if DEBUG

	// �f�o�b�O�p���[�h�ŋN������
	HW.debugMode = true;

#endif // DEBUG


	//! �V�[���Ǘ��p�̃N���X�̃C���X�^���X���擾
	SceneManager sceneManager = SceneManager::Instance();

	// �ÓI�N���X�̏�����
	SceneGame::Init();
	HWGameObject::GetGameObjects();

	// ���C�����[�v
	while (ProcessMessage() == 0)
	{
		//����ʏ���
		ClearDrawScreen();
		//�`���𗠉�ʂ�
		SetDrawScreen(DX_SCREEN_BACK);

		// �S�Ă�Update���\�b�h��S�ČĂяo��
		HW.Update();

		// �e�V�[�������s����
		sceneManager.Update();

		if (SceneManager::isEnd)
			break;


		//����ʂ�\��ʂɃR�s�[
		ScreenFlip();
	}

	// �\�t�g�̏I�� 
	HandlerWaltan::End();

	return 0;
}