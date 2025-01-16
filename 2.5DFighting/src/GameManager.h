#pragma once
#include "Define.h"


enum class GameParam
{
	//! Title
	Title		= 1,
	//! �Z�b�g�A�b�v��
	SetUp		= 1 << 1,
	//! �Q�[����
	Game		= 1 << 2,
	//! �ǂ��炩�̃L�����N�^�[�̗̑͂�0�ɂȂ���
	KO			= 1 << 3,
	//! result
	Result		= 1 << 4,
};

inline GameParam operator|(GameParam a, GameParam b) {
	return static_cast<GameParam>(static_cast<uint16_t>(a) | static_cast<uint16_t>(b));
}
inline GameParam operator&(GameParam a, GameParam b) {
	return static_cast<GameParam>(static_cast<uint16_t>(a) & static_cast<uint16_t>(b));
}
inline GameParam operator~(GameParam a) {
	return static_cast<GameParam>(~static_cast<uint16_t>(a));
}
inline bool operator!(GameParam a) {
	return !static_cast<bool>(a);
}
inline GameParam operator|=(GameParam& a, GameParam b) {
	return a = static_cast<GameParam>(static_cast<uint16_t>(a) | static_cast<uint16_t>(b));
}
inline GameParam operator&=(GameParam& a, GameParam b) {
	return a = static_cast<GameParam>(static_cast<uint16_t>(a) & static_cast<uint16_t>(b));
}
inline bool operator==(GameParam a, GameParam b) {
	return static_cast<uint16_t>(a) == static_cast<uint16_t>(b);
}


class GameManager
{
public:
	// �����o�ϐ�

	//! ���݂̃Q�[���p�����[�^
	static GameParam param;
	//! �Q�[���J�n����
	static int startTime;
	//! ��ʃT�C�YX
	static int screenWidth;
	//! ��ʃT�C�YY
	static int screenHeight;
};