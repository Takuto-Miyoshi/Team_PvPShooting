
#ifndef COMMON_H
#define COMMON_H

#include <iostream>
#include <vector>

#include "DxLib.h"
#include "Function.h"

/// @brief シーンの一覧
enum class SceneList {
	Title,		// タイトル画面
	Setting,	// ルール設定画面
	OnPlay,		// ゲーム中の画面
	Result		// リザルト画面
};

/// @brief 方向
enum class Direction {
	Up,
	Right,
	Left,
	Down,
	UpperRight,
	UpperLeft,
	LowerRight,
	LowerLeft
};

/// @brief ステージの情報
struct Stage{
	int number;			// ステージ番号
	LPCTSTR preview;	// ステージのスクリーンショット
};

/// @brief 画像リスト
namespace Sprite{
	const static LPCTSTR player1	 = "Sprite/Test_Player1.png";
	const static LPCTSTR player2	 = "Sprite/Test_Player2.png";
	const static LPCTSTR bullet		 = "Sprite/Test_Bullet.png";
	const static LPCTSTR stgPreview1 = "Sprite/Test_StagePreview.png";
	const static LPCTSTR stgPreview2 = "Sprite/Test_StagePreview.png";
	const static LPCTSTR stgPreview3 = "Sprite/Test_StagePreview.png";
}

/// @brief フレームレート
const int FRAME_RATE = 60;

/// @brief ステージプレビューの横幅
const int PREVIEW_WIDTH = 300;

/// @brief ステージプレビューの縦幅
const int PREVIEW_HEIGHT = 300;

/// @brief プレイヤー画像の横幅
const int PLAYER_WIDTH = 192;

/// @brief プレイヤー画像の縦幅
const int PLAYER_HEIGHT = 192;

/// @brief 弾画像の横幅
const int BULLET_WIDTH = 64;

/// @brief 弾画像の縦幅
const int BULLET_HEIGHT = 64;

/// @brief ウィンドウの横幅
const int WINDOW_WIDTH = 1920;

/// @brief ウィンドウの縦幅
const int WINDOW_HEIGHT = 1080;

/// @brief フォントのデフォルトサイズ
const int FONT_SIZE = 42;

/// @brief ラウンド数
const int ROUND_MAX = 3;

/// @brief プレイ時間(秒)
const int PLAY_TIME = 60;

const int COLOR_WHITE = GetColor(255, 255, 255);
const int COLOR_BLACK = GetColor(0, 0, 0);
const int COLOR_BLUE = GetColor(0, 0, 255);
const int COLOR_GREEN = GetColor(0, 255, 0);
const int COLOR_RED = GetColor(255, 0, 0);

#endif // !COMMON_N
