#pragma once
#include "GameManager.h"
#include "StageModel.h"
#include "StageView.h"
#include"VampirePresenter.h"

/**
* @author   Suzuki N
* @date     24/11/05
* @note		StagePresenterの定義ファイル
*/


/**
 * @class	StagePresenter
 * @brief   ステージオブジェクトのプレゼンターコンポーネント
 */
class StagePresenter : public HWComponent
{
public:
	// メンバ変数

	//! モデル
	std::unique_ptr<StageModel> model;
	//! ビューコンポーネント
	StageView* view;


	// メソッド

	/**
	 * @brief		明示的に呼ぶ必要のある初期化メソッド
	 * @author      Suzuki N
	 * @date        24/11/05
	 */
	void Initialize(VampirePresenter* _presenter1, VampirePresenter* _presenter2);



#pragma region オーバライド関数


	/**
	 * @brief		インスタンス化したときに呼ばれるメソッド
	 * @author      Suzuki N
	 * @date        24/10/31
	 */
	void Awake() override;

	/**
	 * @brief		毎F呼ばれるメソッド
	 * @author      Suzuki N
	 * @date        24/10/31
	 */
	void Update() override;

#pragma endregion

};

