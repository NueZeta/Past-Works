#include "TablePresenter.h"

TablePresenter::TablePresenter()
{
}

void TablePresenter::Awake()
{
	//
	// MVP‚Ì‰Šú‰»
	//

	model = std::make_unique<TableModel>();
	view = gameObject->AddComponent<TableView>();

	model->Initialize();
	view->Initialize(model->tableModelHandle);

	gameObject->AddComponent<HWRenderer>(model->tableModelHandle);

	transform->rotate = { -90,0,0 };
	transform->position = { 1100,200,600 };
	transform->scale = { 2.5,1,2.5 };
}

void TablePresenter::Update()
{
}
