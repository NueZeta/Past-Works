#include "PlayerController.h"

/**
* @author   Suzuki N
* @date     24/10/02
* @note		PlayerControllerの実装ファイル
*/


PlayerController::PlayerController(std::shared_ptr<InputSystem> _input)
	: collision_start(-1), collision_end(-1), muzzle_1(-1), muzzle_2(-1),
	booster_1(-1), booster_2(-1)
{
	// ステータスなどの初期化設定
	maxHp = hp = PLAYER_DEFAULR_MAXHP;
	// だいたい最初のほうの敵を1撃で倒せるぐらいの攻撃力
	attackPower = PLAYER_DEFAULT_ATTACKPOWER;
	// 上下移動は左右移動よりもやや遅め
	verticalSpeed = PLAYER_DEFAULT_SPEED_VERTICAL;
	// 左右移動は大単に速くしたほうがいいかも？
	horizonSpeed = PLAYER_DEFAULT_SPEED_HORIZON;
	isShootingDown = true;

	// 入力系の設定
	{
		input = _input;
		// 入力を感知するキーコードを登録
		input->AddKeyCode("move", { KEY_INPUT_W, KEY_INPUT_S, KEY_INPUT_D, KEY_INPUT_A, KEY_INPUT_SPACE });
		// 入力感知時に呼ばれるコールバック関数を設定
		input->AddCallBack("move", [&](InputAction::CallBackContext context)
			{
				if (GameManager::isStop || isCrushing) return;

				for (auto it = context.key.begin(); it != context.key.end(); ++it)
					if (it->inputState != InputState::Waiting)
						switch (it->keyCode)
						{
						case KEY_INPUT_W:
							Move(VGet(0, verticalSpeed, 0));
							break;

						case KEY_INPUT_S:
							Move(VGet(0, -verticalSpeed, 0));
							break;

						case KEY_INPUT_D:
							Move(VGet(horizonSpeed, 0, 0));
							break;

						case KEY_INPUT_A:
							Move(VGet(-horizonSpeed, 0, 0));
							break;

						case KEY_INPUT_SPACE:
							if(it->inputState == InputState::Started)
							{
								// 攻撃
								Firing(MV1GetFramePosition(modelHandle, muzzle_1));
								Firing(MV1GetFramePosition(modelHandle, muzzle_2));
							}
							break;
						}
			});
	}
}

PlayerController::~PlayerController()
{
	gunSightObj.reset();
	auto effect1 = boosterEf_1->GetComponent<HWEffect>();
	effect1->Stop();
	boosterEf_1.reset();
	auto effect2 = boosterEf_2->GetComponent<HWEffect>();
	effect2->Stop();
	boosterEf_2.reset();

	for (auto it = bulletVec.begin(); it != bulletVec.end(); ++it)
		delete* it;
}

void PlayerController::Awake()
{
	// 初期座標の設定
	gameObject->transform->position = PLAYER_DEFAULT_POSISION;
	gameObject->transform->rotate = PLAYER_DEFAULT_ROTATE;

	// ガンサイトオブジェクトの作成
	gunSightObj = std::make_unique<HWGameObject>("GunSight");
	sightCp = gunSightObj->AddComponent<GunSight>();
	// ガンサイトオブジェクトを自身の子オブジェクトにする
	gunSightObj->SetParent(gameObject);
}

void PlayerController::Start()
{
	collision_start = MV1SearchFrame(modelHandle, "Collision_Start");
	collision_end = MV1SearchFrame(modelHandle, "Collision_End");

	muzzle_1 = MV1SearchFrame(modelHandle, "Muzzle_1");
	muzzle_2 = MV1SearchFrame(modelHandle, "Muzzle_2");

	booster_1 = MV1SearchFrame(modelHandle, "Booster_1");
	booster_2 = MV1SearchFrame(modelHandle, "Booster_2");


	// ブースターのエフェクトの設定
	{
		{
			boosterEf_1 = std::make_unique<HWGameObject>("booster_1");
			boosterEf_1->SetParent(gameObject);
			auto effect = boosterEf_1->AddComponent<HWEffect>("Assets/Effect/booster.efkefc", BOOSTER_EFFECT_SIZE);
			// 終了時のアクションをループに設定
			effect->stopAction = StopAction::Loop;
			// エフェクトの再生
			effect->Play();
		}
		{
			boosterEf_2 = std::make_unique<HWGameObject>("booster_2");
			boosterEf_2->SetParent(gameObject);
			auto effect = boosterEf_2->AddComponent<HWEffect>("Assets/Effect/booster.efkefc", BOOSTER_EFFECT_SIZE);
			// 終了時のアクションをループに設定
			effect->stopAction = StopAction::Loop;
			// エフェクトの再生
			effect->Play();
		}
	}
}

