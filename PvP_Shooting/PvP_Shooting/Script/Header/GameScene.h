
#ifndef SC_ONPLAY_H
#define SC_ONPLAY_H

#include "SceneBase.h"

// ゲーム中のシーン
class GameScene : public SceneBase {
public:

	/// @brief コンストラクタ
	GameScene();

	/// @brief デストラクタ
	~GameScene();

	/// @brief メインループで呼び出すもの
	void Execute();

	/// @brief objectVaultの情報を取得する
	/// @param arrayNum 配列番号
	/// @return ObjectBase*
	static ObjectBase* GetObjectData( int arrayNum );

	/// @brief すべてのオブジェクトを解放
	static void ReleaseObject();

	/// @brief 指定した番号のオブジェクトを解放
	/// @param arrayNum 配列番号
	static void ReleaseObject( int arrayNum );

	/// @brief 当たり判定の中身
	/// @param l 攻撃された人の左
	/// @param r 攻撃された人の右
	/// @param t 攻撃された人の上
	/// @param b 攻撃された人の下
	/// @param x 弾のPosX
	/// @param y 弾のPosY
	/// @param radius 弾の半径
	/// @return 当たっていたらtrue
	static bool Collision( int l, int r, int t, int b, int x, int y, int radius );

	/// @brief 弾のグラフィックハンドルを取得する
	/// @param playerNumber プレイヤーの番号
	/// @param direction 弾の方向
	/// @param isCharged チャージ状態かどうか
	/// @return グラフィックハンドル
	static int GetBulletHandle( int playerNumber, Direction direction, bool isCharged );

	/// @brief プレイヤーのグラフィックハンドルを取得する
	/// @param playerNumber プレイヤーの番号
	/// @param direction 弾の方向
	/// @param motion どのモーションか
	/// @param spriteNumber 何番目の画像か
	/// @return グラフィックハンドル
	static int GetPlayerHandle( int playerNumber, Direction direction, Motion motion, int spriteNumber );

	/// @brief オブジェクトのグラフィックハンドルを取得する
	/// @param objectTag オブジェクトの種類
	/// @param spriteNumber 何番目の画像か
	/// @return グラフィックハンドル
	static int GetObjectHandle( Tag objectTag, int spriteNumber );

	/// @brief チャージエフェクトのグラフィックハンドルを取得する
	/// @param playerNumber プレイヤーの番号
	/// @param spriteNumber 何番目の画像か
	/// @return グラフィックハンドル
	static int GetChargeEffectHandle( int playerNumber, int spriteNumber );

	/// @brief ダメージエフェクトのグラフィックハンドルを取得する
	/// @param spriteNumber 何番目の画像か
	/// @return グラフィックハンドル
	static int GetHitEffectHandle( int spriteNumber );
private:

	/// @brief ゲーム処理
	void Control();

	/// @brief 描画処理
	void Draw();

	/// @brief プレイヤーと弾の当たり判定
	/// @param target 攻撃された人
	void HitManager( Player* target );

	/// @brief ゲーム開始からの経過時間によって処理を行う
	/// @return Start() End()を実行したならば false
	bool GameManager();

	/// @brief 開始処理 : 最初に呼び出す
	void Start();

	/// @brief 終了処理 : 最後に呼び出す
	void End();

	/// @brief オブジェクトを保存している変数を整列する
	static void SortObjectVault();

	/// @brief ギミック等の配置
	static void StageSetUp();

	/// @brief ポーズ機能に関する処理
	void Pause();

	/// @brief ポイントゲージの描画
	static void PointGauge();

	/// @brief 残り時間の描画
	static void Clock();

	/// @brief 車の処理
	void CarExec();
private:

	static int counter;
	static int startCounter;
	static int readyHandle;
	static int introHandle;
	static int finishHandle;
	static int pauseHandle;
	static int endCounter;
	static bool isOperatable;
	static ObjectBase* objectVault[OBJECT_MAX];
	static bool isPaused;
	static int pointGaugeHandle;
	static int clockFrameHandle;
	static int carSEHandle;

	static int backGroundHandle;

	int pauseSEHandle;
	int battleStartSEHandle;
	int battleEndSEHandle;

	static int USlashHandle[2];
	static int ULSlashHandle[2];
	static int URSlashHandle[2];
	static int LSlashHandle[2];
	static int RSlashHandle[2];
	static int DSlashHandle[2];
	static int DLSlashHandle[2];
	static int DRSlashHandle[2];

	static int UBulletHandle[2];
	static int ULBulletHandle[2];
	static int URBulletHandle[2];
	static int LBulletHandle[2];
	static int RBulletHandle[2];
	static int DBulletHandle[2];
	static int DLBulletHandle[2];
	static int DRBulletHandle[2];

	static int nobunagaChargeHandle[Sprite::chargeFrame];
	static int napoleonChargeHandle[Sprite::chargeFrame];

	static int UNobunagaAttackHandle[Sprite::attackFrame];
	static int LNobunagaAttackHandle[Sprite::attackFrame];
	static int RNobunagaAttackHandle[Sprite::attackFrame];
	static int DNobunagaAttackHandle[Sprite::attackFrame];

	static int UNapoleonAttackHandle[Sprite::attackFrame];
	static int LNapoleonAttackHandle[Sprite::attackFrame];
	static int RNapoleonAttackHandle[Sprite::attackFrame];
	static int DNapoleonAttackHandle[Sprite::attackFrame];

	static int UNobunagaWalkHandle[Sprite::walkFrame];
	static int LNobunagaWalkHandle[Sprite::walkFrame];
	static int RNobunagaWalkHandle[Sprite::walkFrame];
	static int DNobunagaWalkHandle[Sprite::walkFrame];

	static int UNapoleonWalkHandle[Sprite::walkFrame];
	static int LNapoleonWalkHandle[Sprite::walkFrame];
	static int RNapoleonWalkHandle[Sprite::walkFrame];
	static int DNapoleonWalkHandle[Sprite::walkFrame];

	static int UNobunagaWaitHandle[Sprite::waitFrame];
	static int LNobunagaWaitHandle[Sprite::waitFrame];
	static int RNobunagaWaitHandle[Sprite::waitFrame];
	static int DNobunagaWaitHandle[Sprite::waitFrame];

	static int UNapoleonWaitHandle[Sprite::waitFrame];
	static int LNapoleonWaitHandle[Sprite::waitFrame];
	static int RNapoleonWaitHandle[Sprite::waitFrame];
	static int DNapoleonWaitHandle[Sprite::waitFrame];

	static int treeHandle[Sprite::treeFrame];
	static int flagHandle[Sprite::flagFrame];
	static int stoneHandle;
	static int boxHandle[Sprite::boxFrame];
	static int explosionHandle[Sprite::explosionFrame];
	static int tunnelHandle[Sprite::tunnelFrame];
	static int carHandle[Sprite::carFrame];

	static int hitEffectHandle[Sprite::hitFrame];

	int summonCounter;
	bool isSummoned;

	static int clockNumber[10];
};

#endif
