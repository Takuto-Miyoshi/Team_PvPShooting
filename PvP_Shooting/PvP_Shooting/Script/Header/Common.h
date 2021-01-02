
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

// オブジェクトタグ
enum class Tag{
	Player,
	Stone,
	Tree,
	Flag,
	Box,
	Car,
	Tunnel,
	Explosion
};

/// @brief ステージの情報
struct Stage{
	int number;			// ステージ番号
	LPCTSTR preview;	// ステージのスクリーンショット
};

/// @brief 画像リスト
namespace Sprite{
	const static LPCTSTR player1 = "Sprite/Test_Player1.png";
	const static LPCTSTR player2 = "Sprite/Test_Player2.png";
	const static LPCTSTR bullet = "Sprite/Test_Bullet.png";
	const static LPCTSTR stgPreview1 = "Sprite/Test_StagePreview.png";
	const static LPCTSTR stgPreview2 = "Sprite/Test_StagePreview.png";
	const static LPCTSTR stgPreview3 = "Sprite/Test_StagePreview.png";
	const static LPCTSTR titleScreen = "Sprite/Title_Screen.png";
	const static LPCTSTR characterInfoScreen = "Sprite/CharacterInfo_Screen.png";
	const static LPCTSTR resultNobunagaScreen = "Sprite/ResultNobunaga_Screen.png";
	const static LPCTSTR resultNapoleonScreen = "Sprite/ResultNapoleon_Screen.png";
	
	const static LPCTSTR hitEffect[] = {
		"Sprite/HitEffect/hit1.png",
		"Sprite/HitEffect/hit2.png",
		"Sprite/HitEffect/hit3.png",
		"Sprite/HitEffect/hitMax.png"
	};

	namespace UI{
		const static LPCTSTR titleScreen = "Sprite/UI/ScreenSprite/Title_Screen.png";

		const static LPCTSTR descriptionControl = "Sprite/UI/ScreenSprite/Description_Control.png";
		const static LPCTSTR descriptionRule1 = "Sprite/UI/ScreenSprite/Description_Rule1.png";
		const static LPCTSTR descriptionRule2 = "Sprite/UI/ScreenSprite/Description_Rule2.png";
	
		const static LPCTSTR stageSelectScreen = "Sprite/UI/ScreenSprite/StageSelectScreen.png";

		const static LPCTSTR roundInfo[] = {
			"Sprite/UI/ScreenSprite/RoundInfo1.png",
			"Sprite/UI/ScreenSprite/RoundInfo2.png",
			"Sprite/UI/ScreenSprite/RoundInfo3.png"
		};

		const static LPCTSTR stagePreview1 = "Sprite/UI/ScreenSprite/Stage1_Preview.png";
		const static LPCTSTR stagePreview2 = "Sprite/UI/ScreenSprite/Stage2_Preview.png";

		const static LPCTSTR resultDraw = "Sprite/UI/ScreenSprite/ResultDraw_Screen.png";
		const static LPCTSTR resultNobunaga = "Sprite/UI/ScreenSprite/ResultNobunaga_Screen.png";
		const static LPCTSTR resultNapoleon = "Sprite/UI/ScreenSprite/ResultNapoleon_Screen.png";

		const static LPCTSTR selectNo = "Sprite/UI/Select_No.png";
		const static LPCTSTR selectYes = "Sprite/UI/Select_Yes.png";
		const static LPCTSTR alternativeBack = "Sprite/UI/AlternativeBack.png";

		const static LPCTSTR ready = "Sprite/UI/Ready.png";
		const static LPCTSTR start = "Sprite/UI/Start.png";
		const static LPCTSTR end = "Sprite/UI/End.png";
		const static LPCTSTR pause = "Sprite/UI/Pause.png";

		const static LPCTSTR pointGauge = "Sprite/UI/PointGauge.png";

		const static LPCTSTR clockFrame = "Sprite/UI/Clock/Frame.png";
		const static LPCTSTR clockNumber[] = {
			"Sprite/UI/Clock/0.png",
			"Sprite/UI/Clock/1.png",
			"Sprite/UI/Clock/2.png",
			"Sprite/UI/Clock/3.png",
			"Sprite/UI/Clock/4.png",
			"Sprite/UI/Clock/5.png",
			"Sprite/UI/Clock/6.png",
			"Sprite/UI/Clock/7.png",
			"Sprite/UI/Clock/8.png",
			"Sprite/UI/Clock/9.png"
		};
	}

