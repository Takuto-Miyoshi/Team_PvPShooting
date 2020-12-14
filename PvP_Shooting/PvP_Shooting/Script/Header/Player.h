
#ifndef PLAYER_H
#define PLAYER_H

#include "Common.h"
#include "Bullet.h"

/// @brief プレイヤーの数
const int PLAYER_MAX = 2;

/// @brief 射撃のクールタイム(フレーム)
const int SHOOTING_COOL_TIME = 60;

/// @brief 無敵時間(フレーム)
const int INVINCIBLE_TIME = 60;

/// @brief デフォルトの移動速度
const int PLAYER_SPEED = 7;

/// @brief プレイヤー
class Player {
public:

	/// @brief コンストラクタ
	/// @param padNum 使用するコントローラー : キーボードの場合は0
	/// @param playerNum 個体識別用
	/// @param keyUp 上移動に使用するキー
	/// @param keyRight 右移動に使用するキー
	/// @param keyLeft 左移動に使用するキー
	/// @param keyDown 下移動に使用するキー
	/// @param keyShot 射撃に使用するキー
	/// @param keyBomb 爆弾に使用するキー
	/// @param keyUlt 必殺技に使用するキー
	Player( int padNum, int playerNum, int keyUp, int keyRight, int keyLeft, int keyDown, int keyShot, int keyBomb, int keyUlt );

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
	int GetPosX()const;

	/// @brief 現在のY座標を取得する
	/// @return Y座標
	int GetPosY()const;

	/// @brief X座標を設定する
	/// @param x X座標
	void SetPosX( int x );

	/// @brief Y座標を設定する
	/// @param y Y座標
	void SetPosY( int y );

	/// @brief 弾の情報を取得する
	/// @param arrayNum 配列の番号
	/// @return 弾の情報
	Bullet* GetBulletData( int arrayNum )const;

	/// @brief 生存状態を取得する
	/// @return 生きていたらtrue
	bool GetAlive()const;

	/// @brief 生存状態を設定する
	/// @param state 生きている状態にするならtrue
	void SetAlive( bool state );

	/// @brief スコアを取得する : 引数-1で合計スコアを取得
	/// @param round 何ラウンド目のスコアを取得するか
	/// @return 現在のスコア
	int GetScore( int round )const;

	/// @brief スコアを全て０にする
	void ResetScore();

	/// @brief スコアを加算する
	/// @param value 加算する値
	/// @param round 現在のラウンド
	void AddScore( int value, int round );

	/// @brief 弾を削除する
	/// @param arrayNum 配列の番号
	void DeleteBullet( int arrayNum );

	/// @brief 死んだときの処理
	void DeathProcessing();

public:
	int upMovingKey;
	int rightMovingKey;
	int leftMovingKey;
	int downMovingKey;
	int shotKey;
	int bombKey;

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
	int chargeCount;
	int score[3];

	int padNumber;
	int ultKey;
	LPCTSTR spritePath;	// 描画する画像のパス

	int spriteNumber; // 画像の何番目を表示するか
	int animationCounter;	// アニメーションの変更タイミング

	bool isMoved;		// 移動中か
	bool isAttacked;	// 攻撃中か
};

#endif // !PLAYER_H