void PlayerController::Update()
{
	// プレイヤーの機が自動で前に進むようにする
	gameObject->transform->velocity = VAdd(gameObject->transform->velocity, VScale(transform->forward, PLAYER_AUTOACROLL_SPEED));

	// 移動により機体が傾ている場合、平行に戻す力を加える
	if (gameObject->transform->rotate.z != PLAYER_DEFAULT_ROTATE.z)
		gameObject->transform->rotate.z += -gameObject->transform->rotate.z / POWER_RETURN_PARALLEL_Z;
	if (gameObject->transform->rotate.x != PLAYER_DEFAULT_ROTATE.x)
		gameObject->transform->rotate.x += -gameObject->transform->rotate.x / POWER_RETURN_PARALLEL_X;


	// 一定時間が経過した弾丸のインスタンスを削除する
	for (auto it = bulletVec.begin(); it != bulletVec.end();)
	{
		// 弾丸管理用のコンポーネントを取得
		auto bulletCp = (*it)->GetComponent<Bullet>();

		// 一定時間経過、もしくはEnemyにヒットしていた場合は削除する
		if (GetNowCount() - bulletCp->startTyme > BULLET_TIME_TO_LIVE ||
			bulletCp->isHit)
		{
			delete *it;
			it = bulletVec.erase(it);  // eraseの戻り値でiteratorを更新
		}
		else
			++it;  // 削除しなかった場合のみ次の要素に進む
	}


	// 一定時間が経過した弾丸のインスタンスを削除する
	for (auto it = bulletVec.begin(); it != bulletVec.end(); /* ここでは更新しない */)
	{
		// 弾丸管理用のコンポーネントを取得
		auto bulletCp = (*it)->GetComponent<Bullet>();

		// 一定時間経過、もしくはEnemyにヒットしていた場合は削除する
		if (GetNowCount() - bulletCp->startTyme > BULLET_TIME_TO_LIVE ||
			bulletCp->isHit)
		{
			delete *it;
			it = bulletVec.erase(it);  // eraseの戻り値でiteratorを更新
		}
		else
			++it;  // 削除しなかった場合のみ次の要素に進む
	}


	// カメラ設定
	auto& pos = gameObject->GetChild(1)->transform->position;
	SetCameraPositionAndTarget_UpVecY(pos, VAdd(transform->position, CAMERA_POSITION));

	// コライダーの座標更新
	capsuleCol->UsStartPos = MV1GetFramePosition(modelHandle, collision_start);
	capsuleCol->UsEndPos = MV1GetFramePosition(modelHandle, collision_end);

	// ブースターのエフェクトの座標更新
	boosterEf_1->transform->position = MV1GetFramePosition(modelHandle, booster_1);
	boosterEf_2->transform->position = MV1GetFramePosition(modelHandle, booster_2);


	DrawFormatString(10, 20, GetColor(0, 255, 0), "%d / %d", hp,maxHp);
}

void PlayerController::Move(const VECTOR& _velocity)
{
	// 移動ベクトルを加算
	transform->velocity = VAdd(transform->velocity, _velocity);

	if (transform->position.x + transform->velocity.x < MOVE_LEFT_LIMIT ||
		transform->position.x + transform->velocity.x > MOVE_RIGHT_LIMIT)
		transform->velocity.x = 0.f;
	if (transform->position.y + transform->velocity.y < MOVE_DOWN_LIMIT ||
		transform->position.y + transform->velocity.y > MOVE_UP_LIMIT)
		transform->velocity.y = 0.f;


	// 移動量に応じて機体を傾ける
	transform->rotate.z += _velocity.x * AIRFRAME_SLOPE_SPEED_Z;

	if(transform->rotate.z > AIRFRAME_MAX_SLOPE_Z ||
		transform->rotate.z < -AIRFRAME_MAX_SLOPE_Z)
	{
		transform->rotate.z -= _velocity.x * AIRFRAME_SLOPE_SPEED_Z;
	}

	transform->rotate.x -= _velocity.y * AIRFRAME_SLOPE_SPEED_X;

	if(transform->rotate.x > AIRFRAME_MAX_SLOPE_X ||
		transform->rotate.x < -AIRFRAME_MAX_SLOPE_X)
	{
		transform->rotate.x += _velocity.y * AIRFRAME_SLOPE_SPEED_X;
	}
}

void PlayerController::Firing(const VECTOR& _pos)
{
	HWGameObject* bullet = new HWGameObject(*Bullet::bulletOrigin);
	// 弾丸の初期座標
	bullet->transform->position = _pos;
	bullet->active = true;
	bullet->name = "Bullet_player";

	auto bulletCp = bullet->AddComponent<Bullet>(attackPower, transform->forward);
	bulletCp->ignoreTag = Tag::player;
	HWCapsuleCollider* col = bullet->AddComponent<HWCapsuleCollider>();
	// コライダーの初期化処理
	col->height = 0;
	col->radius = BULLET_COLLIDR_RADIUS;
	col->isTrigger = true;

	bulletVec.push_back(bullet);
}

void PlayerController::Damage(int _damage)
{
	// 体力を減らす
	hp -= _damage;

	// 体力が0になったら撃破フラグを立てる
	if (hp <= 0)
	{
		hp = 0;
		// スコアを減算
		Score::score += PLAYER_CRASH_SCORE;
		if (Score::score)
			Score::score = 0;

		isCrushing = true;
		Time::SetTargetFPS(10);

		// 撃破用のエフェクトを再生
		HWGameObject* effect = new HWGameObject("CrushingEf");
		auto info = effect->AddComponent<HWEffect>("Assets/Effect/CrushingEffect.efkefc", CRUSHING_EFFECT_SIZE);
		effect->transform->position = transform->position;
		info->stopAction = StopAction::Destroy;
		info->Play();
		info->SetPlaySpeed(2.f);
	}
}
