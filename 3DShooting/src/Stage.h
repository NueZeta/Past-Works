#pragma once
#include "Define.h"
#include "Player.h"

/**
* @author   Suzuki N
* @date     24/10/02
* @note		Stageクラスの定義ファイル
*/


/**
 * @class	Stage
 * @brief   背景オブジェクトのクラス
 * @detail	二つのマップオブジェクトを交互に移動させてマップをループさせる
 */
class Stage : public HWComponent
{
public:
	// メンバ変数

	//! playerオブジェクト
	Player* player;
	//! スカイボックスのモデルハンドル
	int skyBoxModelHandle;
	//! ライトハンドル
	int lightHandle;


public:
	// メソッド

	// コンストラクタ
	Stage(Player* _player);
	// デストラクタ
	~Stage();

	/**
	 * @brief		オブジェクトにアタッチされたときに働くメソッド
	 * @author      Suzuki N
	 * @date        24/10/02
	 */
	void Awake()override;

	/**
	 * @brief		最初のUpdateメソッドの直前に働く
	 * @author      Suzuki N
	 * @date        24/10/04
	 */
	void Start()override;

	/**
	 * @brief		毎F呼ばれるメソッド
	 * @author      Suzuki N
	 * @date        24/10/02
	 */
	void Update()override;
};

