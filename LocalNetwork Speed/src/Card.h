/**
 * @file	Card.h
 * @brief	各カードごとのパラメータ
 * @author	NS
 * @date	2024/1/2
 */

#pragma once
#include "GameManager.h"


 /**
  * @class	Card
  * @brief  カード一枚ごとにもつクラス
  */
class Card
{
	//
	// メンバ変数
	//

public:

	//! 自身のマーク
	Suit suit;
	//! 自身の数字
	int number;
	//! 自身がいる領域
	Area area;
	//! 自身が属する領域の何枚目か
	int areaNumber;
	//! 座標
	VECTOR position;
	//! 回転
	VECTOR rotation;
	//! 拡縮
	VECTOR scale;
	//! 初期座標
	VECTOR defaultPosition;
	//! 初期回転
	VECTOR defaultRotate;
	//! 自身のフレーム番号
	int frameIndex;
	//! カード全体のモデルハンドル
	static int modelHandle;

	//! 移動中のフラグ
	bool isMove;

private:

	//! 移動アニメーションの目標地点
	VECTOR targetPos;
	//! 移動アニメーションの開始地点
	VECTOR startPos;


	//
	// メソッド
	//

public:

	/**
	 * @brief		コンストラクタ
	 */
	Card(Suit, int);

	/**
	 * @brief		コンストラクタ
	 */
	Card() {}

	/**
	 * @brief		デストラクタ
	 */
	~Card();

	/**
	 * @brief		領域が変わった時のアニメーション
	 */
	void AreaChangeAnimStart(Area _prevArea, Area _newArea);

	/**
	 * @brief		明示的な更新処理
	 */
	void ManualUpdate();

private:

	/**
	 * @brief		座標の更新処理
	 */
	void PositionUpdate();

	/**
	 * @brief		領域が変わった時のアニメーション
	 */
	void AreaChangeAnimation();

};


#pragma pack(1)

/**
 * @class	CardData
 * @brief  データ送信用
 */
struct CardData
{
	unsigned char data;
	unsigned char area;
	unsigned char areaNumber;
};

#pragma pack()