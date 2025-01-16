#include "TableModel.h"

TableModel::TableModel()
	: tableModelHandle(-1)
{
}

void TableModel::Initialize()
{
	//
	// ‰Šú‰»İ’è
	//

	tableModelHandle = MV1LoadModel("Assets/Model/Table/Table.mv1");
}

