#pragma once
#include "Define.h"

/**
* @author   Suzuki N
* @date     24/10/02
* @note		���ׂĂ̋@�̂̊��N���X�ƂȂ�Airframe�N���X�̒�`�t�@�C��
*/


/**
 * @class	Airframe
 * @brief   �@�̂ɕK�v�Ȓl�������N���X
 */
class Airframe
{
public:
	// �����o�ϐ�

	//! �ő�HP
	int maxHp;
	//! HP
	int hp;
	//! �U����(1HIT������)
	int attackPower;
	//! �㉺�̈ړ����x
	float verticalSpeed;
	//! ���E�̈ړ����x
	float horizonSpeed;
	//! ���ăt���O
	bool isShootingDown;


protected:
	// ���\�b�h

	// �R���X�g���N�^
	// ���N���X�̂��߁A�C���X�^���X���쐬�ł��Ȃ��悤�ɂ���
	Airframe() : maxHp(-1), hp(-1), attackPower(-1), verticalSpeed(0.0f),
		horizonSpeed(0.0f), isShootingDown(false)
	{}

public:

	// HP���擾����
	inline int GetHp()const { return hp; }
	// �ő�HP���擾����
	inline int GetMaxHp()const { return maxHp; }

	// �f�X�g���N�^
	// ���z�֐�
	virtual ~Airframe(){}
};