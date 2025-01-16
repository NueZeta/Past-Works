#pragma once
#include "VampireModel.h"
#include "VampireView.h"
#include "AttackPresenter.h"
#include "ProjectilePresenter.h"
#include "StageModel.h"


/**
* @author   Suzuki N
* @date     24/10/29
* @note		VampirePresenterの定義ファイル
*/


/**
 * @class	VampirePresenter
 * @brief   キャラクター1の管理クラス
 */
class VampirePresenter : public HWComponent
{
public:
	//  メンバ変数

	//! モデルクラス
	std::unique_ptr<VampireModel> model;
	//! ビューコンポーネント
	VampireView* view;
	//! 相手のGameObject
	HWGameObject* opponent;

	
	// メンバ関数
private:

	/**
	 * @brief		現在のパラメータを参照して、アニメーションをセットする
	 * @author      Suzuki N
	 * @date        24/10/29
	 */
	void AnimChange();

	/**
	 * @brief		最新の入力を参照してパラメータをセットする
	 * @author      Suzuki N
	 * @date        24/10/29
	 */
	void ParameterSet();

	/**
	 * @brief		コマンド必殺技が成立しているかを調べる
	 * @param[in]	const Parameter&  押したキー
	 * @return		const Parameter　成立したアクション
	 * @author      Suzuki N
	 * @date        24/10/31
	 */
	const Parameter CommandCheck(const Parameter& _param);

	/**
	 * @brief		現在のパラメータを参照して、移動処理を行う
	 * @author      Suzuki N
	 * @date        24/10/29
	 */
	void Move();

	/**
	 * @brief		現在のパラメータがジャンプ中ならば行われる処理
	 * @author      Suzuki N
	 * @date        24/11/11
	 */
	void Jump();

	/**
	 * @brief		攻撃アニメーション終了時に呼ばれるメソッド
	 * @author      Suzuki N
	 * @date        24/10/29
	 */
	void AttackAnimEnd();

	/**
	 * @brief		ガードアニメーション終了時に呼ばれるメソッド
	 * @author      Suzuki N
	 * @date        24/10/29
	 */
	void GuardAnimEnd();

	/**
	 * @brief		ヒットアニメーション終了時に呼ばれるメソッド
	 * @author      Suzuki N
	 * @date        24/10/29
	 */
	void HitAnimEnd();

	/**
	 * @brief		キー入力時に呼ばれるコールバック
	 * @author      Suzuki N
	 * @date        24/10/29
	 */
	void OnKeyCheck(InputAction::CallBackContext& context);

	/**
	 * @brief		体力が0になった際の処理
	 * @author      Suzuki N
	 * @date        24/10/29
	 */
	void Dead();


	void Debug();

public:

	/**
	 * @brief		攻撃を受けた際の処理
	 * @param[in]	const AttackPresenter* Hitした攻撃情報
	 * @return		bool ? Hitした(true) : Guardされた(false)
	 * @author      Suzuki N
	 * @date        24/10/29
	 */
	bool AttackHit(const AttackPresenter* _attackPresenter);

	/**
	 * @brief		攻撃を受けた際の処理
	 * @param[in]	const ProjectilePresenter* Hitした攻撃情報
	 * @return		bool ? Hitした(true) : Guardされた(false)
	 * @author      Suzuki N
	 * @date        24/10/29
	 */
	bool AttackHit(const ProjectilePresenter* _attackPresenter);



#pragma region オーバライド関数


	/**
	 * @brief		インスタンス化したときに呼ばれるメソッド
	 * @author      Suzuki N
	 * @date        24/10/29
	 */
	void Awake() override;

	/**
	 * @brief		毎F呼ばれるメソッド
	 * @author      Suzuki N
	 * @date        24/10/29
	 */
	void Update() override;

	/**
	 * @brief		トリガーコライダーと衝突した瞬間に呼ばれるメソッド
	 * @author      Suzuki N
	 * @date        24/10/29
	 */
	void OnTriggerStay(HWCollider& other)override;

#pragma endregion

};

