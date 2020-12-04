
#ifndef PLAYER_H
#define PLAYER_H

#include "Common.h"
#include "Bullet.h"

/// @brief プレイヤーの数
const int PLAYER_MAX = 2;

/// @brief 画像の横幅
const int PLAYER_SPRITE_WIDTH = 192;

/// @brief 画像の縦幅
const int PLAYER_SPRITE_HEIGHT = 192;

/// @brief 射撃のクールタイム(フレーム)
const int SHOOTING_COOL_TIME = 60;

/// @brief 無敵時間(フレーム)
const int INVINCIBLE_TIME = 60;

/// @brief プレイヤー
class Player {
public:

	/// @brief コンストラクタ
	/// @param playerNum 個体識別用
	/// @param keyUp 上移動に使用するキー
	/// @param keyRight 右移動に使用するキー
	/// @param keyLeft 左移動に使用するキー
	/// @param keyDown 下移動に使用するキー
	/// @param keyShot 射撃に使用するキー
	/// @param keyBomb 爆弾に使用するキー
	/// @param spritePath 読み込む画像のパス 
	Player( int playerNum, int keyUp, int keyRight, int keyLeft, int keyDown, int keyShot, int keyBomb, LPCTSTR spritePath );

	/// @brief デストラクタ
	~Player();

	/// @brief 移動
	void Move();

	/// @brief 描画
	void Draw();

	/// @brief 射撃
	void Shoot();

	/// @brief 爆弾
	void Bomb();

	/// @brief 当たり判定
	void Hit();
	
	/// @brief 死んでたら復活
	void Invincible();

	/// @brief 個体識別番号を取得
	/// @return 番号
	int GetPlayerNumber();

	/// @brief 現在のX座標を取得する
	/// @return X座標
	int GetPosX();
	
	/// @brief 現在のY座標を取得する
	/// @return Y座標
	int GetPosY();

	/// @brief 弾の情報を取得する
	/// @param arrayNum 配列の番号
	/// @return 弾の情報
	Bullet* GetBulletData( int arrayNum );

	/// @brief 生存状態を取得する
	/// @return 生きていたらtrue
	bool GetAlive();

	/// @brief 生存状態を設定する
	/// @param state 生きている状態にするならtrue
	void SetAlive( bool state );

	/// @brief スコアを取得する
	/// @return 現在のスコア
	int GetScore();

	/// @brief スコアを設定する
	/// @param value 設定する値
	void SetScore( int value );

	/// @brief スコアを加算する
	/// @param value 加算する値
	void AddScore( int value );

	/// @brief 弾を削除する
	/// @param arrayNum 配列の番号
	void DeleteBullet( int arrayNum );

	/// @brief 死んだときの処理
	void DeathProcessing();

private:
	int playerNumber;
	bool isAlive;
	int invincibleCount;

	int posX;
	int posY;
	int speed;
	Direction dir;
	Bullet* bullets[BULLET_MAX];
	int shootingCoolTime;
	int score;

	int upMovingKey;
	int rightMovingKey;
	int leftMovingKey;
	int downMovingKey;
	int shotKey;
	int bombKey;
	LPCTSTR spriteFolderPath;
};

#endif // !PLAYER_H
