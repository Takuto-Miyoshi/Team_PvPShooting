
#ifndef PLAYER_H
#define PLAYER_H

#include "Common.h"
#include "Bullet.h"
#include "ObjectBase.h"

/// @brief プレイヤーの数
const int PLAYER_MAX = 2;

/// @brief 射撃のクールタイム(フレーム)
const int SHOOTING_COOL_TIME = 60;

/// @brief 無敵時間(フレーム)
const int INVINCIBLE_TIME = 60;

/// @brief デフォルトの移動速度
const int PLAYER_SPEED = 7;

/// @brief プレイヤー
class Player : public ObjectBase {
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

	void Control();

	/// @brief 爆弾
	void Bomb();

	void Reset();

	/// @brief ギミックとの当たり判定
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

	/// @brief 自身の中心Y座標を取得する
	/// @return 現在の中心Y座標
	int GetCenterY()const;

	/// @brief 自身の横幅を取得する
	/// @return 画像の横幅
	int GetSpriteWidth() const{ return PLAYER_WIDTH; }

	/// @brief 自身の縦幅を取得する
	/// @return 画像の縦幅
	int GetSpriteHeight() const{ return PLAYER_HEIGHT; }

	/// @brief 当たり判定の上からのずれ幅を取得する
	/// @return 上からのずれ幅
	int GetHitOffsetUY() const{ return PLAYER_OFFSET_UY; }

	/// @brief 当たり判定の下からのずれ幅を取得する
	/// @return 上からのずれ幅
	int GetHitOffsetDY() const{ return PLAYER_OFFSET_DY; }

	/// @brief 当たり判定の横のずれ幅を取得する
	/// @return 横のずれ幅
	int GetHitOffsetX() const { return PLAYER_OFFSET_X; }

	/// @brief 現在の画像が何番目か取得する
	/// @return 画像番号
	int GetSpriteNumber() const { return spriteNumber; }

	/// @brief 画像番号を設定する
	/// @param value 設定する番号
	void SetSpriteNumber( int value ) { spriteNumber = value; }

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

	/// @brief オブジェクトの種類を取得する
	/// @return タグの名前
	Tag GetTag() const { return Tag::Player; }

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

	/// @brief 向きに応じて１歩下がる
	void BackStep();

	/// @brief プレイヤーのサウンドデータを読み込む
	void LoadSoundData();
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
	int centerY;
	int speed;
	Direction dir;
	Bullet* bullets[BULLET_MAX];
	int shootingCoolTime;
	int chargeCount;
	int score[3];

	int padNumber;
	int ultKey;
	int spriteHandle;

	int spriteNumber; // 画像の何番目を表示するか
	int chargeSpriteNumber;	// チャージ画像の何番目を表示するか
	int hitSpriteNumber;	// ヒット画像の何番目を表示するか
	int animationCounter;	// アニメーションの変更タイミング

	bool isMoved;		// 移動中か
	bool isAttacked;	// 攻撃中か
	bool previousAlive;	// 前のフレームは生きていたか

	int chargeSEHandle;
	int hittingSEHandle;
	int attackSEHandle;

	int treeSEHandle;
	int boxSEHandle;
};

#endif // !PLAYER_H
