#include "SceneResult.h"

/**
* @author   Suzuki N
* @date     24/11/20
* @note		SceneResult�̎����t�@�C��
*/


SceneResult::SceneResult()
{
	// ���s���̃V�[���^�O
	sceneTag = SceneTag::Result;
}

SceneResult::~SceneResult()
{
}

void SceneResult::Update()
{
	DrawFormatString(100, 200, GetColor(255, 255, 255), "SceneResult");
}
