
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

private:
	int spriteCounter;
	const int COUNTER_MAX = 3;	// 説明画面の枚数
	bool ruleShowing;

	static const LPCTSTR ruleSprite[];
};

#endif
