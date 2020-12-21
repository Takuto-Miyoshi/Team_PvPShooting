
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

struct Animation{
	LPCTSTR* waitUp;
	LPCTSTR* waitDown;
	LPCTSTR waitLeft;
	LPCTSTR waitRight;
};

/// @brief 画像リスト
namespace Sprite{
	const static LPCTSTR player1	 = "Sprite/Test_Player1.png";
	const static LPCTSTR player2	 = "Sprite/Test_Player2.png";
	const static LPCTSTR bullet		 = "Sprite/Test_Bullet.png";
	const static LPCTSTR stgPreview1 = "Sprite/Test_StagePreview.png";
	const static LPCTSTR stgPreview2 = "Sprite/Test_StagePreview.png";
	const static LPCTSTR stgPreview3 = "Sprite/Test_StagePreview.png";
	const static LPCTSTR titleScreen = "Sprite/Title_Screen.png";
	const static LPCTSTR characterInfoScreen = "Sprite/CharacterInfo_Screen.png";
	const static LPCTSTR resultNobunagaScreen = "Sprite/ResultNobunaga_Screen.png";
	const static LPCTSTR resultNapoleonScreen = "Sprite/ResultNapoleon_Screen.png";

	namespace Nobunaga{
		const static LPCTSTR waitUp[] = {
			"Sprite/Nobunaga/Wait/up1.png",
			"Sprite/Nobunaga/Wait/up2.png"
		};

		const static LPCTSTR waitDown[] = {
			"Sprite/Nobunaga/Wait/down1.png",
			"Sprite/Nobunaga/Wait/down2.png"
		};

		const static LPCTSTR waitLeft[] = {
			"Sprite/Nobunaga/Wait/left1.png",
			"Sprite/Nobunaga/Wait/left2.png"
		};

		const static LPCTSTR waitRight[] = {
			"Sprite/Nobunaga/Wait/right1.png",
			"Sprite/Nobunaga/Wait/right2.png"
		};

		const static LPCTSTR walkUp[] = {
			"Sprite/Nobunaga/Walk/up1.png",
			"Sprite/Nobunaga/Walk/up2.png",
			"Sprite/Nobunaga/Walk/up3.png"
		};

		const static LPCTSTR walkDown[] = {
			"Sprite/Nobunaga/Walk/down1.png",
			"Sprite/Nobunaga/Walk/down2.png",
			"Sprite/Nobunaga/Walk/down3.png"
		};

		const static LPCTSTR walkLeft[] = {
			"Sprite/Nobunaga/Walk/left1.png",
			"Sprite/Nobunaga/Walk/left2.png",
			"Sprite/Nobunaga/Walk/left3.png"
		};

		const static LPCTSTR walkRight[] = {
			"Sprite/Nobunaga/Walk/right1.png",
			"Sprite/Nobunaga/Walk/right2.png",
			"Sprite/Nobunaga/Walk/right3.png"
		};

		const static LPCTSTR attackUp[] = {
			"Sprite/Nobunaga/Attack/up1.png",
			"Sprite/Nobunaga/Attack/up2.png",
			"Sprite/Nobunaga/Attack/up3.png",
			"Sprite/Nobunaga/Attack/up4.png"
		};

		const static LPCTSTR attackDown[] = {
			"Sprite/Nobunaga/Attack/down1.png",
			"Sprite/Nobunaga/Attack/down2.png",
			"Sprite/Nobunaga/Attack/down3.png",
			"Sprite/Nobunaga/Attack/down4.png"
		};

		const static LPCTSTR attackLeft[] = {
			"Sprite/Nobunaga/Attack/left1.png",
			"Sprite/Nobunaga/Attack/left2.png",
			"Sprite/Nobunaga/Attack/left3.png",
			"Sprite/Nobunaga/Attack/left4.png"
		};

		const static LPCTSTR attackRight[] = {
			"Sprite/Nobunaga/Attack/right1.png",
			"Sprite/Nobunaga/Attack/right2.png",
			"Sprite/Nobunaga/Attack/right3.png",
			"Sprite/Nobunaga/Attack/right4.png"
		};

