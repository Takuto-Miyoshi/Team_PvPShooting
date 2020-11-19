
#ifndef SC_ONPLAY_H
#define SC_ONPLAY_H

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
};

#endif
