#pragma once

#include "HandlerWaltanForDxLib.h"
#include <random>


//
// �萔��`
//

//#define DEBUG (1)

//! �J�[�h����(�W���[�J�[����)
const int CardTotalNumber = 52;

//! �v���C���[1�̎�D�̏�������
const int InitialHandNumber_1p = 4;
//! �v���C���[1�̎�D�̖������
const int HandNumberLimit_1p = 4;

//! �v���C���[2�̎�D�̏�������
const int InitialHandNumber_2p = 4;
//! �v���C���[2�̎�D�̖������
const int HandNumberLimit_2p = 4;

//! �f�b�L�̏������W
const VECTOR DeckDefaultPosition = { 10,-10,0 };
//! ��D�̏������W
const VECTOR HandDefaultPosition = { 80,-15,0 };

//! �ΐ푊��̃f�b�L�̏������W
const VECTOR OpponentDeckDefaultPosition = { 10,32,0 };
//! �ΐ푊��̎�D�̏������W
const VECTOR OpponentHandDefaultPosition = { 80,37,0 };

//! �t�B�[���h(1���[��)�������W
const VECTOR Field1DefaultPosition = { 70, 11, 0 };
//! �t�B�[���h(2���[��)�������W
const VECTOR Field2DefaultPosition = { 90, 11, 0 };


/**
 * @enum	Suit
 * @brief	�J�[�h�̕�
 */
enum class Suit
{
	//! �n�[�g
	Heart = 0,
	//! �_�C��
	Diamond = 1,
	//! �N���u
	Club = 2,
	//! �X�y�[�h
	Spade = 3
};

/**
 * @enum	Area
 * @brief	�J�[�h�����݂���̈�
 */
enum class Area
{
	//! �R�D
	Deck,
	//! �R�D
	Deck_Opponent,
	//! �t�B�[���h1
	Field_1,
	//! �t�B�[���h2
	Field_2,
	//! ��D(1P)
	Hand,
	//! ��D(2P)
	Hand_Opponent
};

/**
 * @enum	ItemList
 * @brief	�I������
 */
enum class ItemList
{
	//! �R�D
	Deck,
	//! ��D1
	Hand_1,
	//! ��D2
	Hand_2,
	//! ��D3
	Hand_3,
	//! ��D4
	Hand_4,
	//! �t�B�[���h1
	Field_1,
	//! �t�B�[���h2
	Field_2,
};

/**
 * @enum	Direction
 * @brief	����
 */
enum class Direction
{
	Up		= 2,
	Down	= -2,
	Right	= 1,
	Left	= -1,
};


/**
 * @enum	GameParameter
 * @brief	�Q�[���̃p�����[�^
 */
enum class GameParameter
{
	//! �Z�b�g�A�b�v
	SetUp,
	//! �Q�[����
	Game,
	//! ���U���g
	Result
};

/**
 * @enum	PlayerType
 * @brief	�v���C���[�̎��
 */
enum class PlayerType
{
	//! �z�X�g
	Host,
	//! �N���C�A���g
	Client,
};