		const static LPCTSTR bulletUp[] = {
			"Sprite/Nobunaga/NormalBullet/Up.png",
			"Sprite/Nobunaga/ChargeBullet/Up.png"
		};

		const static LPCTSTR bulletDown[] = { 
			"Sprite/Nobunaga/NormalBullet/Down.png",
			"Sprite/Nobunaga/ChargeBullet/Down.png"
		};

		const static LPCTSTR bulletLeft[] = {
			"Sprite/Nobunaga/NormalBullet/Left.png",
			"Sprite/Nobunaga/ChargeBullet/Left.png"
		};

		const static LPCTSTR bulletRight[] = {
			"Sprite/Nobunaga/NormalBullet/Right.png",
			"Sprite/Nobunaga/ChargeBullet/Right.png"
		};

		const static LPCTSTR bulletUpperLeft[] = {
			"Sprite/Nobunaga/NormalBullet/Upper_Left.png",
			"Sprite/Nobunaga/ChargeBullet/Upper_Left.png"
		};
		
		const static LPCTSTR bulletUpperRight[] = {
			"Sprite/Nobunaga/NormalBullet/Upper_Right.png",
			"Sprite/Nobunaga/ChargeBullet/Upper_Right.png"
		};

		const static LPCTSTR bulletLowerLeft[] = {
			"Sprite/Nobunaga/NormalBullet/Lower_Left.png",
			"Sprite/Nobunaga/ChargeBullet/Lower_Left.png"
		};

		const static LPCTSTR bulletLowerRight[] = {
			"Sprite/Nobunaga/NormalBullet/Lower_Right.png",
			"Sprite/Nobunaga/ChargeBullet/Lower_Right.png"
		};
	}

	namespace Napoleon{
		const static LPCTSTR waitUp[] = {
			"Sprite/Napoleon/Wait/up1.png",
			"Sprite/Napoleon/Wait/up2.png"
		};

		const static LPCTSTR waitDown[] = {
			"Sprite/Napoleon/Wait/down1.png",
			"Sprite/Napoleon/Wait/down2.png"
		};

		const static LPCTSTR waitLeft[] = {
			"Sprite/Napoleon/Wait/left1.png",
			"Sprite/Napoleon/Wait/left2.png"
		};

		const static LPCTSTR waitRight[] = {
			"Sprite/Napoleon/Wait/right1.png",
			"Sprite/Napoleon/Wait/right2.png"
		};

		const static LPCTSTR walkUp[] = {
			"Sprite/Napoleon/Walk/up1.png",
			"Sprite/Napoleon/Walk/up2.png",
			"Sprite/Napoleon/Walk/up3.png"
		};

		const static LPCTSTR walkDown[] = {
			"Sprite/Napoleon/Walk/down1.png",
			"Sprite/Napoleon/Walk/down2.png",
			"Sprite/Napoleon/Walk/down3.png"
		};

		const static LPCTSTR walkLeft[] = {
			"Sprite/Napoleon/Walk/left1.png",
			"Sprite/Napoleon/Walk/left2.png",
			"Sprite/Napoleon/Walk/left3.png"
		};

		const static LPCTSTR walkRight[] = {
			"Sprite/Napoleon/Walk/right1.png",
			"Sprite/Napoleon/Walk/right2.png",
			"Sprite/Napoleon/Walk/right3.png"
		};

		const static LPCTSTR attackUp[] = {
			"Sprite/Napoleon/Attack/up1.png",
			"Sprite/Napoleon/Attack/up1.png",
			"Sprite/Napoleon/Attack/up2.png",
			"Sprite/Napoleon/Attack/up2.png"
		};

		const static LPCTSTR attackDown[] = {
			"Sprite/Napoleon/Attack/down1.png",
			"Sprite/Napoleon/Attack/down1.png",
			"Sprite/Napoleon/Attack/down2.png",
			"Sprite/Napoleon/Attack/down2.png"
		};

