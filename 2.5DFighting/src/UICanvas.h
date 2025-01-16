#pragma once
#include "GameManager.h"


/**
* @author   Suzuki N
* @date     24/11/11
* @note		UICanvasの定義ファイル
*/


/**
 * @class	UICanvas
 * @brief   HUD管理クラス
 */
class UICanvas
{
public:
	//  メンバ変数

	//! 1PのHPゲージ画像(背景)
	int hpGaugeBackScreen_1p;
	//! 1PのHPゲージ画像(MAX時)
	int maxHpGauge_1p;
	//! 1PのHPゲージ画像(100%未満)
	int hpGauge_1p;

	//! 2PのHPゲージ画像(背景)
	int hpGaugeBackScreen_2p;
	//! 2PのHPゲージ画像(MAX時)
	int maxHpGauge_2p;
	//! 2PのHPゲージ画像(100%未満)
	int hpGauge_2p;

	//! FontHandle
	int fontHandle;
	//! KO時の文字のdefaultのフォントサイズ
	int defaultFontSize = 350;
	//! フォントサイズ
	double fontSize = 1;
	//! Fightを表示した時刻
	int showFightTime = 0;
	//! KOを表示した時刻
	int showKoTime = 0;
	//! Resultを表示した時間
	int showResultTime = 0;


	// メンバ関数
public:

	// コンストラクタ
	UICanvas() : 
		hpGaugeBackScreen_1p(LoadGraph("Assets/UI/Gauge/HpGaugeBackScreen.png")), 
		maxHpGauge_1p(LoadGraph("Assets/UI/Gauge/MaxHpGauge.png")),
		hpGauge_1p(LoadGraph("Assets/UI/Gauge/hpGauge.png")),
		hpGaugeBackScreen_2p(LoadGraph("Assets/UI/Gauge/HpGaugeBackScreen.png")), 
		maxHpGauge_2p(LoadGraph("Assets/UI/Gauge/MaxHpGauge.png")),
		hpGauge_2p(LoadGraph("Assets/UI/Gauge/hpGauge.png"))
	{
		// 画像ファイルの読み込みに失敗した
		if (hpGaugeBackScreen_1p == -1 || maxHpGauge_1p == -1 || hpGauge_1p == -1 ||
			hpGaugeBackScreen_2p == -1 || maxHpGauge_2p == -1 || hpGauge_2p == -1)
			throw std::runtime_error("いずれかの画像ファイルの読み込みに失敗しました");

		// 画面サイズの取得
		GetWindowSize(&GameManager::screenWidth, &GameManager::screenHeight);

		// フォントハンドルを作成(KO)
		fontHandle = CreateFontToHandle(NULL, defaultFontSize, 30, DX_FONTTYPE_ANTIALIASING_8X8);
		fontSize = 1;
	}


	/**
	 * @brief		毎F呼ばれるメソッド
	 * @author      Suzuki N
	 * @date        24/10/29
	 */
	void ManualUpdate(int _maxHp_1p, int _hp_1p, int _maxHp_2p, int _hp_2p)
	{
#pragma region HUDの表示

#pragma region 1P

		//! 画像サイズ取得用
		int x, y;

		// HPがMAXの場合
		if (_hp_1p == _maxHp_1p)
		{
			GetGraphSize(maxHpGauge_1p, &x, &y);

			DrawExtendGraph(20, 50, GameManager::screenWidth / 2 - 20,
				20 + GameManager::screenHeight / 10, maxHpGauge_1p, TRUE);
		}
		// HPがMAXではない場合、背景も合わせて表示する
		else
		{
			//! 現在HPの割合
			float hpRate = (float)_hp_1p / (float)_maxHp_1p;

			// 先に背景用の画像を表示
			GetGraphSize(hpGaugeBackScreen_1p, &x, &y);

			DrawExtendGraph(20, 50, GameManager::screenWidth / 2 - 20,
				20 + GameManager::screenHeight / 10, hpGaugeBackScreen_1p, TRUE);

			// その上に現在体力の画像を割合分領域を指定して表示
			GetGraphSize(hpGauge_1p, &x, &y);

			DrawRectExtendGraph(20 + ((GameManager::screenWidth / 2 - 40) - (GameManager::screenWidth / 2 - 40) * hpRate),
				50, GameManager::screenWidth / 2 - 20, 20 + GameManager::screenHeight / 10,
				0, 0, (int)((float)x * hpRate), y, hpGauge_1p, TRUE);
		}

#pragma endregion

#pragma region 2P

		// HPがMAXの場合
		if (_hp_2p == _maxHp_2p)
		{
			GetGraphSize(maxHpGauge_2p, &x, &y);

			DrawExtendGraph((GameManager::screenWidth / 2 + 20), 50, (GameManager::screenWidth - 20),
				20 + GameManager::screenHeight / 10, maxHpGauge_2p, TRUE);
		}
		// HPがMAXではない場合、背景も合わせて表示する
		else
		{
			//! 現在HPの割合
			float hpRate = (float)_hp_2p / (float)_maxHp_2p;

			// 先に背景用の画像を表示
			GetGraphSize(hpGaugeBackScreen_2p, &x, &y);

			DrawExtendGraph((GameManager::screenWidth / 2 + 20), 50, (GameManager::screenWidth - 20),
				20 + GameManager::screenHeight / 10, hpGaugeBackScreen_2p, TRUE);

			// その上に現在体力の画像を割合分領域を指定して表示
			GetGraphSize(hpGauge_1p, &x, &y);

			DrawRectExtendGraph((GameManager::screenWidth / 2 + 20), 50, (GameManager::screenWidth / 2 + 20) +
				(int)((float)((GameManager::screenWidth - 20) - (GameManager::screenWidth / 2 + 20)) * hpRate),
				20 + GameManager::screenHeight / 10, 0, 0, (int)((float)x * hpRate), y, hpGauge_2p, TRUE);
		}
#pragma endregion

#pragma endregion


		if ((GameManager::param & GameParam::SetUp) == GameParam::SetUp)
			SetUp();

		if ((GameManager::param & GameParam::KO) == GameParam::KO)
			KO();

		if ((GameManager::param & GameParam::Result) == GameParam::Result)
			Result(_hp_1p, _hp_2p);
	}


