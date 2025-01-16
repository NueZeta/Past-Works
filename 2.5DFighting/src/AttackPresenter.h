#pragma once
#include "AttackModel.h"
#include "AttackView.h"
#include "VampirePresenter.h"

/**
* @author   Suzuki N
* @date     24/10/31
* @note		AttackPresenterの定義ファイル
*/


/**
 * @class	AttackPresenter
 * @brief   攻撃判定の管理クラス
 */
class AttackPresenter : public HWComponent
{
public:
	//  メンバ変数

	//! モデルクラス
	std::unique_ptr<AttackModel> model;
	//! ビューコンポーネント
	AttackView* view;


public:
	// メンバ関数

	/**
	 * @brief		コリジョン情報を設定する
	 * @param[in]	VampireModel*	自身のモデル
	 * @param[in]	const int	モデルハンドル
	 * @param[in]	const int	当たり判定の中心になるモデルのフレーム(右向きの場合)
	 * @param[in]	const int	当たり判定の中心になるモデルのフレーム(左向きの場合)
	 * @param[in]	const float	当たり判定の半径
	 * @param[in]	const int	Hit時のダメージ
	 * @param[in]	const int	Hit時の硬直
	 * @param[in]	const int	Guard時の硬直
	 * @author      Suzuki N
	 * @date        24/10/31
	 */
	void CollisionSet(VampireModel* _model, const int _modelHandle, const int _centerFrame_right, const int _centerFrame_left, 
		const float _attackColRadius, const int _damage, const int hitStun, const int guardStun, AttackAttribute _attribute);

	/**
	 * @brief		コリジョンを切る
	 * @author      Suzuki N
	 * @date        24/10/31
	 */
	void CollisionDisable() { model->attackCol->active = false; }

	/**
	 * @brief		コリジョンをつける
	 * @author      Suzuki N
	 * @date        24/10/31
	 */
	void CollisionEnable() { model->attackCol->active = true; }


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

	/**
	 * @brief		トリガーコライダーと衝突した瞬間に呼ばれるメソッド
	 * @author      Suzuki N
	 * @date        24/10/31
	 */
	void OnTriggerEnter(HWCollider& other)override;

#pragma endregion

};

