#include "ProjectilePresenter.h"


void ProjectilePresenter::CollisionSet(VampireModel* _model, const int _effecthandle, const VECTOR _pos, 
	const float _attackColRadius, const int _damage, const int _hitStun, const int _guardStun, const float _speed, AttackAttribute _attribute)
{
	model->vampireModel = _model;
	model->attackColRadius = _attackColRadius;
	model->damage = _damage;
	model->hitStun = _hitStun;
	model->guardStun = _guardStun;
	model->attribute = _attribute;
	// �������W
	transform->position = _pos;
	model->speed = _speed;
	model->generateTime = GetNowCount();

	// �R���C�_�[�R���|�[�l���g���A�^�b�`
	model->attackCol = gameObject->AddComponent<HWCapsuleCollider>();

	model->attackCol->radius = 0.f;
	model->attackCol->isTrigger = true;

	// �Ƃԕ��������߂�
	model->flyingDirection = ((model->vampireModel->param & Parameter::Facing_Right) == Parameter::Facing_Right);

	model->effectCp = gameObject->AddComponent<HWEffect>(_effecthandle, 0.f);
	model->effectCp->stopAction = StopAction::Destroy;
	model->effectCp->Play();

	model->effectCp->transform->scale = VGet(0, 0, 0);

	CollisionEnable();

	// ��莞�Ԍ�ɍ폜����
	HWGameObject::Destroy(gameObject, 4.0f);
}


void ProjectilePresenter::Awake()
{
	gameObject->tag = (int)Tag::FireBall;

	// ���f���̃C���X�^���X���쐬
	model = std::make_unique<ProjectileModel>();
	// View�R���|�[�l���g���A�^�b�`����
	view = gameObject->AddComponent<ProjectileView>();
	// �����I�ȏ������������s��
	view->Initialize();
}


void ProjectilePresenter::Update()
{
	if (model->effectCp->transform->scale.x < 1.f)
		model->effectCp->transform->scale += VGet(0.2f,0.2f,0.2f);
	if (model->attackCol->radius < model->attackColRadius)
		model->attackCol->radius += 3.0f;

	if(model->flyingDirection)
		transform->position.x += model->speed;
	else
		transform->position.x -= model->speed;
}


void ProjectilePresenter::OnDestroy()
{
	model->effectCp->Stop();
	model->vampireModel->projectile = nullptr;
}


void ProjectilePresenter::OnTriggerEnter(HWCollider& other)
{
	// ��ѓ���ƏՓ˂����ꍇ
	if (other.gameObject->tag == (int)Tag::FireBall)
		HWGameObject::Destroy(gameObject);

	// �ΐ푊��̃R���C�_�[��Hit�����ꍇ
	if ((model->vampireModel->playerId == 1 && other.gameObject->tag == (int)Tag::Player_2) ||
		(model->vampireModel->playerId == 2 && other.gameObject->tag == (int)Tag::Player_1))
	{
		//
		// �_���[�W�A�d������
		//

		// �����Hit�������Ƃ�`���� �߂�l��Hit��Guard���𔻒�
		int isHit = other.gameObject->GetComponent<VampirePresenter>()->AttackHit(this);
		// �p�����[�^��Hit�t���O�𗧂Ă�
		model->vampireModel->param |= Parameter::Hit;
		
		//
		// �G�t�F�N�g�Đ�
		//
		
		// Hit���̃G�t�F�N�g�Đ�
		HWGameObject* effect = new HWGameObject("HitEf");
		auto info = effect->AddComponent<HWEffect>("Assets/Effect/HitEffect.efkefc", 30.f);
		effect->transform->position = transform->position;
		info->stopAction = StopAction::Destroy;
		info->Play();
		HWGameObject::Destroy(gameObject);
	}
}
