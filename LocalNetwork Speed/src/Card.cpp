/**
 * @file	Card.cpp
 * @brief	�e�J�[�h���Ƃ̃p�����[�^
 * @author	NS
 * @date	2024/1/2
 */

#include "Card.h"
#include "CardManager.h"

 //
 // �ÓI�����o�ϐ��̏�����
 // 
int Card::modelHandle = 0;


Card::Card(Suit _suit, int _number)
	: suit(_suit), number(_number), position({0,0,0}), rotation({0,0,0}), scale({1,1,1}),frameIndex(-1),
	defaultPosition({0,0,0}), defaultRotate({0,0,0}), area(Area::Deck), areaNumber(-1), isMove(false),
	targetPos({0,0,0}), startPos({ 0,0,0 })
{
	//
	// ���g�̃t���[���̐ݒ�
	//

	switch (suit)
	{
	case Suit::Heart:
		frameIndex = number + 1;
		break;
	case Suit::Diamond:
		frameIndex = number + 13 + 2;
		break;
	case Suit::Club:
		frameIndex = number + 13 * 2 + 3;
		break;
	case Suit::Spade:
		frameIndex = number + 13 * 3 + 4;
		break;
	}
}

Card::~Card()
{
}

void Card::ManualUpdate()
{
	// �|�W�V�����ɉ����č��W��ύX
	position.z = areaNumber * 0.06f;

	// �J�[�h�A�j���[�V����
	AreaChangeAnimation();

	// ���W�̍X�V
	PositionUpdate();
}

void Card::PositionUpdate()
{
	//
	// �������W��ݒ�
	//

	if (area == Area::Deck)
		defaultPosition = DeckDefaultPosition;
	else if (area == Area::Hand)
		defaultPosition = HandDefaultPosition;

	else if (area == Area::Field_1)
		defaultPosition = Field1DefaultPosition;
	else if (area == Area::Field_2)
		defaultPosition = Field2DefaultPosition;

	else if (area == Area::Deck_Opponent)
		defaultPosition = OpponentDeckDefaultPosition;
	else if (area == Area::Hand_Opponent)
		defaultPosition = OpponentHandDefaultPosition;

	//
	// ��]�̏����l�����߂�
	//
	if (area == Area::Deck || area == Area::Deck_Opponent)
		defaultRotate = { 0,0,180 };
	else
		defaultRotate = { 0,0,0 };

	if (!isMove && (area == Area::Field_1 || area == Area::Field_2))
	{
		position.x = 0;
		position.y = 0;
	}


	// transform�s��
	MATRIX mat, t, r, s;
	t = r = s = MGetIdent();

	// ���s�ړ�
	t.m[3][0] = defaultPosition.x + position.x;
	t.m[3][1] = defaultPosition.z + position.z;
	t.m[3][2] = defaultPosition.y + position.y;

	// ��]
	MATRIX rotX = MGetRotX((float)Deg2Rad(defaultRotate.x + rotation.x));
	MATRIX rotY = MGetRotY((float)Deg2Rad(defaultRotate.y + rotation.y));
	MATRIX rotZ = MGetRotZ((float)Deg2Rad(defaultRotate.z + rotation.z));
	r = MMult(rotZ, MMult(rotY, rotX));

	// �g�k
	s.m[0][0] = scale.x;
	s.m[1][1] = scale.y;
	s.m[2][2] = scale.z;

	// �s��̍���(t -> r -> s)
	mat = MMult(s, MMult(r, t));

	MV1SetFrameUserLocalMatrix(Card::modelHandle, frameIndex, mat);
}

void Card::AreaChangeAnimation()
{
	if (CardManager::Instance().selectItem == ItemList::Deck)
		if (area == Area::Deck && areaNumber == CardManager::Instance().deck.size() - 1)
			scale = { 1.2f,1.2f,1.2f };
		else
			scale = { 1,1,1 };
	if (CardManager::Instance().selectItem == ItemList::Hand_1)
		if (area == Area::Hand && areaNumber == 0)
			scale = { 1.2f,1.2f,1.2f };
		else
			scale = { 1,1,1 };
	if (CardManager::Instance().selectItem == ItemList::Hand_2)
		if (area == Area::Hand && areaNumber == 1)
			scale = { 1.2f,1.2f,1.2f };
		else
			scale = { 1,1,1 };
	if (CardManager::Instance().selectItem == ItemList::Hand_3)
		if (area == Area::Hand && areaNumber == 2)
			scale = { 1.2f,1.2f,1.2f };
		else
			scale = { 1,1,1 };
	if (CardManager::Instance().selectItem == ItemList::Hand_4)
		if (area == Area::Hand && areaNumber == 3)
			scale = { 1.2f,1.2f,1.2f };
		else
			scale = { 1,1,1 };
	if (CardManager::Instance().selectItem == ItemList::Field_1)
		if (area == Area::Field_1 && areaNumber == CardManager::Instance().field_1.size() - 1)
			scale = { 1.2f,1.2f,1.2f };
		else
			scale = { 1,1,1 };
	if (CardManager::Instance().selectItem == ItemList::Field_2)
		if (area == Area::Field_2 && areaNumber == CardManager::Instance().field_2.size() - 1)
			scale = { 1.2f,1.2f,1.2f };
		else
			scale = { 1,1,1 };
	if(CardManager::Instance().selectCard.get() == this)
		if(area == Area::Hand)
			scale = { 1.2f,1.2f,1.2f };
		else
			scale = { 1,1,1 };

	if (!isMove) return;
}

void Card::AreaChangeAnimStart(Area _prevArea, Area _newArea)
{
	return;

	isMove = true;

	startPos = position + defaultPosition;

	if (_newArea == Area::Field_1)
		targetPos = Field1DefaultPosition;
	if (_newArea == Area::Field_2)
		targetPos = Field2DefaultPosition;

	position = { 0,0,0 };


}
