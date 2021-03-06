﻿
#ifndef FUNCTION_H
#define FUNCTION_H

/// @brief フェードの状態
enum class FadeMode {
	None,	// フェードなし
	In,		// フェードイン中
	Out		// フェードアウト中
};

/// @brief キーボード、マウスの入力状態
enum class InputState {
	Invalid = -1,	// 無効
	NotPressed,		// 押されていない
	Pressed,		// 押された瞬間
	Pressing,		// 押している
	Released		// 離した瞬間
};

/// @brief マウスボタンの入力状態を調べる範囲
const int MOUSEBUTTON_UPDATE_RANGE = 5;

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

/// @brief キーの入力状態を更新する :毎フレーム呼び出す
/// @return 0以外はエラー
int UpdateKeyState();

/// @brief キーの入力状態を取得する
/// @param keyCode 入力状態を取得したいキーのキーコード
/// @return InputStateで返す
InputState GetKeyStatus( int keyCode );

/// @brief キー入力の無効/有効切り替え
/// @param keyCode 入力の無効/有効を切り替えたいキーのキーコード
void KeyInputEnabledToggle( int keyCode );

/// @brief マウスボタンの入力状態を更新する :毎フレーム呼び出す
/// @return 0以外はエラー
int UpdateMouseButtonState();

/// @brief マウスボタンの入力状態を取得する
/// @param mouseButtonCode 入力状態を取得したいマウスボタンのコード
/// @return InputStateで返す
InputState GetMouseButtonStatus( int mouseButtonCode );

/// @brief マウスボタン入力の無効/有効切り替え
/// @param mouseButtonCode 入力の無効/有効を切り替えたいマウスボタンのコード
void MouseButtonInputEnabledToggle( int mouseButtonCode );

/// @brief パッドの入力状態を更新する
/// @return 0以外はエラー
int UpdatePadState();

/// @brief パッドボタンの入力状態を取得する
/// @param padNum パッドの識別番号
/// @param padCode 入力状態を取得したいボタンのコード
/// @return InputStateで返す
InputState GetPadStatus( int padNum, int padCode );

/// @brief 対象が画面外にいるか判定する
/// @param posX 対象のX座標
/// @param posY 対象のY座標
/// @return 画面外ならtrue
bool IsOutsideWindow( int posX, int posY );

/// @brief 中央揃え用 : 文字列を表示する時にX座標に返り値を減算すると中央に表示できる
/// @param Length 文字数 : 全角文字は2文字としてカウントする
/// @return ずらす量
int CenterAdjustment( int length );

#endif // !FUNCTION_H
