#pragma once

//! デバッグモード
#define DEBUG (1)


// インクルードファイル ------------------------------------------------

#include <chrono>
#include <thread>
#include "HandlerWaltanForDxLib.h"
#include <math.h>
#include <iostream>
#include <cmath>

// ---------------------------------------------------------------------





// タグ ----------------------------------------------------------------


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
 * @brief	キャラクターの現在のパラメータ
 */
enum class Parameter
{
	//! ニュートラル状態(0)
	Neutral      = 0,
	//! しゃがみ(1)
	Crouching    = 1,
	//! 右を向いている(2)
	Facing_Right = 1 << 1,
	//! 前進(3)
	Walk         = 1 << 2,
	//! 後退(3)
	Back         = 1 << 3,
	//! ジャンプ(4)
	Jump		 = 1 << 4,
	//! ガード中(5)
	Guard        = 1 << 5,
	//! 食らい硬直(6)
	Hitstun      = 1 << 6,
	//! ガード硬直(7)
	Blockstun    = 1 << 7,
	//! ダウン中(8)
	Down		 = 1 << 8,
	//! 攻撃が相手にヒット(9)
	Hit          = 1 << 9,
	//! 弱攻撃(10)
	La           = 1 << 10,
	//! 強攻撃(11)
	Ha           = 1 << 11,
	//! 必殺技_1(12)
	Special_1    = 1 << 12,
	//! 必殺技_2(13)
	Special_2    = 1 << 13,
};

// ビット演算用のヘルパー関数
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
 * @brief	キャラクター1のアニメーション
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

	//! 末尾
	Left,
};


/**
 * @enum	InputKey
 * @brief   キー入力
 */
enum class InputKey
{
	//! 入力 -> 5
	Neutral = 0,
	//! 入力 -> 8
	Up      = 1,
	//! 入力 -> 2
	Down    = 1 << 1,
	//! 入力 -> 4
	Left    = 1 << 2,
	//! 入力 -> 6
	Right   = 1 << 3,
	//! 入力 -> 弱攻撃
	La      = 1 << 4,
	//! 入力 -> 強攻撃
	Ha      = 1 << 5,
};

// ビット演算用のヘルパー関数
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
 * @brief   攻撃の属性
 */
enum class AttackAttribute
{
	//! 属性なし
	None			= 0,
	//! 下段属性
	LowAttack		= 1,
	//! 中段属性
	OverheadAttack	= 1 << 1,
	//! ダウン属性
	KnockDown		= 1 << 2,
};

// ビット演算用のヘルパー関数
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



// インライン関数 ------------------------------------------------------

/**
 * @brief 画像サイズを指定して画像を読み込む
 * @param const char*[in] fileName 画像ファイルのパス
 * @param int[in] sizeX 変更後のX軸のサイズ
 * @param int[in] sizeY 変更後のY軸のサイズ
 * @return -1の場合はエラー発生、それ以外は変更後の画像のハンドル
 */
inline int LoadGraphBySpecifyingSize(const char* fileName, int _sizeX, int _sizeY)
{
	int originalHandle = LoadGraph(fileName);

	//読み込みに失敗した場合はエラー(-1)を返す
	if (originalHandle == -1) {
		return -1;
	}
	//現在の描画している画面を保存しておく
	int nowScreen = GetDrawScreen();

	//!指定された画像サイズのグラフィックハンドルを作成
	int resizedGrHandle = MakeScreen(_sizeX, _sizeY, TRUE);
	//グラフィックの作成に失敗した場合
	if (resizedGrHandle == -1) {
		DeleteGraph(originalHandle);
		return -1;
	}

	//描画先を新たに作成したハンドルに指定
	SetDrawScreen(resizedGrHandle);
	//指定されたサイズで描画
	DrawExtendGraph(0, 0, _sizeX, _sizeY, originalHandle, TRUE);

	//不要になったので、元サイズの画像ハンドルを削除
	DeleteGraph(originalHandle);

	//描画画面を元に戻す
	SetDrawScreen(nowScreen);

	return resizedGrHandle;
}

// ---------------------------------------------------------------------




// 定数定義 ------------------------------------------------------------


//! 前進のスピード
constexpr float WALK_SPEED = 3.5f;
//! 後退のスピード
constexpr float BACK_SPEED = 2.5f;

//! 地面
constexpr float GROUND = 100.f;


// アニメーション関係

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


//! StLaのダメージ
constexpr int StLaDamage = 10;
//! StLaのヒット硬直
constexpr int StLaHitStun = 20;
//! StLaのガード硬直
constexpr int StLaGuardStun = 20;

//! StHaのダメージ
constexpr int StHaDamage = 60;
//! StHaのヒット硬直
constexpr int StHaHitStun = 60;
//! StHaのガード硬直
constexpr int StHaGuardStun = 60;

//! CtLaのダメージ
constexpr int CrLaDamage = 30;
//! CtLaのヒット硬直
constexpr int CrLaHitStun = 60;
//! CrLaのガード硬直
constexpr int CrLaGuardStun = 20;

//! CrHaのダメージ
constexpr int CrHaDamage = 60;
//! CrHaのヒット硬直
constexpr int CrHaHitStun = 60;
//! CrHaのガード硬直
constexpr int CrHaGuardStun = 50;

//! Sp1のダメージ
constexpr int Sp1Damage = 60;
//! Sp1のヒット硬直
constexpr int Sp1HitStun = 40;
//! Sp1のガード硬直
constexpr int Sp1GuardStun = 40;

//! Sp2のダメージ
constexpr int Sp2Damage = 80;
//! Sp2のヒット硬直
constexpr int Sp2HitStun = 70;
//! Sp2のガード硬直
constexpr int Sp2GuardStun = 50;



// ---------------------------------------------------------------------




