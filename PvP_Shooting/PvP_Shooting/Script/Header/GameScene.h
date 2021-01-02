
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
private:

	static int counter;
	static int startCounter;
	static int introHandle;
	static int endCounter;
	static bool isOperatable;
	static ObjectBase* objectVault[OBJECT_MAX];
	static bool isPaused;

	static int backGroundHandle;

	int pauseSEHandle;
	int battleStartSEHandle;
	int battleEndSEHandle;
};

#endif
