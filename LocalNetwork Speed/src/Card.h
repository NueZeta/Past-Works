/**
 * @file	Card.h
 * @brief	�e�J�[�h���Ƃ̃p�����[�^
 * @author	NS
 * @date	2024/1/2
 */

#pragma once
#include "GameManager.h"


 /**
  * @class	Card
  * @brief  �J�[�h�ꖇ���Ƃɂ��N���X
  */
class Card
{
	//
	// �����o�ϐ�
	//

public:

	//! ���g�̃}�[�N
	Suit suit;
	//! ���g�̐���
	int number;
	//! ���g������̈�
	Area area;
	//! ���g��������̈�̉����ڂ�
	int areaNumber;
	//! ���W
	VECTOR position;
	//! ��]
	VECTOR rotation;
	//! �g�k
	VECTOR scale;
	//! �������W
	VECTOR defaultPosition;
	//! ������]
	VECTOR defaultRotate;
	//! ���g�̃t���[���ԍ�
	int frameIndex;
	//! �J�[�h�S�̂̃��f���n���h��
	static int modelHandle;

	//! �ړ����̃t���O
	bool isMove;

private:

	//! �ړ��A�j���[�V�����̖ڕW�n�_
	VECTOR targetPos;
	//! �ړ��A�j���[�V�����̊J�n�n�_
	VECTOR startPos;


	//
	// ���\�b�h
	//

public:

	/**
	 * @brief		�R���X�g���N�^
	 */
	Card(Suit, int);

	/**
	 * @brief		�R���X�g���N�^
	 */
	Card() {}

	/**
	 * @brief		�f�X�g���N�^
	 */
	~Card();

	/**
	 * @brief		�̈悪�ς�������̃A�j���[�V����
	 */
	void AreaChangeAnimStart(Area _prevArea, Area _newArea);

	/**
	 * @brief		�����I�ȍX�V����
	 */
	void ManualUpdate();

private:

	/**
	 * @brief		���W�̍X�V����
	 */
	void PositionUpdate();

	/**
	 * @brief		�̈悪�ς�������̃A�j���[�V����
	 */
	void AreaChangeAnimation();

};


#pragma pack(1)

/**
 * @class	CardData
 * @brief  �f�[�^���M�p
 */
struct CardData
{
	unsigned char data;
	unsigned char area;
	unsigned char areaNumber;
};

#pragma pack()