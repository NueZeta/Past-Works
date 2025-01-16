#pragma once

/**
* @author   Suzuki N
* @date     24/10/02
* @note		�萔��C���N���[�h�t�@�C�����܂Ƃ߂��t�@�C��
*/


#include "HandlerWaltanForDxLib.h"

#include <math.h>
#include <random>


// �I�u�W�F�N�g�̃^�O

/*
 * @ enum	Tag
 * @ brief	HWGameObject�ɐݒ肷��^�O
 **/
enum class Tag
{
	//! �����l(0)
	notFound,
	//! �v���C���[(1)
	player,
	//! �G�l�~�[(2)
	Enemy,
	//! �{�X(2)
	Boss,
	//! �e��(4)
	Bullet,
};


// �萔��`

// �f�o�b�O���[�h�ŋN������
//#define DEBUG (1)


//! �v���C���[�̃f�t�H���g���W
constexpr VECTOR PLAYER_DEFAULT_POSISION = {200, 200, 0};
//! �v���C���[�̃f�t�H���g�p�x
constexpr VECTOR PLAYER_DEFAULT_ROTATE = { 0, 180, 0 };

//! �v���C���[�̃f�t�H���g�̗�
constexpr int PLAYER_DEFAULR_MAXHP = 200;
//! �v���C���[�̃f�t�H���g�U���� 
constexpr int PLAYER_DEFAULT_ATTACKPOWER = 10;
//! �v���C���[�̃f�t�H���g�ړ��X�s�[�h(x)
constexpr float PLAYER_DEFAULT_SPEED_HORIZON = 4.5f;
//! �v���C���[�̃f�t�H���g�ړ��X�s�[�h(y)
constexpr float PLAYER_DEFAULT_SPEED_VERTICAL = 2.0f;
//! �v���C���[�̎����X�N���[���̃X�s�[�h(z)
constexpr float PLAYER_AUTOACROLL_SPEED = 5.0f;
//! �v���C���[�̃R���C�_�[�̔��a
constexpr float PLAYER_COLLIDR_RADIUS = 20.0f;


//! �@�̂̈ړ��ɂ��X���̏��(x)
constexpr float AIRFRAME_MAX_SLOPE_X = 45.0f;
//! �@�̂̈ړ��ɂ��X���̏��(z)
constexpr float AIRFRAME_MAX_SLOPE_Z = 70.0f;
//! �@�̂̈ړ��ɂ��X���̑��x(x)
constexpr float AIRFRAME_SLOPE_SPEED_X = 0.4f;
//! �@�̂̈ړ��ɂ��X���̑��x(z)
constexpr float AIRFRAME_SLOPE_SPEED_Z = 0.7f;

//! �ړ��ɂ��@�̂��X�Ă���ꍇ�A���s�ɖ߂���(z)
constexpr float POWER_RETURN_PARALLEL_Z = 10.f;
//! �ړ��ɂ��@�̂��X�Ă���ꍇ�A���s�ɖ߂���(x)
constexpr float POWER_RETURN_PARALLEL_X = 20.f;

//! �ړ�����(X)
constexpr float MOVE_RIGHT_LIMIT = 2500.f;
//! �ړ�����(-X)
constexpr float MOVE_LEFT_LIMIT = -3000.f;
//! �ړ�����(Y)
constexpr float MOVE_UP_LIMIT = 3500.f;
//! �ړ�����(-Y)
constexpr float MOVE_DOWN_LIMIT = -1000.f;

//! �v���C���[�����j���ꂽ�Ƃ��̃X�R�A
constexpr int PLAYER_CRASH_SCORE = -10000;


//! �G�l�~�[�̃f�t�H���g�p�x
constexpr VECTOR ENEMY_DEFAULT_ROTATE = { 0, 180, 0 };
//! �G�l�~�[�̃f�t�H���g�T�C�Y
constexpr VECTOR ENEMY_DEFAULT_SCALE = { 0.1f, 0.1f, 0.1f };

//! �G�l�~�[�̏������W
constexpr VECTOR ENEMY_DEFAULT_POSITION = { 0.0f, 0.0f, 2000.0f };

//! �G�l�~�[�̐���������W�̗h��X
constexpr float ENEMY_POSITION_TREMOR_X = 200.0f;
//! �G�l�~�[�̐���������W�̗h��Y
constexpr float ENEMY_POSITION_TREMOR_Y = 200.0f;


//! �G�l�~�[�̃f�t�H���g�̗�
constexpr int ENEMY_DEFAULR_MAXHP = 15;
//! �G�l�~�[�̃f�t�H���g�U���� 
constexpr int ENEMY_DEFAULT_ATTACKPOWER = 10;
//! �G�l�~�[�̃f�t�H���g�ړ��X�s�[�h(x)
constexpr float ENEMY_DEFAULT_SPEED_HORIZON = 4.5f;
//! �G�l�~�[�̃f�t�H���g�ړ��X�s�[�h(y)
constexpr float ENEMY_DEFAULT_SPEED_VERTICAL = 4.0f;
//! �G�l�~�[�̃R���C�_�[�̔��a
constexpr float ENEMY_COLLIDR_RADIUS = 20.0f;

