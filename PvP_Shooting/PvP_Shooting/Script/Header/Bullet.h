
#ifndef BULLET_H
#define BULLET_H

#include "Header/Common.h"

/// @brief 弾の最大数
const int BULLET_MAX = 10;

/// @brief 画像の横幅
const int BULLET_SPRITE_WIDTH = 32;

/// @brief 画像の縦幅
const int BULLET_SPRITE_HEIGHT = 32;

/// @brief チャージショットを撃つために必要な時間(フレーム)
const int CHARGE_COUNT = 120;

/// @brief デフォルトの弾速度
const int BULLET_SPEED = 13;

/// @brief チャージショットの速度
const int BULLET_CHARGE_SPEED = 26;

class Bullet{

public:
	/// @brief コンストラクタ
	/// @param dir 進む方向
	/// @param spritePath 読み込む画像のパス
	Bullet( int InitPosX, int InitPosY, Direction direction, LPCTSTR spritePath, bool isCharged );
	~Bullet();

	/// @brief 移動
	void Move();

	/// @brief 描画
	void Draw();

	/// @brief X座標を取得する
	/// @return X座標
	int GetPosX();

	/// @brief Y座標を取得する
	/// @return Y座標
	int GetPosY();

private:
	int posX;
	int posY;
	int speed;
	Direction dir;
	bool changeChargeShot;

	LPCTSTR spriteFolderPath;
};

#endif // !BULLET_H
