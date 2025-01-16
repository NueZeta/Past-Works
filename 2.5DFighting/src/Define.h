#pragma once

//! �f�o�b�O���[�h
#define DEBUG (1)


// �C���N���[�h�t�@�C�� ------------------------------------------------

#include <chrono>
#include <thread>
#include "HandlerWaltanForDxLib.h"
#include <math.h>
#include <iostream>
#include <cmath>

// ---------------------------------------------------------------------





// �^�O ----------------------------------------------------------------


enum class Tag
{
	Player_1,
	Player_2,
	Attack,
	FireBall,
};

// ---------------------------------------------------------------------



// enum ----------------------------------------------------------------

/**
 * @enum	Parameter
 * @brief	�L�����N�^�[�̌��݂̃p�����[�^
 */
enum class Parameter
{
	//! �j���[�g�������(0)
	Neutral      = 0,
	//! ���Ⴊ��(1)
	Crouching    = 1,
	//! �E�������Ă���(2)
	Facing_Right = 1 << 1,
	//! �O�i(3)
	Walk         = 1 << 2,
	//! ���(3)
	Back         = 1 << 3,
	//! �W�����v(4)
	Jump		 = 1 << 4,
	//! �K�[�h��(5)
	Guard        = 1 << 5,
	//! �H�炢�d��(6)
	Hitstun      = 1 << 6,
	//! �K�[�h�d��(7)
	Blockstun    = 1 << 7,
	//! �_�E����(8)
	Down		 = 1 << 8,
	//! �U��������Ƀq�b�g(9)
	Hit          = 1 << 9,
	//! ��U��(10)
	La           = 1 << 10,
	//! ���U��(11)
	Ha           = 1 << 11,
	//! �K�E�Z_1(12)
	Special_1    = 1 << 12,
	//! �K�E�Z_2(13)
	Special_2    = 1 << 13,
};

// �r�b�g���Z�p�̃w���p�[�֐�
inline Parameter operator|(Parameter a, Parameter b) {
	return static_cast<Parameter>(static_cast<uint16_t>(a) | static_cast<uint16_t>(b));
}
inline Parameter operator&(Parameter a, Parameter b) {
	return static_cast<Parameter>(static_cast<uint16_t>(a) & static_cast<uint16_t>(b));
}
inline Parameter operator~(Parameter a) {
	return static_cast<Parameter>(~static_cast<uint16_t>(a));
}
inline bool operator!(Parameter a) {
	return !static_cast<bool>(a);
} 
inline Parameter operator|=(Parameter& a, Parameter b) {
	return a = static_cast<Parameter>(static_cast<uint16_t>(a) | static_cast<uint16_t>(b));
}
inline Parameter operator&=(Parameter &a, Parameter b) {
	return a = static_cast<Parameter>(static_cast<uint16_t>(a) & static_cast<uint16_t>(b));
}
inline bool operator==(Parameter a, Parameter b) {
	return static_cast<uint16_t>(a) == static_cast<uint16_t>(b);
}




/**
 * @enum	VampireAnim
 * @brief	�L�����N�^�[1�̃A�j���[�V����
 */
enum class VampireAnim
{
	StIdol			= 0,
	Jump			= 1,
	Fall			= 2,
	Landing			= 3,
	Down			= 4,
	WakeUp			= 5,
	StWalk 			= 6,
	StBack			= 7,
	StDamage		= 8,
	StGuard			= 9,
	StHa			= 10,
	StLa			= 11,
	CrIdol			= 12,
	CrDamage		= 13,
	CrGuard			= 14,
	CrHa			= 15,
	CrLa			= 16,
	SpFireBall		= 17,
	SpDragonUpper	= 18,

	//! ����
	Left,
};


/**
 * @enum	InputKey
 * @brief   �L�[����
 */
enum class InputKey
{
	//! ���� -> 5
	Neutral = 0,
	//! ���� -> 8
	Up      = 1,
	//! ���� -> 2
	Down    = 1 << 1,
	//! ���� -> 4
	Left    = 1 << 2,
	//! ���� -> 6
	Right   = 1 << 3,
	//! ���� -> ��U��
	La      = 1 << 4,
	//! ���� -> ���U��
	Ha      = 1 << 5,
};

