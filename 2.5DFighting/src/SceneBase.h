#pragma once
#include "GameManager.h"

/**
* @author   Suzuki N
* @date     24/10/01
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
	//! SceneManagerが持つInputSystem
	InputSystem* input;
	//! シーン遷移のコールバック関数のID
	int callBackId;


	// メンバ関数

	// コンストラクタ
	SceneBase() : nextSceneTag(SceneTag::NotFound)
	{}

	// シーン内部でシーンを遷移する
	void SceneChange(const SceneTag _nextSceneTag)
	{
		nextSceneTag = _nextSceneTag;
	}

public:
	// デストラクタ
	// 仮想関数
	virtual ~SceneBase() {};

	// 毎F呼ばれるメソッド
	// 仮想関数
	virtual void Update() {};
};