#include "SceneGame.h"

/**
* @author   Suzuki N
* @date     24/10/01
* @note		SceneGame�̎����t�@�C��
*/


//
// �ÓI�ϐ��̏���������
//

// �ŏ���pause��Ԃ���n�܂�
GameParam GameManager::param = GameParam::SetUp;
// �Q�[���J�n�������L�^
int GameManager::startTime = GetNowCount();
// ��ʃT�C�Y
int GameManager::screenWidth = 1920;
int GameManager::screenHeight = 1080;
// ���@���p�C�A�̔�ѓ���̃G�t�F�N�g�n���h��
int VampireModel::projectileEffectHandle = -1;


SceneGame::SceneGame(InputSystem* _input)
{
	// ���s���̃V�[���^�O
	sceneTag = SceneTag::Game;


	// ���͌n��ݒ�
#ifdef DEBUG
	{
		input = _input;
		// �L�[�������̃R�[���o�b�N��ݒ�
		callBackId = input->AddCallBack("Change", [&](InputAction::CallBackContext c) {
			if (c.state == InputState::Started) SceneChange(SceneTag::Result);
			});
	}
#endif // DEBUG


	// ���C�g�֌W
	{
		SetLightEnable(false);
		pointLightHandle_1 = CreatePointLightHandle(VGet(0, 0, 1000), 2000.0f, 0.0001f, 0.008f, 0.000f);
		pointLightHandle_2 = CreatePointLightHandle(VGet(0, 00000, -15000), 1500000.0f, 0.005f, 0.00008f, 0.000f);
		pointLightHandle_3 = CreatePointLightHandle(VGet(10000, 10000, -15000), 1500000.0f, 0.001f, 0.00006f, 0.000f);
		pointLightHandle_4 = CreatePointLightHandle(VGet(-10000, 10000, -15000), 1500000.0f, 0.001f, 0.00006f, 0.000f);
	}


	// ���@���p�C�A�̔�ѓ���̃G�t�F�N�g��ǂݍ���ł���
	VampireModel::projectileEffectHandle = LoadEffekseerEffect("Assets/Effect/FireBall.efkefc", 50.f);


	// �L�����N�^�[1 �̐���
	{
		player_1 = std::make_unique<HWGameObject>("Player_1");
		player_1_presenter = player_1->AddComponent<VampirePresenter>();
		player_1->transform->position = VGet(400, GROUND,0);
		player_1->transform->rotate = VGet(0, -90, 0);
	}
	// �L�����N�^�[2 �̐���
	{
		player_2 = std::make_unique<HWGameObject>("Player_2");
		player_2_presenter = player_2->AddComponent<VampirePresenter>();
		player_2->transform->position = VGet(800, GROUND, 0);
		player_2->transform->rotate = VGet(0, 90, 0);
	}

	// ���ꂼ��ɑ����GameObject�̏���^����
	player_1_presenter->opponent = player_2.get();
	player_2_presenter->opponent = player_1.get();


	// �X�e�[�W�̏�����
	{
		stage = std::make_unique<HWGameObject>("traningStage", 100);
		stagePresenter = stage->AddComponent<StagePresenter>();
		stagePresenter->Initialize(player_1_presenter, player_2_presenter);
	}

	// UI�L�����o�X�̍쐬
	{
		canvas = std::make_unique<UICanvas>();
	}

	// �t�H���g�f�[�^�ǂݍ���
	fontHandle = CreateFontToHandle(NULL, 32, 2, DX_FONTTYPE_ANTIALIASING_8X8);

	
	// �e��t���O�̏�����
	GameManager::startTime = GetNowCount();

	// FPS���Œ�
	Time::SetTargetFPS(120);

	//! �Q�[���p�����[�^��ύX����
	GameManager::param = GameParam::SetUp;
}

SceneGame::~SceneGame()
{
#if DEBUG
	input->DeleteCallBack("Change", callBackId);
#endif // DEBUG

	DeleteLightHandleAll();

	// ��ѓ���̃G�t�F�N�g���폜
	DeleteEffekseerEffect(VampireModel::projectileEffectHandle);
}

void SceneGame::Update()
{
	if(HandlerWaltan::debugMode)
	{
		DrawFormatString(10, 50, GetColor(255, 255, 255), "%d", player_1_presenter->model->param);
		DrawFormatString(10, 30, GetColor(255, 255, 255), "%d", player_1_presenter->model->crrInputParam);
		DrawFormatString(100, 30, GetColor(255, 255, 255), "%d", player_1_presenter->transform->position.x);

		for (int i = 0; i < player_1_presenter->model->keyHistory.size(); ++i)
		{
			int y = i < 15 ? 20 : 70;
			int x = i < 15 ? 70 + 20 * i : 70 + 20 * (i - 15);

			DrawFormatString(x, y, GetColor(255, 255, 255), "%d", player_1_presenter->model->keyHistory[i]);
		}

		DrawFormatString(430, 50, GetColor(255, 255, 255), "%d", player_2_presenter->model->param);

		for (int i = 0; i < player_2_presenter->model->keyHistory.size(); ++i)
		{
			int y = i < 15 ? 20 : 70;
			int x = i < 15 ? 470 + 20 * i : 470 + 20 * (i - 15);

			DrawFormatString(x, y, GetColor(255, 255, 255), "%d", player_2_presenter->model->keyHistory[i]);
		}
	}

	// HUD�̕\��
	canvas->ManualUpdate(player_1_presenter->model->maxHp, player_1_presenter->model->hp,
		player_2_presenter->model->maxHp, player_2_presenter->model->hp);


	// Manager�̃p�����[�^��result�ɂȂ�����J��
	if ((GameManager::param & GameParam::Title) == GameParam::Title)
		SceneChange(SceneTag::Title);
}
