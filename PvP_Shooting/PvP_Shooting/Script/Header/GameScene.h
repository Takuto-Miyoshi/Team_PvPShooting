
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
};

#endif
