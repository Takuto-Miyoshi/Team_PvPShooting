
#ifndef SC_TITLE_H
#define SC_TITLE_H

/// @brief ルールの画像
const LPCSTR RuleSprite[] {
	"Sprite/Test_Player.png",	// テスト用プレイヤー
	"Sprite/Test_Bullet.png"	// テスト用弾
};

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

	/// @brief ルールの表示
	void ShowRule();

private:

	int spriteCounter;
	const int COUNTER_MAX = 1;
	bool ruleShowing;
};

#endif
