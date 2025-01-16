#pragma once
#include "SceneBase.h"

/**
* @author   Suzuki N
* @date     24/10/01
* @note		SceneTitleの定義ファイル
*/


/**
 * @class	SceneTitle
 * @brief   タイトルシーン
 */
class SceneTitle : public SceneBase
{
private:
	// メンバ変数

	//! タイトルロゴのフォントデータ
	int logoFontHandle;
	//! 文字列を点滅させる
	int flashingInterval;


public:
	// メソッド

	// コンストラクタ
	SceneTitle(InputSystem* _input);

	// デストラクタ
	~SceneTitle() override;

	// 毎F呼ばれる関数
	// オーバライドメソッド
	void Update() override;
};

