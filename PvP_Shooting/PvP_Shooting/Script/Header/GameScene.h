
#ifndef SC_ONPLAY_H
#define SC_ONPLAY_H

#include "Header/Common.h"
#include "Header/SceneBase.h"
#include "Header/Player.h"

// ゲーム中のシーン
class GameScene : public SceneBase {
public:

	/// @brief コンストラクタ
	GameScene();

	/// @brief デストラクタ
	~GameScene();

	/// @brief メインループで呼び出すもの
	void Execute();

private:

	/// @brief ゲーム処理
	void Control();

	/// @brief 描画処理
	void Draw();

	/// @brief 当たり判定
	/// @param target 攻撃された人
	void HitManager( Player* target );

	/// @brief 当たり判定の中身
	/// @param l 攻撃された人の左
	/// @param r 攻撃された人の右
	/// @param t 攻撃された人の上	
	/// @param b 攻撃された人の下 
	/// @param x 弾のPosX		
	/// @param y 弾のPosY
	/// @param radius 弾の半径     
	/// @return 条件に当てはまらなかったらtrue
	bool Collision( int l, int r, int t, int b, int x, int y, int radius );
};

#endif
