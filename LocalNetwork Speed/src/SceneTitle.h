#pragma once
#include "SceneBase.h"

/**
* @author   Suzuki N
* @date     24/11/20
* @note		SceneTitleの定義ファイル
*/


/**
 * @class	SceneTitle
 * @brief   タイトルシーン
 */
class SceneTitle : public SceneBase
{
private:

	bool isConnect = false;
	bool isConnected = false;
	int netHandle;
	int connectTime = 0;

public:
	// メソッド

	/**
	 * @brief       コンストラクタ
	 * @author      Suzuki N
	 * @date        24/11/20
	 */
	SceneTitle();

	/**
	 * @brief       デストラクタ
	 * @author      Suzuki N
	 * @date        24/11/20
	 */
	~SceneTitle() override;

	/**
	 * @brief       毎F呼ばれるメソッド
	 * @author      Suzuki N
	 * @date        24/11/20
	 */
	void Update() override;
};

