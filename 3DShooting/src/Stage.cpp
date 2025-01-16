#include "Stage.h"

/**
* @author   Suzuki N
* @date     24/10/02
* @note		Stageの実装ファイル
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


    // フォグに関する
    //SetFogEnable(TRUE);					// フォグを有効にする
    //SetFogColor(128, 128, 128);			// フォグの色にする
    //SetFogStartEnd(9000.0f, 10000.0f);	// フォグの開始距離

    transform->position = VAdd(player->player->transform->position,
        VGet(-4000,-200,0));


    // ライトの設定
    SetLightEnable(false);
    lightHandle = CreatePointLightHandle(transform->position, 15000.00, 1.f, 0.0f, 0.0f);

    SetCameraNearFar(0.0f, 100);
}

void Stage::Update()
{
    // ライトの位置を変更
    //SetLightPositionHandle(lightHandle, transform->position);


    // カメラ位置にスカイボックスを追従させる
    //MV1SetPosition(skyBoxModelHandle, transform->position);

    // スカイボックスの描画
    MV1DrawModel(skyBoxModelHandle);


    //DrawFormatString(10, 50, GetColor(0, 255, 0), "%.2f, %.2f, %.2f", 
    //    player->controller->transform->position.x, player->controller->transform->position.y,
    //    player->controller->transform->position.z);

    //DrawFormatString(10, 70, GetColor(0, 255, 0), "%.2f, %.2f, %.2f", 
    //    transform->position.x, transform->position.y,
    //    transform->position.z);

}
