#pragma once
#include "SceneBase.h"

/**
* @author   Suzuki N
* @date     24/10/01
* @note		SceneResultの定義ファイル
*/


/**
 * @class	SceneResult
 * @brief   リザルトシーン
 */
class SceneResult : public SceneBase
{
private:
	// メンバ変数

	//! フォントデータ
	int fontHandle;
	//! 文字列を点滅させる
	int flashingInterval;


public:
	// メソッド

	// コンストラクタ
	SceneResult(InputSystem* _input);

	// デストラクタ
	~SceneResult() override;

	// 毎F呼ばれる関数
	// オーバライドメソッド
	void Update() override;
};

