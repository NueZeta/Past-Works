#include "TableModel.h"

TableModel::TableModel()
	: tableModelHandle(-1)
{
}

void TableModel::Initialize()
{
	//
	// 初期化設定
	//

	tableModelHandle = MV1LoadModel("Assets/Model/Table/Table.mv1");
}