	namespace BackGround{
		const static LPCTSTR stage1 = "Sprite/BackGrounds/Stage1.png";
		const static LPCTSTR stage2 = "Sprite/BackGrounds/Stage2.png";
	}

	const static int waitFrame = 4;			// 待機モーションの枚数
	const static int walkFrame = 3;			// 移動モーションの枚数
	const static int attackFrame = 4;		// 攻撃モーションの枚数
	const static int treeFrame = 3;			// 木の画像数
	const static int flagFrame = 3;			// 旗の画像数
	const static int boxFrame = 3;			// 木箱の画像数
	const static int tunnelFrame = 2;		// トンネルの画像数
	const static int carFrame = 4;			// 車の画像数
	const static int explosionFrame = 8;	// 爆発の画像数
	const static int chargeFrame = 3;		// チャージエフェクトの枚数
	const static int hitFrame = 3;			// ヒットエフェクトの枚数


	// 信長の画像
	namespace Nobunaga{

		const static LPCTSTR waitUp[] = {
			"Sprite/Nobunaga/Wait/up1.png",
			"Sprite/Nobunaga/Wait/up1.png",
			"Sprite/Nobunaga/Wait/up2.png",
			"Sprite/Nobunaga/Wait/up2.png"
		};

		const static LPCTSTR waitDown[] = {
			"Sprite/Nobunaga/Wait/down1.png",
			"Sprite/Nobunaga/Wait/down1.png",
			"Sprite/Nobunaga/Wait/down2.png",
			"Sprite/Nobunaga/Wait/down2.png"
		};

		const static LPCTSTR waitLeft[] = {
			"Sprite/Nobunaga/Wait/left1.png",
			"Sprite/Nobunaga/Wait/left1.png",
			"Sprite/Nobunaga/Wait/left2.png",
			"Sprite/Nobunaga/Wait/left2.png"
		};

