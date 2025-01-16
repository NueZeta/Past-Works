#pragma once

/**
* @author   Suzuki N
* @date     24/10/02
* @note		定数やインクルードファイルをまとめたファイル
*/


#include "HandlerWaltanForDxLib.h"

#include <math.h>
#include <random>


// オブジェクトのタグ

/*
 * @ enum	Tag
 * @ brief	HWGameObjectに設定するタグ
 **/
enum class Tag
{
	//! 初期値(0)
	notFound,
	//! プレイヤー(1)
	player,
	//! エネミー(2)
	Enemy,
	//! ボス(2)
	Boss,
	//! 弾丸(4)
	Bullet,
};


// 定数定義

// デバッグモードで起動する
//#define DEBUG (1)


//! プレイヤーのデフォルト座標
constexpr VECTOR PLAYER_DEFAULT_POSISION = {200, 200, 0};
//! プレイヤーのデフォルト角度
constexpr VECTOR PLAYER_DEFAULT_ROTATE = { 0, 180, 0 };

//! プレイヤーのデフォルト体力
constexpr int PLAYER_DEFAULR_MAXHP = 200;
//! プレイヤーのデフォルト攻撃力 
constexpr int PLAYER_DEFAULT_ATTACKPOWER = 10;
//! プレイヤーのデフォルト移動スピード(x)
constexpr float PLAYER_DEFAULT_SPEED_HORIZON = 4.5f;
//! プレイヤーのデフォルト移動スピード(y)
constexpr float PLAYER_DEFAULT_SPEED_VERTICAL = 2.0f;
//! プレイヤーの自動スクロールのスピード(z)
constexpr float PLAYER_AUTOACROLL_SPEED = 5.0f;
//! プレイヤーのコライダーの半径
constexpr float PLAYER_COLLIDR_RADIUS = 20.0f;


//! 機体の移動による傾きの上限(x)
constexpr float AIRFRAME_MAX_SLOPE_X = 45.0f;
//! 機体の移動による傾きの上限(z)
constexpr float AIRFRAME_MAX_SLOPE_Z = 70.0f;
//! 機体の移動による傾きの速度(x)
constexpr float AIRFRAME_SLOPE_SPEED_X = 0.4f;
//! 機体の移動による傾きの速度(z)
constexpr float AIRFRAME_SLOPE_SPEED_Z = 0.7f;

//! 移動により機体が傾ている場合、平行に戻す力(z)
constexpr float POWER_RETURN_PARALLEL_Z = 10.f;
//! 移動により機体が傾ている場合、平行に戻す力(x)
constexpr float POWER_RETURN_PARALLEL_X = 20.f;

//! 移動制限(X)
constexpr float MOVE_RIGHT_LIMIT = 2500.f;
//! 移動制限(-X)
constexpr float MOVE_LEFT_LIMIT = -3000.f;
//! 移動制限(Y)
constexpr float MOVE_UP_LIMIT = 3500.f;
//! 移動制限(-Y)
constexpr float MOVE_DOWN_LIMIT = -1000.f;

//! プレイヤーが撃破されたときのスコア
constexpr int PLAYER_CRASH_SCORE = -10000;


//! エネミーのデフォルト角度
constexpr VECTOR ENEMY_DEFAULT_ROTATE = { 0, 180, 0 };
//! エネミーのデフォルトサイズ
constexpr VECTOR ENEMY_DEFAULT_SCALE = { 0.1f, 0.1f, 0.1f };

//! エネミーの初期座標
constexpr VECTOR ENEMY_DEFAULT_POSITION = { 0.0f, 0.0f, 2000.0f };

//! エネミーの生成する座標の揺れX
constexpr float ENEMY_POSITION_TREMOR_X = 200.0f;
//! エネミーの生成する座標の揺れY
constexpr float ENEMY_POSITION_TREMOR_Y = 200.0f;


//! エネミーのデフォルト体力
constexpr int ENEMY_DEFAULR_MAXHP = 15;
//! エネミーのデフォルト攻撃力 
constexpr int ENEMY_DEFAULT_ATTACKPOWER = 10;
//! エネミーのデフォルト移動スピード(x)
constexpr float ENEMY_DEFAULT_SPEED_HORIZON = 4.5f;
//! エネミーのデフォルト移動スピード(y)
constexpr float ENEMY_DEFAULT_SPEED_VERTICAL = 4.0f;
//! エネミーのコライダーの半径
constexpr float ENEMY_COLLIDR_RADIUS = 20.0f;

