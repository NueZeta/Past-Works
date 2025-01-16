#pragma once
#include "Airframe.h"
#include "PlayerController.h"

/**
* @author   Suzuki N
* @date     24/10/02
* @note		プレイヤーが操作するPlayerクラスの定義ファイル
*/


/**
 * @class	Player
 * @brief   プレイヤーが操作する機体クラス
 */
class Player
{
public:
	// メンバ変数

	//! PlayerのGameObject
	std::unique_ptr<HWGameObject> player;
	//! プレイヤーコントローラ
	PlayerController* controller;
	//! プレイヤーの当たり判定(カプセル型)
	HWCapsuleCollider* capsuleCol;
	//! CameraのGameObject
	std::unique_ptr<HWGameObject> camera;
	//! キャラクター操作用のInputSystem
	std::shared_ptr<InputSystem> input;
	

public:
	// メソッド

	// コンストラクタ
	Player();

	// デストラクタ
	~Player();
};

