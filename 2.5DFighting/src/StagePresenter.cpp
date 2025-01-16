#include "StagePresenter.h"

float StageModel::leftCorner = 0.0f;
float StageModel::rightCorner = 0.0f;


void StagePresenter::Initialize(VampirePresenter* _presenter1, VampirePresenter* _presenter2)
{
	model->player1_presenter = _presenter1;
	model->player2_presenter = _presenter2;

	// 注視点を定める
	model->viewPoint = model->player1_presenter->transform->position +
		(model->player1_presenter->transform->position - model->player2_presenter->transform->position) * 0.5;

	// 初期座標と拡縮
	transform->position = VGet(500, 70, 100);
	transform->scale = VGet(2, 2, 2);
}


void StagePresenter::Awake()
{
	model = std::make_unique<StageModel>();
	view = gameObject->AddComponent<StageView>();
	// 明示的な初期化関数を呼び出す
	view->Initialize();
}


void StagePresenter::Update()
{
	// 注視点を定める
	model->viewPoint.x = (model->player1_presenter->transform->position.x + model->player2_presenter->transform->position.x) / 2;
	model->viewPoint.y = 200;
	model->viewPoint.z = model->player1_presenter->transform->position.z;

	if (model->viewPoint.x < -1000)
		model->viewPoint.x = -1000;
	if (model->viewPoint.x > 2000)
		model->viewPoint.x = 2000;

	StageModel::leftCorner = model->viewPoint.x - 450;
	StageModel::rightCorner = model->viewPoint.x + 450;


	SetCameraPositionAndTarget_UpVecY(model->viewPoint - VGet(0, -50, 500) + VGet(0,0,0), model->viewPoint);
}