		const static LPCTSTR waitRight[] = {
			"Sprite/Nobunaga/Wait/right1.png",
			"Sprite/Nobunaga/Wait/right1.png",
			"Sprite/Nobunaga/Wait/right2.png",
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

		const static LPCTSTR chargeEffect[] = {
			"Sprite/Nobunaga/ChargeEffect/charge1.png",
			"Sprite/Nobunaga/ChargeEffect/charge2.png",
			"Sprite/Nobunaga/ChargeEffect/charge3.png"
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

	// ナポレオンの画像
	namespace Napoleon{
		const static LPCTSTR waitUp[] = {
			"Sprite/Napoleon/Wait/up1.png",
			"Sprite/Napoleon/Wait/up1.png",
			"Sprite/Napoleon/Wait/up2.png",
			"Sprite/Napoleon/Wait/up2.png"
		};

		const static LPCTSTR waitDown[] = {
			"Sprite/Napoleon/Wait/down1.png",
			"Sprite/Napoleon/Wait/down1.png",
			"Sprite/Napoleon/Wait/down2.png",
			"Sprite/Napoleon/Wait/down2.png"
		};

		const static LPCTSTR waitLeft[] = {
			"Sprite/Napoleon/Wait/left1.png",
			"Sprite/Napoleon/Wait/left1.png",
			"Sprite/Napoleon/Wait/left2.png",
			"Sprite/Napoleon/Wait/left2.png"
		};

		const static LPCTSTR waitRight[] = {
			"Sprite/Napoleon/Wait/right1.png",
			"Sprite/Napoleon/Wait/right1.png",
			"Sprite/Napoleon/Wait/right2.png",
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
			
		const static LPCTSTR chargeEffect[] = {
			"Sprite/Napoleon/ChargeEffect/charge1.png",
			"Sprite/Napoleon/ChargeEffect/charge2.png",
			"Sprite/Napoleon/ChargeEffect/charge3.png"
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

	// ギミックの画像
	namespace Gimmick{
		const static LPCTSTR tree[] = {
			"Sprite/Gimmick/tree1.png",
			"Sprite/Gimmick/tree2.png",
			"Sprite/Gimmick/tree3.png"
		};

		const static LPCTSTR flag[] = {
			"Sprite/Gimmick/flag1.png",
			"Sprite/Gimmick/flag2.png",
			"Sprite/Gimmick/flag3.png"
		};

		const static LPCTSTR stone = "Sprite/Gimmick/stone.png";

		const static LPCTSTR box[] = {
			"Sprite/Gimmick/box1.png",
			"Sprite/Gimmick/box2.png",
			"Sprite/Gimmick/box3.png"
		};

		const static LPCTSTR tunnel[] = {
			"Sprite/Gimmick/tunnelLeft.png",
			"Sprite/Gimmick/tunnelRight.png"
		};

		const static LPCTSTR car[] = {
			"Sprite/Gimmick/car1.png",
			"Sprite/Gimmick/car2.png",
			"Sprite/Gimmick/car3.png",
			"Sprite/Gimmick/car4.png"
		};

		const static LPCTSTR explosion[] = {
			"Sprite/Gimmick/explosion1.png",
			"Sprite/Gimmick/explosion2.png",
			"Sprite/Gimmick/explosion3.png",
			"Sprite/Gimmick/explosion4.png",
			"Sprite/Gimmick/explosion5.png",
			"Sprite/Gimmick/explosion6.png",
			"Sprite/Gimmick/explosion7.png",
			"Sprite/Gimmick/explosion8.png"
		};
	}
}

/// @brief 音リスト
namespace Sounds{
	namespace BGM{
		const static LPCTSTR title = "Sounds/BGM/Title.mp3";
		const static LPCTSTR battle = "Sounds/BGM/Battle.mp3";
	}

	namespace SE{
		const static LPCTSTR titleStart = "Sounds/SE/TitleStart.mp3";
		const static LPCTSTR backToTitle = "Sounds/SE/BackToTitle.mp3";
		const static LPCTSTR cursor = "Sounds/SE/Cursor.mp3";
		const static LPCTSTR enter = "Sounds/SE/Enter.mp3";

		const static LPCTSTR pause = "Sounds/SE/Pause.mp3";
		const static LPCTSTR battleStart = "Sounds/SE/BattleStart.mp3";
		const static LPCTSTR battleEnd = "Sounds/SE/BattleEnd.mp3";

		const static LPCTSTR charged = "Sounds/SE/Charged.mp3";
		const static LPCTSTR hitting = "Sounds/SE/Hitting.mp3";
		const static LPCTSTR slash = "Sounds/SE/Slash.mp3";
		const static LPCTSTR shoot = "Sounds/SE/Shoot.mp3";

		const static LPCTSTR treeDamaged = "Sounds/SE/TreeDamaged.mp3";
		const static LPCTSTR carMoved = "Sounds/SE/Car.mp3";
		const static LPCTSTR boxDamaged = "Sounds/SE/BoxDamaged.mp3";
		const static LPCTSTR explosion = "Sounds/SE/Explosion.mp3";
	}
}

/// @brief フレームレート
const int FRAME_RATE = 60;

/// @brief ステージプレビューの横幅
const int PREVIEW_WIDTH = 493;

/// @brief ステージプレビューの縦幅
const int PREVIEW_HEIGHT = 373;

/// @brief プレイヤーの当たり判定の横幅
const int PLAYER_HITBOX_WIDTH = 96;

/// @brief プレイヤーの当たり判定の縦幅
const int PLAYER_HITBOX_HEIGHT = 144;

/// @brief プレイヤーのX軸判定のずらす量
const int PLAYER_OFFSET_X = 35;

/// @brief プレイヤー画像の横幅
const int PLAYER_WIDTH = 192 - PLAYER_OFFSET_X * 2;

/// @brief プレイヤー画像の縦幅
const int PLAYER_HEIGHT = 192;

/// @brief プレイヤーのY軸判定の上からずらす量
const int PLAYER_OFFSET_UY = PLAYER_HEIGHT - PLAYER_HEIGHT / 3;

/// @brief プレイヤーのY軸判定の下からずらす量
const int PLAYER_OFFSET_DY = 0;

/// @brief 弾画像の横幅
const int BULLET_WIDTH = 64;

/// @brief 弾画像の縦幅
const int BULLET_HEIGHT = 64;

/// @brief 弾の水平方向の当たり判定の横幅
const int BULLET_HORIZONTAL_WIDTH = 96;

/// @brief 弾の水平方向の当たり判定の縦幅
const int BULLET_HORIZONTAL_HEIGHT = 160;

/// @brief 弾の垂直方向の当たり判定の横幅
const int BULLET_VERTICAL_WIDTH = 100;

/// @brief 弾の垂直方向の当たり判定の縦幅
const int BULLET_VERTICAL_HEIGHT = 56;

/// @brief 弾の当たり判定の半径
const int BULLET_RADIUS = 48;

/// @brief 木箱の横幅
const int BOX_WIDTH = 192;

/// @brief 木箱の縦幅
const int BOX_HEIGHT = 176;

/// @brief 木箱のY軸判定の上からずらす量
const int BOX_OFFSET_UY = BOX_HEIGHT / 2;

/// @brief 木箱のY軸判定の下からずらす量
const int BOX_OFFSET_DY = BOX_HEIGHT / 4;

/// @brief 車の横幅
const int CAR_WIDTH = 652;

/// @brief 車の縦幅
const int CAR_HEIGHT = 361;

/// @brief 車のY軸判定の上からずらす量
const int CAR_OFFSET_UY = CAR_HEIGHT / 5 * 2;

/// @brief 車のY軸判定の下からずらす量
const int CAR_OFFSET_DY = CAR_HEIGHT / 5;

/// @brief 爆発の横幅
const int EXPLOSION_WIDTH = 400;

/// @brief 爆発の縦幅
const int EXPLOSION_HEIGHT = 400;

/// @brief 爆発のY軸判定の上からずらす量
const int EXPLOSION_OFFSET_UY = EXPLOSION_HEIGHT / 2;

/// @brief 爆発のY軸判定の下からずらす量
const int EXPLOSION_OFFSET_DY = 0;

/// @brief 旗の横幅
const int FLAG_WIDTH = 84;

/// @brief 旗の縦幅
const int FLAG_HEIGHT = 303;

/// @brief 旗のY軸判定の上からずらす量
const int FLAG_OFFSET_UY = FLAG_HEIGHT - FLAG_HEIGHT / 8;

/// @brief 旗のY軸判定の下からずらす量
const int FLAG_OFFSET_DY = 0;

/// @brief 石の横幅
const int STONE_WIDTH = 172;

/// @brief 石の縦幅
const int STONE_HEIGHT = 113;

/// @brief 石のY軸判定の上からずらす量
const int STONE_OFFSET_UY = STONE_HEIGHT / 10 * 4;

/// @brief 石のY軸判定の下からずらす量
const int STONE_OFFSET_DY = STONE_HEIGHT / 4;

/// @brief トンネルの横幅
const int TUNNEL_WIDTH = 64;

/// @brief トンネルの縦幅
const int TUNNEL_HEIGHT = 1080;

/// @brief トンネルのY軸判定の上からずらす量
const int TUNNEL_OFFSET_UY = 0;

/// @brief トンネルのY軸判定の下からずらす量
const int TUNNEL_OFFSET_DY = 0;

/// @brief 木の横幅
const int TREE_WIDTH = 313;

/// @brief 木の縦幅
const int TREE_HEIGHT = 253;

/// @brief 木のY軸判定の上からずらす量
const int TREE_OFFSET_UY = TREE_HEIGHT / 4 * 3;

/// @brief 木のY軸判定の下からずらす量
const int TREE_OFFSET_DY = TREE_HEIGHT / 6;

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

/// @brief 描画可能なオブジェクトの数
const int OBJECT_MAX = 50;

const int COLOR_WHITE = GetColor(255, 255, 255);
const int COLOR_BLACK = GetColor(0, 0, 0);
const int COLOR_BLUE = GetColor(0, 0, 255);
const int COLOR_GREEN = GetColor(0, 255, 0);
const int COLOR_RED = GetColor(255, 0, 0);

#endif // !COMMON_N
