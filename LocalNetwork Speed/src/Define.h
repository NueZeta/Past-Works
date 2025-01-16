#pragma once

#include "HandlerWaltanForDxLib.h"
#include <random>


//
// 定数定義
//

//#define DEBUG (1)

//! カード総数(ジョーカー除く)
const int CardTotalNumber = 52;

//! プレイヤー1の手札の初期枚数
const int InitialHandNumber_1p = 4;
//! プレイヤー1の手札の枚数上限
const int HandNumberLimit_1p = 4;

//! プレイヤー2の手札の初期枚数
const int InitialHandNumber_2p = 4;
//! プレイヤー2の手札の枚数上限
const int HandNumberLimit_2p = 4;

//! デッキの初期座標
const VECTOR DeckDefaultPosition = { 10,-10,0 };
//! 手札の初期座標
const VECTOR HandDefaultPosition = { 80,-15,0 };

//! 対戦相手のデッキの初期座標
const VECTOR OpponentDeckDefaultPosition = { 10,32,0 };
//! 対戦相手の手札の初期座標
const VECTOR OpponentHandDefaultPosition = { 80,37,0 };

//! フィールド(1レーン)初期座標
const VECTOR Field1DefaultPosition = { 70, 11, 0 };
//! フィールド(2レーン)初期座標
const VECTOR Field2DefaultPosition = { 90, 11, 0 };


/**
 * @enum	Suit
 * @brief	カードの柄
 */
enum class Suit
{
	//! ハート
	Heart = 0,
	//! ダイヤ
	Diamond = 1,
	//! クラブ
	Club = 2,
	//! スペード
	Spade = 3
};

/**
 * @enum	Area
 * @brief	カードが存在する領域
 */
enum class Area
{
	//! 山札
	Deck,
	//! 山札
	Deck_Opponent,
	//! フィールド1
	Field_1,
	//! フィールド2
	Field_2,
	//! 手札(1P)
	Hand,
	//! 手札(2P)
	Hand_Opponent
};

/**
 * @enum	ItemList
 * @brief	選択項目
 */
enum class ItemList
{
	//! 山札
	Deck,
	//! 手札1
	Hand_1,
	//! 手札2
	Hand_2,
	//! 手札3
	Hand_3,
	//! 手札4
	Hand_4,
	//! フィールド1
	Field_1,
	//! フィールド2
	Field_2,
};

/**
 * @enum	Direction
 * @brief	方向
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
 * @brief	ゲームのパラメータ
 */
enum class GameParameter
{
	//! セットアップ
	SetUp,
	//! ゲーム中
	Game,
	//! リザルト
	Result
};

/**
 * @enum	PlayerType
 * @brief	プレイヤーの種類
 */
enum class PlayerType
{
	//! ホスト
	Host,
	//! クライアント
	Client,
};

