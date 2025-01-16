#include "VampireModel.h"

VampireModel::VampireModel()
	: maxHp(1000), hp(maxHp), param(Parameter::Neutral)
{
	// “ü—ÍŒn‚Ì‰Šúİ’è
	input = std::make_unique<InputSystem>();
	// Å‰‚É—v‘f‚ğˆê‚Â‚¾‚¯“ü‚ê‚Ä‚¨‚­
	keyHistory.push_back(InputKey::Neutral);
}


void VampireModel::ExplicitUpdate()
{
	// 30 ‚æ‚è‚à‘O‚Ì“ü—Í‹L˜^‚ğÁ‚·
	if (keyHistory.size() > 30)
	{
		keyHistory.erase(keyHistory.begin(), keyHistory.begin() + (keyHistory.size() - 30));
	}
}
