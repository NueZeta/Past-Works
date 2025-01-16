#pragma once
#include "Define.h"
#include<iostream>
#include<fstream>

/**
* @author   Suzuki N
* @date     24/10/08
* @note		Scoreの定義ファイル
*/


/**
 * @class	Score
 * @brief   スコア管理用の静的クラス
 */class Score
{
public:
	// メンバ変数

	//! スコア
	static int score;


	// テキストに記録する
	static void ScoreSave(const std::string& _path)
	{
		// ファイルを作成
		std::ofstream file(_path.c_str());

		// スコアを記録
		file << std::to_string(score);
		file.close();
	}

	// スコアを読み込む
	static int ScoreLoad(const std::string& _path)
	{
		// ファイルを読み込む
		std::ifstream file(_path.c_str());
		if (!file)  return -1;

		//! テキストの文字列の入力先
		std::string line;

		// スコアを読み込む
		while (std::getline(file, line))
			// 文字列を数字に置き換える
			return std::stoi(line);

		return -1;
	}
};
 
 /**
 * @class	GameManager
 * @brief   スコア管理用の静的クラス
 */
 class GameManager
{
public:
	// メンバ変数

	//! スクリーンサイズ
	static int ScreenSizeX;
	static int ScreenSizeY;
	//! クリアフラグ
	static bool isClear;
	//! ゲームストップ
	static bool isStop;
	//! ノーダメージクリア
	static bool isNoDamage;
	//! ぎりぎりでクリア
	static bool isMortalCombat;
	//! スコア最高記録更新
	static bool isHighestScoreUpdated;
};