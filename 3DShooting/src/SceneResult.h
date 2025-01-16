#pragma once
#include "SceneBase.h"
#include "Score.h"

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
	int highestScore = -1;


public:
	// メソッド

	// コンストラクタ
	SceneResult(InputSystem* _Input);

	// デストラクタ
	~SceneResult() override;

	// 毎F呼ばれる関数
	// オーバライドメソッド
	void Update() override;
};