// �r�b�g���Z�p�̃w���p�[�֐�
inline InputKey operator|(InputKey a, InputKey b) {
	return static_cast<InputKey>(static_cast<uint16_t>(a) | static_cast<uint16_t>(b));
}
inline InputKey operator&(InputKey a, InputKey b) {
	return static_cast<InputKey>(static_cast<uint16_t>(a) & static_cast<uint16_t>(b));
}
inline InputKey operator~(InputKey a) {
	return static_cast<InputKey>(~static_cast<uint16_t>(a));
}
inline bool operator!(InputKey a) {
	return !static_cast<bool>(a);
}
inline InputKey operator|=(InputKey& a, InputKey b) {
	return a = static_cast<InputKey>(static_cast<uint16_t>(a) | static_cast<uint16_t>(b));
}
inline InputKey operator&=(InputKey& a, InputKey b) {
	return a = static_cast<InputKey>(static_cast<uint16_t>(a) & static_cast<uint16_t>(b));
}
inline bool operator==(InputKey a, InputKey b) {
	return static_cast<uint16_t>(a) == static_cast<uint16_t>(b);
}


/**
 * @enum	AttackParameter
 * @brief   �U���̑���
 */
enum class AttackAttribute
{
	//! �����Ȃ�
	None			= 0,
	//! ���i����
	LowAttack		= 1,
	//! ���i����
	OverheadAttack	= 1 << 1,
	//! �_�E������
	KnockDown		= 1 << 2,
};

// �r�b�g���Z�p�̃w���p�[�֐�
inline AttackAttribute operator|(AttackAttribute a, AttackAttribute b) {
	return static_cast<AttackAttribute>(static_cast<uint16_t>(a) | static_cast<uint16_t>(b));
}
inline AttackAttribute operator&(AttackAttribute a, AttackAttribute b) {
	return static_cast<AttackAttribute>(static_cast<uint16_t>(a) & static_cast<uint16_t>(b));
}
inline AttackAttribute operator~(AttackAttribute a) {
	return static_cast<AttackAttribute>(~static_cast<uint16_t>(a));
}
inline bool operator!(AttackAttribute a) {
	return !static_cast<bool>(a);
}
inline AttackAttribute operator|=(AttackAttribute& a, AttackAttribute b) {
	return a = static_cast<AttackAttribute>(static_cast<uint16_t>(a) | static_cast<uint16_t>(b));
}
inline AttackAttribute operator&=(AttackAttribute& a, AttackAttribute b) {
	return a = static_cast<AttackAttribute>(static_cast<uint16_t>(a) & static_cast<uint16_t>(b));
}
inline bool operator==(AttackAttribute a, AttackAttribute b) {
	return static_cast<uint16_t>(a) == static_cast<uint16_t>(b);
}



// ---------------------------------------------------------------------



// �C�����C���֐� ------------------------------------------------------

/**
 * @brief �摜�T�C�Y���w�肵�ĉ摜��ǂݍ���
 * @param const char*[in] fileName �摜�t�@�C���̃p�X
 * @param int[in] sizeX �ύX���X���̃T�C�Y
 * @param int[in] sizeY �ύX���Y���̃T�C�Y
 * @return -1�̏ꍇ�̓G���[�����A����ȊO�͕ύX��̉摜�̃n���h��
 */
