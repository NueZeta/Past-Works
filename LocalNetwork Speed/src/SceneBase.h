#pragma once
#include "GameManager.h"

/**
* @author   Suzuki N
* @date     24/11/20
* @note		SceneBaseの定義ファイル
*/


/**
 * @enum	SceneTag
 * @brief   シーンのタグ
 */
enum class SceneTag
{
	//! タイトルシーン(0)
	Title,
	//! ゲームシーン(1)
	Game,
	//! リザルトシーン(2)
	Result,

	/*
		追加する場合は、ここにタグを追加し、SceneManagerのSceneChangeメソッドに追記する
	*/

	//! 未使用 (常に末尾)
	NotFound = -1,
};


/**
 * @enum	SceneLoadState
 * @brief   シーンロードのステータス
 */
enum class SceneLoadState
{
	//! 待機中(0)
	Wait,
	//! ロード中(1)
	Loading,
	//! ロード完了(2)
	Completed,
};


/**
 * @class	SceneBase
 * @brief   各シーンのもとになる基底クラス
 * @detail	仮想クラスのため、インスタンスを作成できない
 */
class SceneBase
{
	friend class SceneManager;

protected:
	//  メンバ変数

	//! シーンのタグ
	SceneTag sceneTag;
	//! 遷移先のシーンタグ
	SceneTag nextSceneTag;
	//! 非同期で読み込む遷移先のシーンタグ
	SceneTag nextSceneTagAsync;
	//! SceneManagerが持つInputSystem
	InputSystem* input;
	//! シーン遷移のコールバック関数のID
	int callBackId;


	// メンバ関数

	/**
	 * @brief       コンストラクタ
	 * @author      Suzuki N
	 * @date        24/11/20
	 */
	SceneBase() : nextSceneTag(SceneTag::NotFound), nextSceneTagAsync(SceneTag::NotFound)
	{}

	/**
	 * @brief       シーン内からシーンを変更する
	 * @param[in]	const SceneTag 変更先のシーンタグ
	 * @author      Suzuki N
	 * @date        24/11/20
	 */
	void SceneChange(const SceneTag _nextSceneTag)
	{
		nextSceneTag = _nextSceneTag;
	}
	/**
	 * @brief       非同期でシーン内からシーンを変更する
	 * @param[in]	const SceneTag 変更先のシーンタグ
	 * @author      Suzuki N
	 * @date        24/11/20
	 */
	void SceneChangeAsync(const SceneTag _nextSceneTag)
	{
		nextSceneTagAsync = _nextSceneTag;
	}

public:

	/**
	 * @brief       デストラクタ
	 * @author      Suzuki N
	 * @date        24/11/20
	 */
	virtual ~SceneBase() {};

	/**
	 * @brief       毎F呼ばれるメソッド
	 * @author      Suzuki N
	 * @date        24/11/20
	 */
	virtual void Update() {};
};