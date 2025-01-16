#pragma once
#include "ProjectileModel.h"
#include "ProjectileView.h"
#include "VampirePresenter.h"

/**
* @author   Suzuki N
* @date     24/11/05
* @note		ProjectilePresenterの定義ファイル
*/


/**
 * @class	ProjectilePresenter
 * @brief   飛び道具の攻撃判定の管理クラス
 */
class ProjectilePresenter : public HWComponent
{
public:
	//  メンバ変数

	//! モデルクラス
	std::unique_ptr <ProjectileModel> model;
	//! ビューコンポーネント
	ProjectileView* view;


public:
	// メンバ関数

	/**
	 * @brief		コリジョン情報を設定する
	 * @param[in]	VampireModel*	自身のモデル
	 * @param[in]	const int	モデルハンドル
	 * @param[in]	const int	エフェクトハンドル
	 * @param[in]	const VECTOR 座標
	 * @param[in]	const float	当たり判定の半径
	 * @param[in]	const int	Hit時のダメージ
	 * @param[in]	const int	Hit時の硬直
	 * @param[in]	const int	Guard時の硬直
	 * @param[in]	const float	移動スピード
	 * @author      Suzuki N
	 * @date        24/10/31
	 */
	void CollisionSet(VampireModel* _model, const int _effecthandle, const VECTOR _pos, const float _attackColRadius,
		const int _damage, const int hitStun, const int guardStun, const float _speed, AttackAttribute _attribute);

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
	 * @brief		削除時に呼ばれるメソッド
	 * @author      Suzuki N
	 * @date        24/10/31
	 */
	void OnDestroy() override;


	/**
	 * @brief		トリガーコライダーと衝突した瞬間に呼ばれるメソッド
	 * @author      Suzuki N
	 * @date        24/10/31
	 */
	void OnTriggerEnter(HWCollider& other)override;

#pragma endregion

};

