#pragma once
#include "SceneTitle.h"
#include "SceneGame.h"
#include "SceneResult.h"

/**
* @author   Suzuki N
* @date     24/10/01
* @note		SceneManagerの定義ファイル
*/


/**
 * @class	SceneManager
 * @brief   シーンの実行、遷移を行うクラス
 * @detail	シングルトンで設計されているため、インスタンスを作成できません
 */
class SceneManager
{
private:
	// メンバ変数

	//! 実行中のシーンタグ
	SceneTag crrSceneTag;
	//! 実行中のシーンのインスタンス
	SceneBase* crrScene;
	//! シーン遷移、ゲーム終了用の入力
	InputSystem* input;

public:

	//! システム終了フラグ
	bool isEnd = false;


public:
	// メンバ関数

	// インスタンスを取得する
	static SceneManager& Instance()
	{
		static SceneManager* instance = new SceneManager();
		return *instance;
	}

	// 実行中のシーンのタグを取得
	const SceneTag& GetCrrSceneTag()const { return crrSceneTag; }

	// 毎F呼ばれる関数
	void Update();

	// シーンを変更する
	void SceneChange(const SceneTag& _nextSceneTag);

private:
	// コンストラクタは明示的に削除
	SceneManager();
};

