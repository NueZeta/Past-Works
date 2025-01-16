#pragma once
#include "Define.h"


enum class GameParam
{
	//! Title
	Title		= 1,
	//! セットアップ中
	SetUp		= 1 << 1,
	//! ゲーム中
	Game		= 1 << 2,
	//! どちらかのキャラクターの体力が0になった
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
	// メンバ変数

	//! 現在のゲームパラメータ
	static GameParam param;
	//! ゲーム開始時刻
	static int startTime;
	//! 画面サイズX
	static int screenWidth;
	//! 画面サイズY
	static int screenHeight;
};