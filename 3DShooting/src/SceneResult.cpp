#include "SceneResult.h"

/**
* @author   Suzuki N
* @date     24/10/01
* @note		SceneResultの実装ファイル
*/


SceneResult::SceneResult(InputSystem* _Input)
{
	// 実行中のシーンタグ
	sceneTag = SceneTag::Result;

	// SceneManagerのシステム系InputSystemを受け取る
	sysInput = _Input;
	// シーン遷移用コールバック関数を登録
	// R キーでシーン遷移
	{
		sysInput->AddKeyCode("sceneChange", KEY_INPUT_R);
		callBackId = sysInput->AddCallBack("sceneChange", [&](InputAction::CallBackContext context)
			{
				if(context.state == InputState::Started)
					SceneChange(SceneTag::Title);
			});
	}

	//! これまでの最高記録
	highestScore = Score::ScoreLoad("Assets/Score/HighestScore.txt");
	// スコア最高記録更新
	if (Score::score > highestScore)
	{
		GameManager::isHighestScoreUpdated = true;
		Score::ScoreSave("Assets/Score/HighestScore.txt");
		highestScore = Score::score;
	}
}

SceneResult::~SceneResult()
{
	sysInput->DeleteCallBack("sceneChange", callBackId);
}

void SceneResult::Update()
{
	DrawFormatString(10, 50, GetColor(0,0,0), "SceneResult");
	DrawFormatString(10, 70, GetColor(0,0,0), "R でTitle");

	if(GameManager::isClear)
	{
		DrawFormatString(GameManager::ScreenSizeX / 2 + 50, 70, GetColor(0, 0, 0), 
			"Game Clear");
		DrawFormatString(GameManager::ScreenSizeX / 2 + 50, 90, GetColor(0, 0, 0), 
			"今回のスコア [ %d ]", Score::score);

		if(GameManager::isHighestScoreUpdated)
			DrawFormatString(GameManager::ScreenSizeX / 2 + 50, 120, GetColor(0, 0, 0), 
				"最高スコア更新!");
		else
			DrawFormatString(GameManager::ScreenSizeX / 2 + 50, 120, GetColor(0, 0, 0), 
				"過去のスコア [ %d ]", highestScore);

		if(GameManager::isNoDamage)
			DrawFormatString(GameManager::ScreenSizeX / 2 + 50, 170, GetColor(0, 0, 0), 
				"ノーダメージクリア！ + %d", NO_DAMAGE_SCORE);
		if(GameManager::isMortalCombat)
			DrawFormatString(GameManager::ScreenSizeX / 2 + 50, 170, GetColor(0, 0, 0), 
				"ぎりぎりでクリア！ + %d", MORTAL_COMBAT_SCORE);
	}
	else
	{
		DrawFormatString(GameManager::ScreenSizeX / 2 + 50, 70, GetColor(0, 0, 0),
			"Game Over");

		if (GameManager::isHighestScoreUpdated)
			DrawFormatString(GameManager::ScreenSizeX / 2 + 50, 120, GetColor(0, 0, 0),
				"最高スコア更新!");
		else
			DrawFormatString(GameManager::ScreenSizeX / 2 + 50, 120, GetColor(0, 0, 0),
				"過去のスコア [ %d ]", highestScore);
	}

}
