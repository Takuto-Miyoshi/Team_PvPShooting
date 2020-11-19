
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
};

#endif
