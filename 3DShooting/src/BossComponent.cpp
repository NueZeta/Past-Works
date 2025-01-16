#include "BossComponent.h"

BossComponent::BossComponent(HWGameObject* _player) : player(_player), moveType(BossMoveType::Entry),
	moveTime(GetNowCount()), shootingTime(GetNowCount())
{
	// ステータスなどの初期化設定
	maxHp = hp = BOSS_DEFAULR_MAXHP;
	attackPower = BOSS_DEFAULT_ATTACKPOWER;
	isShootingDown = false;
}

BossComponent::~BossComponent()
{
	for (auto it = bulletVec.begin(); it != bulletVec.end(); ++it)
		delete* it;
}

void BossComponent::Entry()
{
	if (transform->position.y < player->transform->position.y)
		MoveTypeSelect();

	// 徐々に下に降りてくる
	transform->velocity.y -= BOSS_MOVE_SPEED * 2;
}

void BossComponent::Wait()
{
	 // 一定時間経過したら次の行動へ移行する
	if (GetNowCount() - moveTime > BOSS_TIME_UNTIL_NEXT_ACTION)
		MoveTypeSelect();
}

void BossComponent::Move()
{
	// 一定時間経過したら次の行動へ移行する
	if (GetNowCount() - moveTime > BOSS_TIME_UNTIL_NEXT_ACTION)
		MoveTypeSelect();

	// 移動方向が決まっていない場合、ランダムに決める
	if(moveDirection == -1)
		moveDirection = Random::GetRandomInt(0, 3);

	switch (moveDirection)
	{
		// ↑
	case 0:
		if (transform->position.y > MOVE_UP_LIMIT)
		{
			moveDirection = -1;
			break;
		}
		transform->velocity.y += BOSS_MOVE_SPEED;
		break;

		// ↓
	case 1:
		if (transform->position.y < MOVE_DOWN_LIMIT)
		{
			moveDirection = -1;
			break;
		}
		transform->velocity.y -= BOSS_MOVE_SPEED;
		break;

		// ←
	case 2:
		if (transform->position.x < MOVE_LEFT_LIMIT)
		{
			moveDirection = -1;
			break;
		}
		transform->velocity.x -= BOSS_MOVE_SPEED;
		break;

		// →
	case 3:
		if (transform->position.x > MOVE_RIGHT_LIMIT)
		{
			moveDirection = -1;
			break;
		}
		transform->velocity.x += BOSS_MOVE_SPEED;
		break;
	}
}

void BossComponent::Fire()
{
	// 一定時間経過したら次の行動へ移行する
	if (GetNowCount() - moveTime > BOSS_TIME_UNTIL_NEXT_ACTION * 2)
		MoveTypeSelect();

	// 一定間隔でPlayerに向けて攻撃する
	if (GetNowCount() - shootingTime > BOSS_FIRE_SPAN)
	{
		// 目標地点
		VECTOR targetPos = player->transform->position;

		targetPos = VAdd(player->transform->position, VScale(player->transform->velocity, 1 * 60));
		targetPos.y += 20;

		HWGameObject* bullet = new HWGameObject(*Bullet::bulletOrigin);
		// 弾丸の初期座標
		bullet->transform->position = transform->position;
		bullet->active = true;
		bullet->name = "Bullet_Boss";
		bullet->transform->scale = VScale(bullet->transform->scale, 1);

		bullet->transform->LookAt(targetPos);
		bullet->transform->rotate = VAdd(bullet->transform->rotate, VGet(0, 190,0));


		// Boss -> Player に向けた方向ベクトル
		VECTOR dir = VNorm(VSub(targetPos, bullet->transform->position));

		auto bulletCp = bullet->AddComponent<Bullet>(attackPower, dir);
		bulletCp->ignoreTag = Tag::Boss;
		HWCapsuleCollider* col = bullet->AddComponent<HWCapsuleCollider>();
		// コライダーの初期化処理
		col->height = 0;
		col->radius = BULLET_COLLIDR_RADIUS * 3;
		col->isTrigger = true;

		// コンテナに追加する
		bulletVec.push_back(bullet);
		// 攻撃時間を上書き
		shootingTime = GetNowCount();
	}
}

void BossComponent::MoveTypeSelect()
{
	// Entryをのぞいた行動からランダムに決める
	moveType = (BossMoveType)Random::GetRandomInt(1, 3);
	moveTime = GetNowCount();
	moveDirection = -1;
}

void BossComponent::Damage(int _damage)
{
	// 体力を減らす
	hp -= _damage;

	// 体力が0になったら撃破フラグを立てる
	if (hp <= 0)
	{
		hp = 0;
		// ボス用のスコアを加算
		Score::score += BOSS_CRASH_SCORE;

		isCrushing = true;
		// 撃破時のエフェクトを再生
		HWGameObject* effect = new HWGameObject("CrushingEf");
		auto info = effect->AddComponent<HWEffect>("Assets/Effect/CrushingEffect.efkefc", CRUSHING_EFFECT_SIZE * 2);
		effect->transform->position = transform->position;
		info->stopAction = StopAction::Destroy;
		info->Play();
		info->SetPlaySpeed(2.f);
	}
}

void BossComponent::Awake()
{
	gameObject->tag = (int)Tag::Boss;
	gameObject->name = "Boss";
	gameObject->active = true;

	// アニメーションをアタッチ
	{
		auto animator = gameObject->AddComponent<HWAnimator>();
		auto& info = animator->AnimLoad("Assets/Enemy/No.1/Anim/Ene_No1_anim.mv1");
		info.isLoop = true;
		info.playSpeed = 700.0f;
		animator->AnimChange(0);
	}

	// 当たり判定を付与
	capsuleCol = gameObject->AddComponent<HWCapsuleCollider>();
	// 当たり判定の初期化
	capsuleCol->radius = BOSS_COLLIDR_RADIUS;
	capsuleCol->isTrigger = true;
	modelHandle = gameObject->GetComponent<HWRenderer>()->GetModelHandle();
}

void BossComponent::Start()
{
	transform->scale = BOSS_DEFAULT_SCALE;

	// 生成座標を指定する
	transform->position = VAdd(player->transform->position, BOSS_DEFAULT_POSITION);
	transform->rotate = BOSS_DEFAULT_ROTATE;
}

void BossComponent::Update()
{
	if (GameManager::isStop) return;

	// プレイヤーの機が自動で前に進むようにする
	gameObject->transform->velocity = VAdd(gameObject->transform->velocity, VScale(transform->forward, PLAYER_AUTOACROLL_SPEED));

	// 現在の行動タイプによって分岐
	switch (moveType)
	{
	case BossMoveType::Entry:
		Entry();
		break;
	case BossMoveType::Wait:
		Wait();
		break;
	case BossMoveType::Move:
		Move();
		break;
	case BossMoveType::Fire:
		Fire();
		break;
	}

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

	// コライダーの座標更新
	capsuleCol->UsStartPos = MV1GetFramePosition(modelHandle, 4);
	capsuleCol->UsEndPos = MV1GetFramePosition(modelHandle, 3);


}

void BossComponent::OnTriggerEnter(HWCollider& other)
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