	private:


		/**
		 * @brief		毎F呼ばれるメソッド
		 * @author      Suzuki N
		 * @date        24/10/29
		 */
		void SetUp()
		{
			if (fontSize > 0.5)
				fontSize -= 0.03;
			else
			{
				if (showFightTime == 0)
					showFightTime = GetNowCount();

				// KOを表示してから一定時間後に勝者を表示する
				if (GetNowCount() - showFightTime > 1000)
				{
					GameManager::param = GameParam::Game;
					fontSize = 1;
					return;
				}
			}

#pragma region Fightの表示

			DrawExtendStringToHandle(GameManager::screenWidth / 2 - 300, GameManager::screenHeight / 2 - 50, fontSize, fontSize,
				"Fight!", GetColor(255, 0, 0), fontHandle);

#pragma endregion
		}

		/**
		 * @brief		毎F呼ばれるメソッド
		 * @author      Suzuki N
		 * @date        24/10/29
		 */
		void KO()
		{
			if (fontSize > 0.5)
				fontSize -= 0.03;
			else
			{
				if (showKoTime == 0)
					showKoTime = GetNowCount();

				// KOを表示してから一定時間後に勝者を表示する
				if (GetNowCount() - showKoTime > 1500)
					GameManager::param = GameParam::Result;
			}

#pragma region KOの表示

			DrawExtendStringToHandle(GameManager::screenWidth / 2 - 100, GameManager::screenHeight / 2 - 50, fontSize, fontSize, 
				"K", GetColor(255, 0, 0), fontHandle);
			DrawExtendStringToHandle(GameManager::screenWidth / 2 + 10, GameManager::screenHeight / 2 - 50, fontSize, fontSize, 
				"O", GetColor(255, 0, 0), fontHandle);

#pragma endregion
		}


		/**
		 * @brief		毎F呼ばれるメソッド
		 * @author      Suzuki N
		 * @date        24/10/29
		 */
		void Result(int _hp_1p, int _hp_2p)
		{
			if (GetNowCount() - showKoTime < 2000)
				return;

			if (showResultTime == 0)
				showResultTime = GetNowCount();

			if (GetNowCount() - showResultTime > 3000)
			{
				GameManager::param = GameParam::Title;
				return;
			}


#pragma region 勝者の表示

			if (_hp_1p <= 0 && _hp_2p <= 0)
			{
				DrawExtendStringToHandle(GameManager::screenWidth / 2 - 100, GameManager::screenHeight / 2 - 50, 0.2, 0.2,
					"Draw", GetColor(255, 0, 0), fontHandle);
			}
			else if(_hp_1p <= 0)
			{
				DrawExtendStringToHandle(GameManager::screenWidth / 2 - 300, GameManager::screenHeight / 2 - 50, 0.2, 0.2,
					"Winner ", GetColor(255, 0, 0), fontHandle);
				DrawExtendStringToHandle(GameManager::screenWidth / 2, GameManager::screenHeight / 2 - 50, 0.2, 0.2,
					"Player2", GetColor(255, 0, 0), fontHandle);
			}
			else if(_hp_2p <= 0)
			{
				DrawExtendStringToHandle(GameManager::screenWidth / 2 - 300, GameManager::screenHeight / 2 - 50, 0.2, 0.2,
					"Winner ", GetColor(255, 0, 0), fontHandle);
				DrawExtendStringToHandle(GameManager::screenWidth / 2, GameManager::screenHeight / 2 - 50, 0.2, 0.2,
					"Player1", GetColor(255, 0, 0), fontHandle);
			}

#pragma endregion
		}
};