#include "Bullet.h"


HWGameObject* Bullet::bulletOrigin = nullptr;


Bullet::Bullet(const int _damage, const VECTOR& _dir) : ignoreTag(Tag::notFound), 
				damage(_damage), FiringDirection(_dir), isHit(false)
{
	startTyme = GetNowCount();
}

Bullet::~Bullet()
{
}

void Bullet::Awake()
{
}

void Bullet::Start()
{

}

void Bullet::Update()
{
	// 弾丸を飛ばす処理
	transform->velocity = VAdd(transform->velocity, VScale(FiringDirection, BULLET_SPEED));
}

void Bullet::OnTriggerEnter(HWCollider& other)
{
	// Hitしたオブジェクトが特定のタグを持っていた場合、そのまま終了
	if (other.gameObject->tag == gameObject->tag || other.gameObject->tag == (int)ignoreTag)
		return;

	// Hit時の処理
	isHit = true;

	// Hit時のダメージ処理
	switch (other.gameObject->tag)
	{
	case (int)Tag::Enemy:
	{
		other.gameObject->GetComponent<EnemyController>()->Damage(damage);

		// Hit時のエフェクトを再生
		HWGameObject* effect = new HWGameObject("BulletEf");
		auto info = effect->AddComponent<HWEffect>("Assets/Effect/HitEffect.efkefc", HIT_EFFECT_SIZE);
		effect->transform->position = transform->position;
		info->stopAction = StopAction::Destroy;
		info->Play();
		info->SetColor(255, 0, 0, 255);

		break;
	}

	case (int)Tag::player:
	{
		other.gameObject->GetComponent<PlayerController>()->Damage(damage);

		// Hit時のエフェクトを再生
		HWGameObject* effect = new HWGameObject("BulletEf");
		auto info = effect->AddComponent<HWEffect>("Assets/Effect/HitEffect.efkefc", HIT_EFFECT_SIZE);
		effect->transform->position = transform->position;
		info->stopAction = StopAction::Destroy;
		info->Play();
		//info->SetColor(0, 0, 255, 255);

		break;
	}

	case (int)Tag::Boss:
	{
		other.gameObject->GetComponent<BossComponent>()->Damage(damage);

		// Hit時のエフェクトを再生
		HWGameObject* effect = new HWGameObject("BulletEf");
		auto info = effect->AddComponent<HWEffect>("Assets/Effect/HitEffect.efkefc", HIT_EFFECT_SIZE);
		effect->transform->position = transform->position;
		info->stopAction = StopAction::Destroy;
		info->Play();

		break;
	}
	}
}
