
#ifndef SC_BASE_H
#define SC_BASE_H

// 各シーンの基盤
class SceneBase {
public:

	/// @brief コンストラクタ
	SceneBase();

	/// @brief デストラクタ
	~SceneBase();

	/// @brief 現在のシーンを取得する
	/// @return 現在のシーン
	static enum SceneList GetCurrentScene();
	
	/// @brief 現在のシーンを削除する :アプリの終了前に呼び出す
	static void ReleaseScene();

	/// @brief シーンがnullの場合にシーンをnewする
	static void CreateScene();
	
	/// @brief 現在読み込まれているシーンで処理を行う
	static void ExecuteScene();
	
	/// @brief シーンの変化があった場合に現在のシーンをdeleteする
	static void ReleaseCurrentScene();

private:

	virtual void Execute() = 0;
	virtual void Control() = 0;
	virtual void Draw() = 0;

protected:

	/// @brief シーン移動 + フェード
	/// @param destinationScene フェードアウト後に移動するシーン
	/// @param fadePower フェードの強さ
	/// @param fadeColor フェードの色
	/// @param waitTime 待ち時間
	void SceneFade( SceneList destinationScene, int fadePower, int fadeColor, int waitTime = 0 );

	/// @brief シーン移動 + フェード
	/// @param destinationScene フェードアウト後に移動するシーン
	/// @param inPower フェードインの強さ
	/// @param outPower フェードアウトの強さ
	/// @param inColor フェードインの色
	/// @param outColor フェードアウトの色
	/// @param inWaitTime フェードインの前に待つ時間(フレーム)
	/// @param outWaitTime フェードアウトの後に待つ時間(フレーム)
	void SceneFade( SceneList destinationScene, int inPower, int outPower, int inColor, int outColor, int inWaitTime = 0, int outWaitTime = 0 );

protected:

	/// @brief 現在のフェードの状態
	static FadeMode fadeMode;

	/// @brief 現在のシーン
	static SceneList currentScene;

private:
	static SceneBase* sc_title;
	static SceneBase* sc_onPlay;
	static SceneBase* sc_result;
	static SceneBase* pSceneBase[3];
	static int previousScene;

};

#endif // !SC_BASE_H
