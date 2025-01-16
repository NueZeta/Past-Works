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
	// 初期座標
	transform->position = _pos;
	model->speed = _speed;
	model->generateTime = GetNowCount();

	// コライダーコンポーネントをアタッチ
	model->attackCol = gameObject->AddComponent<HWCapsuleCollider>();

	model->attackCol->radius = 0.f;
	model->attackCol->isTrigger = true;

	// とぶ方向を決める
	model->flyingDirection = ((model->vampireModel->param & Parameter::Facing_Right) == Parameter::Facing_Right);

	model->effectCp = gameObject->AddComponent<HWEffect>(_effecthandle, 0.f);
	model->effectCp->stopAction = StopAction::Destroy;
	model->effectCp->Play();

	model->effectCp->transform->scale = VGet(0, 0, 0);

	CollisionEnable();

	// 一定時間後に削除する
	HWGameObject::Destroy(gameObject, 4.0f);
}


void ProjectilePresenter::Awake()
{
	gameObject->tag = (int)Tag::FireBall;

	// モデルのインスタンスを作成
	model = std::make_unique<ProjectileModel>();
	// Viewコンポーネントをアタッチする
	view = gameObject->AddComponent<ProjectileView>();
	// 明示的な初期化処理を行う
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
	// 飛び道具と衝突した場合
	if (other.gameObject->tag == (int)Tag::FireBall)
		HWGameObject::Destroy(gameObject);

	// 対戦相手のコライダーにHitした場合
	if ((model->vampireModel->playerId == 1 && other.gameObject->tag == (int)Tag::Player_2) ||
		(model->vampireModel->playerId == 2 && other.gameObject->tag == (int)Tag::Player_1))
	{
		//
		// ダメージ、硬直処理
		//

		// 相手にHitしたことを伝える 戻り値でHitかGuardかを判定
		int isHit = other.gameObject->GetComponent<VampirePresenter>()->AttackHit(this);
		// パラメータのHitフラグを立てる
		model->vampireModel->param |= Parameter::Hit;
		
		//
		// エフェクト再生
		//
		
		// Hit時のエフェクト再生
		HWGameObject* effect = new HWGameObject("HitEf");
		auto info = effect->AddComponent<HWEffect>("Assets/Effect/HitEffect.efkefc", 30.f);
		effect->transform->position = transform->position;
		info->stopAction = StopAction::Destroy;
		info->Play();
		HWGameObject::Destroy(gameObject);
	}
}
