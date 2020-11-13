
#include "DxLib.h"

// プログラムは WinMain から始まります
int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow )
{
	// ログファイルを生成しないようにする
	SetOutApplicationLogValidFlag( false );

	SetGraphMode( 640, 480, 32, 60 );
	// ウィンドウモードに変更
	ChangeWindowMode( true );

	if ( DxLib_Init() == -1 )		// ＤＸライブラリ初期化処理
	{
		return -1;			// エラーが起きたら直ちに終了
	}

	// グラフィックの描画先を裏画面にセット
	SetDrawScreen( DX_SCREEN_BACK );

	// メインループ
	while ( true )
	{
		// 画面を初期化
		ClearDrawScreen();


		// -1 が返ってきたらループを抜ける
		if ( ProcessMessage() < 0 ) break;
		// もしＥＳＣキーが押されていたらループから抜ける
		if ( CheckHitKey( KEY_INPUT_ESCAPE ) ) break;

		// 裏画面の内容を表画面にコピーする
		ScreenFlip();
	}

	DxLib_End();				// ＤＸライブラリ使用の終了処理

	return 0;				// ソフトの終了 
}
