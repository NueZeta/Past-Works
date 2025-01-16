#include "VampireModel.h"

VampireModel::VampireModel()
	: maxHp(1000), hp(maxHp), param(Parameter::Neutral)
{
	// ���͌n�̏����ݒ�
	input = std::make_unique<InputSystem>();
	// �ŏ��ɗv�f�����������Ă���
	keyHistory.push_back(InputKey::Neutral);
}


void VampireModel::ExplicitUpdate()
{
	// 30 �����O�̓��͋L�^������
	if (keyHistory.size() > 30)
	{
		keyHistory.erase(keyHistory.begin(), keyHistory.begin() + (keyHistory.size() - 30));
	}
}
