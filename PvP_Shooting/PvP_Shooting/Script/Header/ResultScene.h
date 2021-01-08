
#ifndef SC_RESULT_H
#define SC_RESULT_H

// リザルトシーン
class ResultScene : public SceneBase {
public:

	/// @brief コンストラクタ
	ResultScene();

	/// @brief デストラクタ
	~ResultScene();

	/// @brief メインループで呼び出すもの
	void Execute();

private:

	/// @brief ゲーム処理
	void Control();

	/// @brief 描画処理
	void Draw();

	/// @brief 結果を調べる
	void Result();

private:

	int winner;
	int resultBackHandle;
	static int winBannerHandle[Sprite::UI::winBannerFrame];
	static int counter;
	static int spriteNum;
	int resultJingleHandle;
};

#endif