//! �G�l�~�[�̎����X�N���[���̃X�s�[�h(z)
constexpr float ENEMY_AUTOACROLL_SPEED = 3.f;

//! �o������Enemy�̍ő吔
constexpr int ENEMY_MAX_NUM = 15;
//! Enemy�����������X�p��
constexpr int ENEMY_POP_SPAN = 2 * 1000;

//! Enemy���U������X�p��
constexpr int ENEMY_SHOOTING_SPAN = 1500;

//! Enemy��|�����Ƃ��̃X�R�A
constexpr int ENEMY_CRASH_SCORE = 1000;
//! Enemy����ʈړ��ɂ��폜���ꂽ�ۂ̃X�R�A�����l
constexpr int ENEMY_ERASE_SCORE = -150;


//! �J�����ƃv���C���[�̋���
constexpr VECTOR CAMERA_POSITION = { 0, 50, 0 };
//! �J�����ƃv���C���[�̋���
constexpr VECTOR CAMERA_DEFAULT_POSITION = { 0, 50, -350 };



//! �e�ۂ̃f�t�H���g�T�C�Y
constexpr VECTOR BULLET_DEFAULT_SCALE = { 0.005f, 0.005f, 0.005f };
//! �G�l�~�[�̃f�t�H���g�p�x
constexpr VECTOR BULLET_DEFAULT_ROTATE = { 90, 0, 0 };

//! �e�ۂ̑��x
constexpr float BULLET_SPEED = PLAYER_AUTOACROLL_SPEED * 4;
//! �e�ۂ̃R���C�_�[�̔��a
constexpr float BULLET_COLLIDR_RADIUS = 4.0f;
//! �e�ۂ�������܂ł̎���
constexpr int BULLET_TIME_TO_LIVE = 3 * 1000;


//! �u�[�X�^�[�̃G�t�F�N�g�̃T�C�Y
constexpr float BOOSTER_EFFECT_SIZE = 3.0f;

//! ���j���̃G�t�F�N�g�̃T�C�Y
constexpr float CRUSHING_EFFECT_SIZE = 15.0f;

//! HIT���̃G�t�F�N�g�̃T�C�Y
constexpr float HIT_EFFECT_SIZE = 20.0f;


//! �{�X���G���g���[����܂ł̎���
constexpr int TIMER_FOR_BOSS_TO_ENTRY = 90 * 1000;
//! �{�X�o���܂ł̎���
constexpr int BOSS_ENTRY = 5 * 1000;


//! PLAYER���|���ꂽ�Ƃ��A���̃V�[���ֈڍs����܂ł̎���
constexpr int PLAYER_CRASH_TIME = 3 * 1000;
//! �{�X��|���ăN���A�����Ƃ��A���̃V�[���ֈڍs����܂ł̎���
constexpr int BOSS_CRASH_TIME = 5 * 1000;


//! �{�X�̃f�t�H���g�̗�
constexpr int BOSS_DEFAULR_MAXHP = 1200;
//! �{�X�̃f�t�H���g�U���� 
constexpr int BOSS_DEFAULT_ATTACKPOWER = 15;
//! �{�X�̈ړ����x
constexpr float BOSS_MOVE_SPEED = 5;

//! �{�X�̃f�t�H���g���W
constexpr VECTOR BOSS_DEFAULT_POSITION = { 0, 1000, 1000 };
//! �{�X�̃f�t�H���g�p�x
constexpr VECTOR BOSS_DEFAULT_ROTATE = { 0, 180, 0 };
//! �{�X�̃f�t�H���g�T�C�Y
constexpr VECTOR BOSS_DEFAULT_SCALE = { 0.5f, 0.5f, 0.5f };

//! �{�X�̃R���C�_�[�̔��a
constexpr float BOSS_COLLIDR_RADIUS = 100.0f;

//! �{�X�����̍s���Ɉڂ�܂ł̎���
constexpr int BOSS_TIME_UNTIL_NEXT_ACTION = 2 * 1000;

//! �{�X�̍U���̊Ԋu
constexpr int BOSS_FIRE_SPAN = 100;



//! Enemy��|�����Ƃ��̃X�R�A
constexpr int BOSS_CRASH_SCORE = 20000;

//! �m�[�_���[�W�̃X�R�A���Z
constexpr int NO_DAMAGE_SCORE = 100000;

//! ���肬��N���A�̃X�R�A���Z
constexpr int MORTAL_COMBAT_SCORE = 70000;


