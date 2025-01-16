#include "SceneManager.h"



// �v���O������ WinMain ����n�܂�܂�
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// DX���C�u�����̏��������������˂Ă���
	if (HandlerWaltan::Instance().Init() == -1)
		return 0;


#ifdef DEBUG

	// ��: 1920, ����: 1080, �r�b�g�[�x: 32
	SetGraphMode(1920 / 2, 1080 / 2, 32);
	ChangeWindowMode(TRUE);
	// �f�o�b�O���[�h�ŋN��
	HandlerWaltan::debugMode = true;

#else

	// ��: 1920, ����: 1080, �r�b�g�[�x: 32
	SetGraphMode(1920, 1080, 32);
	// �E�C���h�E���[�h�ŋN��
	ChangeWindowMode(FALSE);
	// ��f�o�b�O���[�h�ŋN��
	HandlerWaltan::debugMode = false;

#endif // DEBUG


	// �f�v�X�o�b�t�@�iZ�o�b�t�@�j��L���ɂ���
	SetUseZBuffer3D(TRUE);
	// Z�o�b�t�@�ւ̏������݂�L���ɂ���
	SetWriteZBuffer3D(TRUE);

	// FPS���Œ�
	Time::SetTargetFPS(60);


	//! �n���h���[�⃉�C�t�T�C�N���Ɋ�Â����^�C�~���O�Ń��\�b�h�������I�ɌĂяo���I�u�W�F�N�g
	//! �V���O���g���Ő݌v����Ă��邽�߁A�ȉ��̕��@�ȊO�ŃC���X�^���X���擾���邱�Ƃ͂ł��Ȃ�
	HandlerWaltan& HW = HandlerWaltan::Instance();

	//! �V�[���}�l�[�W���[�̃C���X�^���X���擾
	SceneManager& sceneMgr = SceneManager::Instance();


	// ���C�����[�v
	while (ProcessMessage() == 0)
	{
		//����ʏ���
		ClearDrawScreen();
		//�`���𗠉�ʂ�
		SetDrawScreen(DX_SCREEN_BACK);


		// �S�Ă�Update���\�b�h��S�ČĂяo��
		HW.Update();

		// �V�[�����X�V
		sceneMgr.Update();

		// �V�X�e���I���̃t���O����������A���̂܂܏I��
		if (sceneMgr.isEnd) break;


		//����ʂ�\��ʂɃR�s�[
		ScreenFlip();
	}

	// �\�t�g�̏I�� 
	HandlerWaltan::End();

	return 0;
}