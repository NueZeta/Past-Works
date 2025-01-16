#include "EnemyController.h"

/**
* @author   Suzuki N
* @date     24/10/03
* @note		EnemyControllerの実装ファイル
*/



EnemyController::EnemyController(const EnemyType& _type) : isErase(false), isCrushing(false), type(_type)
{
	// ステータスなどの初期化設定
	maxHp = hp = ENEMY_DEFAULR_MAXHP;
	// だいたい最初のほうの敵を1撃で倒せるぐらいの攻撃力
	attackPower = ENEMY_DEFAULT_ATTACKPOWER;
	// 上下移動は左右移動よりもやや遅め
	verticalSpeed = ENEMY_DEFAULT_SPEED_VERTICAL;
	// 左右移動は大単に速くしたほうがいいかも？
	horizonSpeed = ENEMY_DEFAULT_SPEED_HORIZON;
	isShootingDown = true;

	priority = -20;
}

EnemyController::~EnemyController()
{
	for (auto it = bulletVec.begin(); it != bulletVec.end(); ++it)
		delete* it;
}

void EnemyController::Awake()
{
	gameObject->active = true;
	shootingTime = GetNowCount();

	// アニメーションをアタッチ
	{
		auto animator = gameObject->AddComponent<HWAnimator>();
		auto& info = animator->AnimLoad("Assets/Enemy/No.1/Anim/Ene_No1_anim.mv1");
		info.isLoop = true;
		info.playSpeed = 700.0f;
		animator->AnimChange(0);
	}
}

void EnemyController::Start()
{
	transform->scale = ENEMY_DEFAULT_SCALE;


	float random_value_X, random_value_Y;

	// 乱数を取得
	while(true)
	{
		random_value_X = Random::GetRandomFloat(-ENEMY_POSITION_TREMOR_X, ENEMY_POSITION_TREMOR_X);
		if (random_value_X + player->transform->position.x > MOVE_LEFT_LIMIT &&
			random_value_X + player->transform->position.x < MOVE_RIGHT_LIMIT)
			break;
	}

	// 乱数を取得
	while (true)
	{
	random_value_Y = Random::GetRandomFloat(-ENEMY_POSITION_TREMOR_Y, ENEMY_POSITION_TREMOR_Y);
		if (random_value_Y + player->transform->position.y < MOVE_UP_LIMIT &&
			random_value_Y + player->transform->position.y > MOVE_DOWN_LIMIT)
			break;
	}


	// 生成座標を指定する
	transform->position = VAdd(player->transform->position,
		VAdd(ENEMY_DEFAULT_POSITION, VGet(random_value_X, random_value_Y, 0)));

	capsuleCol = gameObject->GetComponent<HWCapsuleCollider>();
	modelHandle = gameObject->GetComponent<HWRenderer>()->GetModelHandle();

	// 行動タイプで分岐
	switch (type)
	{
	case EnemyType::straight:
		break;

	case EnemyType::Chase:
		targetPos.x = player->transform->position.x + transform->velocity.x * 1 * 60;
		targetPos.y = player->transform->position.y + transform->velocity.y * 1 * 60;
		targetPos.z = player->transform->position.z + PLAYER_AUTOACROLL_SPEED * 1 * 60;
		// ターゲットの方を向く
		transform->LookAt(targetPos);

		break;
	}
}

void EnemyController::Update()
{
	if (GameManager::isStop) return;

	// 行動タイプで分岐
	switch (type)
	{
	case EnemyType::straight:
		Straight();
		break;

	case EnemyType::Chase:
		Chase();
		break;
	}

	// 一定時間ごとに射撃する
	if (GetNowCount() - shootingTime > ENEMY_SHOOTING_SPAN)
		Firing(transform->position);


#ifdef DEBUG

	if (type == EnemyType::Chase)
		DrawLine3D(targetPos, transform->position, GetColor(0, 255, 0));

#endif // DEBUG


	// 一定時間が経過した弾丸のインスタンスを削除する
	for (auto it = bulletVec.begin(); it != bulletVec.end();)
	{
		// 弾丸管理用のコンポーネントを取得
		auto bulletCp = (*it)->GetComponent<Bullet>();

		// 一定時間経過、もしくはEnemyにヒットしていた場合は削除する
		if (GetNowCount() - bulletCp->startTyme > BULLET_TIME_TO_LIVE ||
			bulletCp->isHit)
		{
			delete* it;
			it = bulletVec.erase(it);  // eraseの戻り値でiteratorを更新
		}
		else
			++it;  // 削除しなかった場合のみ次の要素に進む
	}

	// 自身のZ座標がPlayerの背後に回った時、自身の消滅フラグを立てる
	if (transform->position.z < player->transform->position.z - 300)
		isErase = true;

	// コライダーの座標更新
	capsuleCol->UsStartPos = MV1GetFramePosition(modelHandle, 4);
	capsuleCol->UsEndPos = MV1GetFramePosition(modelHandle, 3);

	// ブースターのエフェクトの座標更新
	//boosterEf->transform->position = MV1GetFramePosition(modelHandle, 4);
}

void EnemyController::OnTriggerEnter(HWCollider& other)
{
	if (other.gameObject->tag != (int)Tag::player) return;


		other.gameObject->GetComponent<PlayerController>()->Damage(10);

		// Hit時のエフェクトを再生
		HWGameObject* effect = new HWGameObject("BulletEf");
		auto info = effect->AddComponent<HWEffect>("Assets/Effect/HitEffect.efkefc", HIT_EFFECT_SIZE);
		effect->transform->position = transform->position;
		info->stopAction = StopAction::Destroy;
		info->Play();
}

void EnemyController::Chase()
{
	// 敵機が自動で前に進むようにする
	gameObject->transform->velocity = VAdd(gameObject->transform->velocity, VScale(transform->forward, ENEMY_AUTOACROLL_SPEED));
}

void EnemyController::Straight()
{
	// 敵機が自動で前に進むようにする
	gameObject->transform->velocity = VAdd(gameObject->transform->velocity, VScale(transform->forward, ENEMY_AUTOACROLL_SPEED));
}

void EnemyController::Firing(const VECTOR& _pos)
{
	HWGameObject* bullet = new HWGameObject(*Bullet::bulletOrigin);
	// 弾丸の初期座標
	bullet->transform->position = _pos;
	bullet->active = true;
	bullet->name = "Bullet_Ene";

	auto bulletCp = bullet->AddComponent<Bullet>(attackPower, transform->forward);
	bulletCp->ignoreTag = Tag::Enemy;
	HWCapsuleCollider* col = bullet->AddComponent<HWCapsuleCollider>();
	// コライダーの初期化処理
	col->height = 0;
	col->radius = BULLET_COLLIDR_RADIUS;
	col->isTrigger = true;

	shootingTime = GetNowCount();

	bulletVec.push_back(bullet);
}

void EnemyController::Damage(int _damage)
{
	// 体力を減らす
	hp -= _damage;

	// 体力が0になったら撃破フラグを立てる
	if (hp <= 0)
	{
		hp = 0;
		// スコアを加算
		Score::score += ENEMY_CRASH_SCORE;

		isCrushing = true;
		// 撃破時のエフェクトを再生
		HWGameObject* effect = new HWGameObject("CrushingEf");
		auto info = effect->AddComponent<HWEffect>("Assets/Effect/CrushingEffect.efkefc", CRUSHING_EFFECT_SIZE);
		effect->transform->position = transform->position;
		info->stopAction = StopAction::Destroy;
		info->Play();
		info->SetPlaySpeed(2.f);
	}
}
