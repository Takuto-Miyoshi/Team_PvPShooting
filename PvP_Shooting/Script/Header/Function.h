
#ifndef FUNCTION_H
#define FUNCTION_H

/// @brief フェードの状態
enum FadeMode {
	None,	// フェードなし
	In,		// フェードイン中
	Out		// フェードアウト中
};

/// @brief フェード関数の処理部分
/// @param fademode フェードの種類
/// @param fadePower フェードの強さ
/// @param fadeColor フェードの色
/// @param waitTime 待ち時間(フレーム)
/// @return true = 処理終了, false = 処理中
bool Fade( FadeMode fademode, unsigned int fadePower, int fadeColor, int waitTime );

/// @brief フェードイン
/// @param fadePower フェードの強さ
/// @param fadeColor フェードインする前の色
/// @param waitTime フェードが始まる前に待つ時間(フレーム)
/// @return true = 処理終了, false = 処理中
bool FadeIn( unsigned int fadePower, int fadeColor = GetColor( 0, 0, 0 ), int waitTime = 0 );

/// @brief フェードアウト
/// @param fadePower フェードの強さ
/// @param fadeColor フェードの色
/// @param waitTime フェードが終わった後に待つ時間(フレーム)
/// @return true = 処理終了, false = 処理中
bool FadeOut( unsigned int fadePower, int fadeColor = GetColor( 0, 0, 0 ), int waitTime = 0 );

#endif // !FUNCTION_H
