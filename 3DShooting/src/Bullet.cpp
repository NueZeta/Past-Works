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
	// �e�ۂ��΂�����
	transform->velocity = VAdd(transform->velocity, VScale(FiringDirection, BULLET_SPEED));
}

void Bullet::OnTriggerEnter(HWCollider& other)
{
	// Hit�����I�u�W�F�N�g������̃^�O�������Ă����ꍇ�A���̂܂܏I��
	if (other.gameObject->tag == gameObject->tag || other.gameObject->tag == (int)ignoreTag)
		return;

	// Hit���̏���
	isHit = true;

	// Hit���̃_���[�W����
	switch (other.gameObject->tag)
	{
	case (int)Tag::Enemy:
	{
		other.gameObject->GetComponent<EnemyController>()->Damage(damage);

		// Hit���̃G�t�F�N�g���Đ�
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

		// Hit���̃G�t�F�N�g���Đ�
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

		// Hit���̃G�t�F�N�g���Đ�
		HWGameObject* effect = new HWGameObject("BulletEf");
		auto info = effect->AddComponent<HWEffect>("Assets/Effect/HitEffect.efkefc", HIT_EFFECT_SIZE);
		effect->transform->position = transform->position;
		info->stopAction = StopAction::Destroy;
		info->Play();

		break;
	}
	}
}
