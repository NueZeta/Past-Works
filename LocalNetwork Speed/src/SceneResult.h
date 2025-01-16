#pragma once
#include "SceneBase.h"

/**
* @author   Suzuki N
* @date     24/11/20
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


public:
	// メソッド

	/**
	 * @brief       コンストラクタ
	 * @author      Suzuki N
	 * @date        24/11/20
	 */
	SceneResult();

	/**
	 * @brief       デストラクタ
	 * @author      Suzuki N
	 * @date        24/11/20
	 */
	~SceneResult() override;

	/**
	 * @brief       毎F呼ばれるメソッド
	 * @author      Suzuki N
	 * @date        24/11/20
	 */
	void Update() override;
};

