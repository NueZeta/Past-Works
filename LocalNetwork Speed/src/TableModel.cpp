#include "TableModel.h"

TableModel::TableModel()
	: tableModelHandle(-1)
{
}

void TableModel::Initialize()
{
	//
	// �������ݒ�
	//

	tableModelHandle = MV1LoadModel("Assets/Model/Table/Table.mv1");
}

