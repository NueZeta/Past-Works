#include "VampireModel.h"

VampireModel::VampireModel()
	: maxHp(1000), hp(maxHp), param(Parameter::Neutral)
{
	// 入力系の初期設定
	input = std::make_unique<InputSystem>();
	// 最初に要素を一つだけ入れておく
	keyHistory.push_back(InputKey::Neutral);
}


void VampireModel::ExplicitUpdate()
{
	// 30 よりも前の入力記録を消す
	if (keyHistory.size() > 30)
	{
		keyHistory.erase(keyHistory.begin(), keyHistory.begin() + (keyHistory.size() - 30));
	}
}
