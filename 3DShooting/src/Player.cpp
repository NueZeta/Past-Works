#include "Player.h"

/**
* @author   Suzuki N
* @date     24/10/02
* @note		Playerの実装ファイル
*/


Player::Player()
{
	input = std::make_shared<InputSystem>();

	// Playerオブジェクトの設定
	{
		player = std::make_unique<HWGameObject>("ド・ダイ");
		player->tag = (int)Tag::player;
		// 必要なコンポーネントをアタッチする
		player->AddComponent<HWRenderer>("Assets/Player/do・dai.mv1");
		// キャラクター操作のコンポーネントをアタッチする
		controller = player->AddComponent<PlayerController>(input);
		// カプセルコライダーをアタッチ
		capsuleCol = player->AddComponent<HWCapsuleCollider>();
		capsuleCol->radius = PLAYER_COLLIDR_RADIUS;
		capsuleCol->isTrigger = true;
		// コントローラーの設定
		controller->capsuleCol = capsuleCol;
		controller->modelHandle = player->GetComponent<HWRenderer>()->GetModelHandle();
	}
	

	// カメラオブジェクトの設定
	{
		camera = std::make_unique<HWGameObject>("Camera");
		//camera->AddComponent<HWCamera>();
		// playerオブジェクトの子オブジェクトにする
		camera->SetParent(player.get());
		// カメラの初期座標の設定
		camera->transform->position = VAdd(player->transform->position, CAMERA_DEFAULT_POSITION);
	}
}

Player::~Player()
{
	camera.reset();
	player.reset();
}