//! エネミーの自動スクロールのスピード(z)
constexpr float ENEMY_AUTOACROLL_SPEED = 3.f;

//! 出現するEnemyの最大数
constexpr int ENEMY_MAX_NUM = 15;
//! Enemyが生成されるスパン
constexpr int ENEMY_POP_SPAN = 2 * 1000;

//! Enemyが攻撃するスパン
constexpr int ENEMY_SHOOTING_SPAN = 1500;

//! Enemyを倒したときのスコア
constexpr int ENEMY_CRASH_SCORE = 1000;
//! Enemyが画面移動により削除された際のスコア減少値
constexpr int ENEMY_ERASE_SCORE = -150;


//! カメラとプレイヤーの距離
constexpr VECTOR CAMERA_POSITION = { 0, 50, 0 };
//! カメラとプレイヤーの距離
constexpr VECTOR CAMERA_DEFAULT_POSITION = { 0, 50, -350 };



//! 弾丸のデフォルトサイズ
constexpr VECTOR BULLET_DEFAULT_SCALE = { 0.005f, 0.005f, 0.005f };
//! エネミーのデフォルト角度
constexpr VECTOR BULLET_DEFAULT_ROTATE = { 90, 0, 0 };

//! 弾丸の速度
constexpr float BULLET_SPEED = PLAYER_AUTOACROLL_SPEED * 4;
//! 弾丸のコライダーの半径
constexpr float BULLET_COLLIDR_RADIUS = 4.0f;
//! 弾丸が消えるまでの時間
constexpr int BULLET_TIME_TO_LIVE = 3 * 1000;


//! ブースターのエフェクトのサイズ
constexpr float BOOSTER_EFFECT_SIZE = 3.0f;

//! 撃破時のエフェクトのサイズ
constexpr float CRUSHING_EFFECT_SIZE = 15.0f;

//! HIT時のエフェクトのサイズ
constexpr float HIT_EFFECT_SIZE = 20.0f;


//! ボスがエントリーするまでの時間
constexpr int TIMER_FOR_BOSS_TO_ENTRY = 90 * 1000;
//! ボス出現までの時間
constexpr int BOSS_ENTRY = 5 * 1000;


//! PLAYERが倒されたとき、次のシーンへ移行するまでの時間
constexpr int PLAYER_CRASH_TIME = 3 * 1000;
//! ボスを倒してクリアしたとき、次のシーンへ移行するまでの時間
constexpr int BOSS_CRASH_TIME = 5 * 1000;


//! ボスのデフォルト体力
constexpr int BOSS_DEFAULR_MAXHP = 1200;
//! ボスのデフォルト攻撃力 
constexpr int BOSS_DEFAULT_ATTACKPOWER = 15;
//! ボスの移動速度
constexpr float BOSS_MOVE_SPEED = 5;

//! ボスのデフォルト座標
constexpr VECTOR BOSS_DEFAULT_POSITION = { 0, 1000, 1000 };
//! ボスのデフォルト角度
constexpr VECTOR BOSS_DEFAULT_ROTATE = { 0, 180, 0 };
//! ボスのデフォルトサイズ
constexpr VECTOR BOSS_DEFAULT_SCALE = { 0.5f, 0.5f, 0.5f };

//! ボスのコライダーの半径
constexpr float BOSS_COLLIDR_RADIUS = 100.0f;

//! ボスが次の行動に移るまでの時間
constexpr int BOSS_TIME_UNTIL_NEXT_ACTION = 2 * 1000;

//! ボスの攻撃の間隔
constexpr int BOSS_FIRE_SPAN = 100;



//! Enemyを倒したときのスコア
constexpr int BOSS_CRASH_SCORE = 20000;

//! ノーダメージのスコア加算
constexpr int NO_DAMAGE_SCORE = 100000;

//! ぎりぎりクリアのスコア加算
constexpr int MORTAL_COMBAT_SCORE = 70000;


