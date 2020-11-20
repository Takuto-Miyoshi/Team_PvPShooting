
#ifndef SC_TITLE_H
#define SC_TITLE_H

// タイトルシーン
class TitleScene : public SceneBase {
public:

	/// @brief コンストラクタ
	TitleScene();

	/// @brief デストラクタ
	~TitleScene();

	/// @brief メインループで呼び出すもの
	void Execute();

private:

	/// @brief ゲーム処理
	void Control();

	/// @brief 描画処理
	void Draw();
};

#endif
