
#ifndef SC_SETTING_H
#define SC_SETTING_H

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

private:
	int settingStep;
};

#endif
