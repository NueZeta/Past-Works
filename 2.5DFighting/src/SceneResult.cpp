#include "SceneResult.h"

/**
* @author   Suzuki N
* @date     24/10/01
* @note		SceneResultの実装ファイル
*/


SceneResult::SceneResult(InputSystem* _input)
{
	// 実行中のシーンタグ
	sceneTag = SceneTag::Result;

	// 開始時刻を保存
	flashingInterval = GetNowCount();



	// 入力系を設定
	{
		input = _input;
		// キー押下時のコールバックを設定
		callBackId = input->AddCallBack("Change", [&](InputAction::CallBackContext c) {
			if (c.state == InputState::Started) SceneChange(SceneTag::Title);
			});
	}

	// フォントデータ読み込み
	fontHandle = CreateFontToHandle(NULL, 32, 2, DX_FONTTYPE_ANTIALIASING_8X8);
}

SceneResult::~SceneResult()
{
	input->DeleteCallBack("Change", callBackId);
}

void SceneResult::Update()
{
	//
	// 文字列を点滅表示する
	//
	if (GetNowCount() - flashingInterval < 500)
		DrawFormatStringToHandle(750, 1000, GetColor(0, 0, 0), fontHandle, "---- Press START button ----");
	else
		if (GetNowCount() - flashingInterval > 1000)
			flashingInterval = GetNowCount();
}
