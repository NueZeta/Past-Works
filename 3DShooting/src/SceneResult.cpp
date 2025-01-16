#include "SceneResult.h"

/**
* @author   Suzuki N
* @date     24/10/01
* @note		SceneResult�̎����t�@�C��
*/


SceneResult::SceneResult(InputSystem* _Input)
{
	// ���s���̃V�[���^�O
	sceneTag = SceneTag::Result;

	// SceneManager�̃V�X�e���nInputSystem���󂯎��
	sysInput = _Input;
	// �V�[���J�ڗp�R�[���o�b�N�֐���o�^
	// R �L�[�ŃV�[���J��
	{
		sysInput->AddKeyCode("sceneChange", KEY_INPUT_R);
		callBackId = sysInput->AddCallBack("sceneChange", [&](InputAction::CallBackContext context)
			{
				if(context.state == InputState::Started)
					SceneChange(SceneTag::Title);
			});
	}

	//! ����܂ł̍ō��L�^
	highestScore = Score::ScoreLoad("Assets/Score/HighestScore.txt");
	// �X�R�A�ō��L�^�X�V
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
	DrawFormatString(10, 70, GetColor(0,0,0), "R ��Title");

	if(GameManager::isClear)
	{
		DrawFormatString(GameManager::ScreenSizeX / 2 + 50, 70, GetColor(0, 0, 0), 
			"Game Clear");
		DrawFormatString(GameManager::ScreenSizeX / 2 + 50, 90, GetColor(0, 0, 0), 
			"����̃X�R�A [ %d ]", Score::score);

		if(GameManager::isHighestScoreUpdated)
			DrawFormatString(GameManager::ScreenSizeX / 2 + 50, 120, GetColor(0, 0, 0), 
				"�ō��X�R�A�X�V!");
		else
			DrawFormatString(GameManager::ScreenSizeX / 2 + 50, 120, GetColor(0, 0, 0), 
				"�ߋ��̃X�R�A [ %d ]", highestScore);

		if(GameManager::isNoDamage)
			DrawFormatString(GameManager::ScreenSizeX / 2 + 50, 170, GetColor(0, 0, 0), 
				"�m�[�_���[�W�N���A�I + %d", NO_DAMAGE_SCORE);
		if(GameManager::isMortalCombat)
			DrawFormatString(GameManager::ScreenSizeX / 2 + 50, 170, GetColor(0, 0, 0), 
				"���肬��ŃN���A�I + %d", MORTAL_COMBAT_SCORE);
	}
	else
	{
		DrawFormatString(GameManager::ScreenSizeX / 2 + 50, 70, GetColor(0, 0, 0),
			"Game Over");

		if (GameManager::isHighestScoreUpdated)
			DrawFormatString(GameManager::ScreenSizeX / 2 + 50, 120, GetColor(0, 0, 0),
				"�ō��X�R�A�X�V!");
		else
			DrawFormatString(GameManager::ScreenSizeX / 2 + 50, 120, GetColor(0, 0, 0),
				"�ߋ��̃X�R�A [ %d ]", highestScore);
	}

}
