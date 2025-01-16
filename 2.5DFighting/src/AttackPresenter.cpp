#include "AttackPresenter.h"


void AttackPresenter::CollisionSet(VampireModel* _model, const int _modelHandle, const int _centerFrame_right, const int _centerFrame_left, 
	const float _attackColRadius, const int _damage, const int _hitStun, const int _guardStun, AttackAttribute _attribute)
{
	model->vampireModel = _model;
	model->modelHandle = _modelHandle;
	model->attackColCenterFrame_right = _centerFrame_right;
	model->attackColCenterFrame_left = _centerFrame_left;
	model->attackColRadius = _attackColRadius;
	model->damage = _damage;
	model->hitStun = _hitStun;
	model->guardStun = _guardStun;
	model->attribute = _attribute;
	
	// コライダーコンポーネントをアタッチ
	model->attackCol = gameObject->AddComponent<HWCapsuleCollider>();

	model->attackCol->radius = model->attackColRadius;
	model->attackCol->isTrigger = true;
}


void AttackPresenter::Awake()
{
	gameObject->tag = (int)Tag::Attack;
	// モデルのインスタンスを作成
	model = std::make_unique<AttackModel>();
	// Viewコンポーネントをアタッチする
	view = gameObject->AddComponent<AttackView>();
	// 明示的な初期化処理を行う
	view->Initialize();
}


void AttackPresenter::Update()
{
	//
	// コライダーの位置を更新
	//

	// 右向きの場合
	if ((model->vampireModel->param & Parameter::Facing_Right) == Parameter::Facing_Right)
		model->attackCol->center = MV1GetFramePosition(model->modelHandle, model->attackColCenterFrame_right);
	else
		model->attackCol->center = MV1GetFramePosition(model->modelHandle, model->attackColCenterFrame_left);
}


void AttackPresenter::OnTriggerEnter(HWCollider& other)
{
	// 対戦相手のコライダーにHitした場合
	if ((model->vampireModel->playerId == 1 && other.gameObject->tag == (int)Tag::Player_2) ||
		(model->vampireModel->playerId == 2 && other.gameObject->tag == (int)Tag::Player_1))
	{		
		//
		// ダメージ、硬直処理
		//

		//! 相手のキャラクター管理コンポーネントを所得
		VampirePresenter* presenter = other.gameObject->GetComponent<VampirePresenter>();

		// 相手にHitしたことを伝える 戻り値でHitかGuardかを判定
		int isHit = presenter->AttackHit(this);

		// ダウン中は無視
		if ((presenter->model->param & Parameter::Down) == Parameter::Down)
			return;

		// パラメータのHitフラグを立てる
		model->vampireModel->param |= Parameter::Hit;

		// コリジョンを切る
		CollisionDisable();
	}
}
