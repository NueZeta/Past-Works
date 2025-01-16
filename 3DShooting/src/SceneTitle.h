#pragma once
#include "SceneBase.h"
#include "Score.h"

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


public:
	// メソッド

	// コンストラクタ
	SceneTitle(InputSystem* _Input);

	// デストラクタ
	~SceneTitle() override;

	// 毎F呼ばれる関数
	// オーバライドメソッド
	void Update() override;
};

