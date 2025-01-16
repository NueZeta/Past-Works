#include "Stage.h"

/**
* @author   Suzuki N
* @date     24/10/02
* @note		Stage�̎����t�@�C��
*/


Stage::Stage(Player* _player)
{
	player = _player;
}

Stage::~Stage()
{
    DeleteLightHandle(lightHandle);
}

void Stage::Awake()
{
	skyBoxModelHandle = MV1LoadModel("Assets/Stage/No.1/skyBox.mv1");
}

void Stage::Start()
{
    transform->position = player->player->transform->position;
    gameObject->SetParent(player->player.get());

    transform->scale = VGet(1000000.f, 1000000.f, 1000000.f);

    gameObject->priority = 100;


    // �t�H�O�Ɋւ���
    //SetFogEnable(TRUE);					// �t�H�O��L���ɂ���
    //SetFogColor(128, 128, 128);			// �t�H�O�̐F�ɂ���
    //SetFogStartEnd(9000.0f, 10000.0f);	// �t�H�O�̊J�n����

    transform->position = VAdd(player->player->transform->position,
        VGet(-4000,-200,0));


    // ���C�g�̐ݒ�
    SetLightEnable(false);
    lightHandle = CreatePointLightHandle(transform->position, 15000.00, 1.f, 0.0f, 0.0f);

    SetCameraNearFar(0.0f, 100);
}

void Stage::Update()
{
    // ���C�g�̈ʒu��ύX
    //SetLightPositionHandle(lightHandle, transform->position);


    // �J�����ʒu�ɃX�J�C�{�b�N�X��Ǐ]������
    //MV1SetPosition(skyBoxModelHandle, transform->position);

    // �X�J�C�{�b�N�X�̕`��
    MV1DrawModel(skyBoxModelHandle);


    //DrawFormatString(10, 50, GetColor(0, 255, 0), "%.2f, %.2f, %.2f", 
    //    player->controller->transform->position.x, player->controller->transform->position.y,
    //    player->controller->transform->position.z);

    //DrawFormatString(10, 70, GetColor(0, 255, 0), "%.2f, %.2f, %.2f", 
    //    transform->position.x, transform->position.y,
    //    transform->position.z);

}
