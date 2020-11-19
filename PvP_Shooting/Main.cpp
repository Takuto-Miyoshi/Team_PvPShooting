
#include "Script/Header/Common.h"

// プログラムは WinMain から始まります
int WINAPI WinMain ( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow )
{
	SetGraphMode ( WINDOW_WIDTH, WINDOW_HEIGHT, 32, 60 );
	ChangeWindowMode ( true ); // ウィンドウモードに変更

	if ( DxLib_Init () == -1 )	// ＤＸライブラリ初期化処理
	{
		return -1; // エラーが起きたら直ちに終了
	}

	// グラフィックの描画先を裏画面にセット
	SetDrawScreen ( DX_SCREEN_BACK );

	// メインループ
	while ( true )
	{
		// 画面を初期化
		ClearDrawScreen();

		SceneBase::CreateScene();
		SceneBase::ExecuteScene();
		SceneBase::ReleaseCurrentScene();

		// -1 が返ってきたらループを抜ける
		if ( ProcessMessage () < 0 ) break;
		// もしＥＳＣキーが押されていたらループから抜ける
		if ( CheckHitKey ( KEY_INPUT_ESCAPE ) ) break;

		// 裏画面の内容を表画面にコピーする
		ScreenFlip ();
	}

	SceneBase::ReleaseScene();
	DxLib_End ();				// ＤＸライブラリ使用の終了処理

	return 0;					// ソフトの終了
}
