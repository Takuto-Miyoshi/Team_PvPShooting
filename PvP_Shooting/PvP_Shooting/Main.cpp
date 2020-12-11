
#include "Script/Header/Common.h"
#include "Script/Header/SceneBase.h"

// プログラムは WinMain から始まります
int WINAPI WinMain( _In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow )
{
	SetOutApplicationLogValidFlag( false );

	SetGraphMode ( WINDOW_WIDTH, WINDOW_HEIGHT, 32, 60 );
	ChangeWindowMode ( false ); // ウィンドウモードに変更

	if ( DxLib_Init () == -1 )	// ＤＸライブラリ初期化処理
	{
		return -1; // エラーが起きたら直ちに終了
	}

	// グラフィックの描画先を裏画面にセット
	SetDrawScreen ( DX_SCREEN_BACK );

	SetFontSize( FONT_SIZE );

	// メインループ
	while ( true )
	{
		// 画面を初期化
		ClearDrawScreen();

		// 入力状態を更新
		if ( UpdateKeyState() != 0 ) break;
		if ( UpdateMouseButtonState() != 0 ) break;
		if ( UpdatePadState() != 0 )break;

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
