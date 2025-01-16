#include "SceneTitle.h"

/**
* @author   Suzuki N
* @date     24/10/01
* @note		SceneTitleの実装ファイル
*/


SceneTitle::SceneTitle(InputSystem* _input)
{
	// 実行中のシーンタグ
	sceneTag = SceneTag::Title;

	// 開始時刻を保存
	flashingInterval = GetNowCount();


	// 入力系を設定
	{
		input = _input;
		// キー押下時のコールバックを設定
		callBackId = input->AddCallBack("Change", [&](InputAction::CallBackContext c) {
			if (c.state == InputState::Started) SceneChange(SceneTag::Game);
			});
	}


	// フォントデータ読み込み
	logoFontHandle = CreateFontToHandle(NULL, 32, 2, DX_FONTTYPE_ANTIALIASING_8X8);
	SetBackgroundColor(255, 255, 255);
}

SceneTitle::~SceneTitle()
{
	input->DeleteCallBack("Change", callBackId);
}

void SceneTitle::Update()
{
	DrawFormatStringToHandle(10, 50, GetColor(0, 0, 0), logoFontHandle, "Title");

	DrawFormatStringToHandle(880, 400, GetColor(0, 0, 0), logoFontHandle, "操作方法");
	DrawFormatStringToHandle(700, 500, GetColor(0, 0, 0), logoFontHandle, "X    :  弱攻撃       Y    : 強攻撃");
	DrawFormatStringToHandle(700, 550, GetColor(0, 0, 0), logoFontHandle, "↓→ :  波動拳       →↓ : 昇竜拳");
	DrawFormatStringToHandle(700, 700, GetColor(0, 0, 0), logoFontHandle, "攻撃がHitした時に必殺技でキャンセル可能");

	//
	// 文字列を点滅表示する
	//
	if(GetNowCount() - flashingInterval < 500)
		DrawFormatStringToHandle(750, 1000, GetColor(0, 0, 0), logoFontHandle, "---- Press START button ----");
	else
		if (GetNowCount() - flashingInterval > 1000)
			flashingInterval = GetNowCount();
}