inline int LoadGraphBySpecifyingSize(const char* fileName, int _sizeX, int _sizeY)
{
	int originalHandle = LoadGraph(fileName);

	//�ǂݍ��݂Ɏ��s�����ꍇ�̓G���[(-1)��Ԃ�
	if (originalHandle == -1) {
		return -1;
	}
	//���݂̕`�悵�Ă����ʂ�ۑ����Ă���
	int nowScreen = GetDrawScreen();

	//!�w�肳�ꂽ�摜�T�C�Y�̃O���t�B�b�N�n���h�����쐬
	int resizedGrHandle = MakeScreen(_sizeX, _sizeY, TRUE);
	//�O���t�B�b�N�̍쐬�Ɏ��s�����ꍇ
	if (resizedGrHandle == -1) {
		DeleteGraph(originalHandle);
		return -1;
	}

	//�`����V���ɍ쐬�����n���h���Ɏw��
	SetDrawScreen(resizedGrHandle);
	//�w�肳�ꂽ�T�C�Y�ŕ`��
	DrawExtendGraph(0, 0, _sizeX, _sizeY, originalHandle, TRUE);

	//�s�v�ɂȂ����̂ŁA���T�C�Y�̉摜�n���h�����폜
	DeleteGraph(originalHandle);

	//�`���ʂ����ɖ߂�
	SetDrawScreen(nowScreen);

	return resizedGrHandle;
}

// ---------------------------------------------------------------------




// �萔��` ------------------------------------------------------------


//! �O�i�̃X�s�[�h
constexpr float WALK_SPEED = 3.5f;
//! ��ނ̃X�s�[�h
constexpr float BACK_SPEED = 2.5f;

//! �n��
constexpr float GROUND = 100.f;


// �A�j���[�V�����֌W

//! stIdol
constexpr float StIdleAnimSpeed = 0.2f;
//! Down
constexpr float DownAnimSpeed = 0.2f;
//! WakeUp
constexpr float WakeUpAnimSpeed = 0.2f;
//! Walk
constexpr float WalkAnimSpeed = 0.8f;
//! Back
constexpr float BackAnimSpeed = 0.5f;
//! Jump
constexpr float JumpAnimSpeed = 1.0f;
//! Fall
constexpr float FallAnimSpeed = 0.1f;
//! Landing
constexpr float LandingAnimSpeed = 0.9f;
//! StHa
constexpr float StHaAnimSpeed = 1.f;
//! StLa
constexpr float StLaAnimSpeed = 1.5f;

//! CrIdol
constexpr float CrIdolAnimSpeed = 0.2f;
//! CrHa
constexpr float CrHaAnimSpeed = 1.0f;
//! CrLa
constexpr float CrLaAnimSpeed = 1.0f;

//! Sp1
constexpr float Sp1AnimSpeed = 1.5f;
//! Sp2
constexpr float Sp2AnimSpeed = 1.0f;


//! StLa�̃_���[�W
constexpr int StLaDamage = 10;
//! StLa�̃q�b�g�d��
constexpr int StLaHitStun = 20;
//! StLa�̃K�[�h�d��
constexpr int StLaGuardStun = 20;

//! StHa�̃_���[�W
constexpr int StHaDamage = 60;
//! StHa�̃q�b�g�d��
constexpr int StHaHitStun = 60;
//! StHa�̃K�[�h�d��
constexpr int StHaGuardStun = 60;

//! CtLa�̃_���[�W
constexpr int CrLaDamage = 30;
//! CtLa�̃q�b�g�d��
constexpr int CrLaHitStun = 60;
//! CrLa�̃K�[�h�d��
constexpr int CrLaGuardStun = 20;

//! CrHa�̃_���[�W
constexpr int CrHaDamage = 60;
//! CrHa�̃q�b�g�d��
constexpr int CrHaHitStun = 60;
//! CrHa�̃K�[�h�d��
constexpr int CrHaGuardStun = 50;

//! Sp1�̃_���[�W
constexpr int Sp1Damage = 60;
//! Sp1�̃q�b�g�d��
constexpr int Sp1HitStun = 40;
//! Sp1�̃K�[�h�d��
constexpr int Sp1GuardStun = 40;

//! Sp2�̃_���[�W
constexpr int Sp2Damage = 80;
//! Sp2�̃q�b�g�d��
constexpr int Sp2HitStun = 70;
//! Sp2�̃K�[�h�d��
constexpr int Sp2GuardStun = 50;



// ---------------------------------------------------------------------




