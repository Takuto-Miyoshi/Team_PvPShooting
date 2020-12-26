
#ifndef SC_SETTING_H
#define SC_SETTING_H

struct AlternativeData{
	int x1 = 0;
	int x2 = 0;
	int y1 = 0;
	int y2 = 0;
	int handle1 = 0;
	int handle2 = 0;
	int currentSelection = 0;
};

// リザルトシーン
class SettingScene : public SceneBase {
public:

	/// @brief コンストラクタ
	SettingScene();

	/// @brief デストラクタ
	~SettingScene();

	/// @brief メインループで呼び出すもの
	void Execute();

	/// @brief ステージ設定処理
	void SetStage();

private:

	/// @brief ゲーム処理
	void Control();

	/// @brief 描画処理
	void Draw();

	/// @brief ステージ確認
	void Confirm();

	/// @brief データの入れ替え
	/// @param data Alternative構造体
	void ReplaceData( AlternativeData* data );

	/// @brief 背景の描画
	void DrawBackground();

private:
	int settingStep;

	SceneList destinationScene;

	AlternativeData preview;
	AlternativeData confirm;
};

#endif
