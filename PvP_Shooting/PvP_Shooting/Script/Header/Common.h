
#ifndef COMMON_H
#define COMMON_H

#include <iostream>
#include <vector>

#include "DxLib.h"
#include "Function.h"

/// @brief シーンの一覧
enum SceneList {
	Title,	// タイトル画面
	OnPlay,	// ゲーム中の画面
	Result	// リザルト画面
};

/// @brief 方向
enum Direction {
	Up,
	Right,
	Left,
	Down,
	UpperRight,
	UpperLeft,
	LowerRight,
	LowerLeft
};

/// @brief 画像ファイル
const LPCSTR spriteList[] = {
	"Sprite/Test_Player.png",	// テスト用プレイヤー 
	"Sprite/Test_Bullet.png"	// テスト用弾	
};

/// @brief ウィンドウの横幅
const int WINDOW_WIDTH = 1920;

/// @brief ウィンドウの縦幅
const int WINDOW_HEIGHT = 1080;

const int COLOR_WHITE = GetColor(255, 255, 255);
const int COLOR_BLACK = GetColor(0, 0, 0);
const int COLOR_BLUE = GetColor(0, 0, 255);
const int COLOR_GREEN = GetColor(0, 255, 0);
const int COLOR_RED = GetColor(255, 0, 0);

#endif // !COMMON_N