		const static LPCTSTR attackLeft[] = {
			"Sprite/Napoleon/Attack/left1.png",
			"Sprite/Napoleon/Attack/left1.png",
			"Sprite/Napoleon/Attack/left2.png",
			"Sprite/Napoleon/Attack/left2.png"
		};

		const static LPCTSTR attackRight[] = {
			"Sprite/Napoleon/Attack/right1.png",
			"Sprite/Napoleon/Attack/right1.png",
			"Sprite/Napoleon/Attack/right2.png",
			"Sprite/Napoleon/Attack/right2.png"
		};

		const static LPCTSTR bulletUp[] = {
			"Sprite/Napoleon/NormalBullet/Up.png",
			"Sprite/Napoleon/ChargeBullet/Up.png"
		};

		const static LPCTSTR bulletDown[] = {
			"Sprite/Napoleon/NormalBullet/Down.png",
			"Sprite/Napoleon/ChargeBullet/Down.png"
		};

		const static LPCTSTR bulletLeft[] = {
			"Sprite/Napoleon/NormalBullet/Left.png",
			"Sprite/Napoleon/ChargeBullet/Left.png"
		};

		const static LPCTSTR bulletRight[] = {
			"Sprite/Napoleon/NormalBullet/Right.png",
			"Sprite/Napoleon/ChargeBullet/Right.png"
		};

		const static LPCTSTR bulletUpperLeft[] = {
			"Sprite/Napoleon/NormalBullet/Upper_Left.png",
			"Sprite/Napoleon/ChargeBullet/Upper_Left.png"
		};

		const static LPCTSTR bulletUpperRight[] = {
			"Sprite/Napoleon/NormalBullet/Upper_Right.png",
			"Sprite/Napoleon/ChargeBullet/Upper_Right.png"
		};

		const static LPCTSTR bulletLowerLeft[] = {
			"Sprite/Napoleon/NormalBullet/Lower_Left.png",
			"Sprite/Napoleon/ChargeBullet/Lower_Left.png"
		};

		const static LPCTSTR bulletLowerRight[] = {
			"Sprite/Napoleon/NormalBullet/Lower_Right.png",
			"Sprite/Napoleon/ChargeBullet/Lower_Right.png"
		};
	}
}

/// @brief フレームレート
const int FRAME_RATE = 60;

/// @brief ステージプレビューの横幅
const int PREVIEW_WIDTH = 300;

/// @brief ステージプレビューの縦幅
const int PREVIEW_HEIGHT = 300;

/// @brief プレイヤーの当たり判定の横幅
const int PLAYER_HITBOX_WIDTH = 100;

/// @brief プレイヤーの当たり判定の縦幅
const int PLAYER_HITBOX_HEIGHT = 144;

/// @brief プレイヤー画像の横幅
const int PLAYER_WIDTH = 192;

/// @brief プレイヤー画像の縦幅
const int PLAYER_HEIGHT = 192;

/// @brief 弾画像の横幅
const int BULLET_WIDTH = 64;

/// @brief 弾画像の縦幅
const int BULLET_HEIGHT = 64;

/// @brief 弾の当たり判定の半径
const int BULLET_RADIUS = 48;

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

/// @brief 待機アニメーションのコマ数
const int WAIT_FRAME = 2;

/// @brief 移動アニメーションのコマ数
const int WALK_FRAME = 3;

/// @brief 攻撃アニメーションのコマ数
const int ATTACK_FRAME = 4;

/// @brief アニメーションの更新頻度
const int TIME_CHANGE_ANIMATION = 12;

const int COLOR_WHITE = GetColor(255, 255, 255);
const int COLOR_BLACK = GetColor(0, 0, 0);
const int COLOR_BLUE = GetColor(0, 0, 255);
const int COLOR_GREEN = GetColor(0, 255, 0);
const int COLOR_RED = GetColor(255, 0, 0);

#endif // !COMMON_N
