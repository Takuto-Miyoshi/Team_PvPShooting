
#include "Header/Common.h"

/// @brief キーが何フレーム入力されているか保存する
InputState keyState[256];

/// @brief マウスボタンが何フレーム入力されているか保存する
InputState mouseState[MOUSEBUTTON_UPDATE_RANGE] = {};

/// @brief ボタンが何フレーム入力されているか保存する
InputState padState[2][9];

bool Fade( FadeMode fademode, unsigned int fadePower, int fadeColor, int waitTime ) {

	const int ALPHA_MAX = 255;
	const int ALPHA_MIN = 0;
	const int ALPHA_INVALID = -1;

	static int alpha = ALPHA_INVALID;
	static int waitTimeCount = 0;

	if ( alpha == ALPHA_INVALID ) {
		alpha = ( fademode == FadeMode::In ) ? ALPHA_MAX : ALPHA_MIN;
	}

	if ( fademode == FadeMode::In ) {
		if ( alpha == ALPHA_MAX ) {
			DrawBox ( 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, fadeColor, true );
			waitTimeCount++;
			if ( waitTime > waitTimeCount ) {
				return false;
			}
		}
	}

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
	DrawBox(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, fadeColor, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	alpha = ( fademode == FadeMode::In ) ? alpha - fadePower : alpha + fadePower;

	if ( alpha < ALPHA_MIN || alpha > ALPHA_MAX ) {
		if ( fademode == FadeMode::Out ) {
			waitTimeCount++;
			if ( waitTime > waitTimeCount ) {
				return false;
			}
		}
		alpha = ALPHA_INVALID;
		waitTimeCount = 0;
		return true;
	}

	return false;
}

bool FadeIn(unsigned int fadePower, int fadeColor, int waitTime ) {
	return Fade ( FadeMode::In, fadePower, fadeColor, waitTime ) ? true : false;
}

bool FadeOut(unsigned int fadePower, int fadeColor, int waitTime ) {
	return Fade ( FadeMode::Out, fadePower, fadeColor, waitTime ) ? true : false;
}

/// @brief キー/マウスの入力状態を更新する
/// @param isPressed 1 = 押している, 1以外 = 押していない
/// @param inputState キー/マウスの入力状態
/// @return 入力状態の判定結果 InputStateで返す
InputState UpdateInputState( int isPressed, InputState inputState ){
	if ( inputState == InputState::Invalid )return InputState::Invalid;

	if ( isPressed == 1 ){
		if ( inputState == InputState::NotPressed ){
			return InputState::Pressed;
		}
		else if ( inputState == InputState::Pressed || inputState == InputState::Pressing ){
			return InputState::Pressing;
		}
	}
	else{
		if ( inputState == InputState::Pressed || inputState == InputState::Pressing ){
			return InputState::Released;
		}
	}

	return InputState::NotPressed;
}

int UpdateKeyState() {
	char currentKeyState[256];

	if ( GetHitKeyStateAll( currentKeyState ) != 0 ) {
		return -1;
	}

	for ( int i = 0; i < 256; i++ ) {
		keyState[i] = UpdateInputState( currentKeyState[i], keyState[i] );
	}

	return 0;
}

InputState GetKeyStatus( int keyCode ){
	return keyState[keyCode];
}

void KeyInputEnabledToggle( int keyCode ) {
	keyState[keyCode] = ( keyState[keyCode] == InputState::Invalid ) ? InputState::NotPressed : InputState::Invalid;
}

int UpdateMouseButtonState() {
	char currentMouseState[MOUSEBUTTON_UPDATE_RANGE];

	for ( int i = 0; i < MOUSEBUTTON_UPDATE_RANGE; i++ ) {
		currentMouseState[i] = ( GetMouseInput() & i );
	}

	for ( int i = 0; i < MOUSEBUTTON_UPDATE_RANGE; i++ ) {
		mouseState[i] = UpdateInputState( currentMouseState[i], mouseState[i] );
	}

	return 0;
}

InputState GetMouseButtonStatus( int mouseButtonCode ) {
	return mouseState[mouseButtonCode];
}

void MouseButtonInputEnabledToggle( int mouseButtonCode ) {
	mouseState[mouseButtonCode] = ( mouseState[mouseButtonCode] == InputState::Invalid ) ? InputState::NotPressed : InputState::Invalid;
}

int UpdatePadState(){
	char currentPadState[2][9];

	for( int p = 0; p < 2; p++ ){
	int buttonTemp = 1;
		for( int b = 0; b < 8; b++ ){
			currentPadState[p][b] = ( ( GetJoypadInputState( p + 1 ) & buttonTemp ) == 0 ) ? 0 : 1;

			if( buttonTemp >= 16 ) buttonTemp += 16;
			else buttonTemp *= 2;
		}
		currentPadState[p][8] = ( ( GetJoypadInputState( p + 1 ) & PAD_INPUT_10 ) == 0 ) ? 0 : 1;
	}

	for( int p = 0; p < 2; p++ ){
		for( int i = 0; i < 8; i++ ){
			padState[p][i] = UpdateInputState( currentPadState[p][i], padState[p][i] );
		}
		padState[p][8] = UpdateInputState( currentPadState[p][8], padState[p][8] );
	}

	return 0;
}

InputState GetPadStatus( int padNum, int padCode ){

	int convertedPadCode = -1;

	switch( padCode ){
	case PAD_INPUT_DOWN:	convertedPadCode = 0; break;
	case PAD_INPUT_LEFT:	convertedPadCode = 1; break;
	case PAD_INPUT_RIGHT:	convertedPadCode = 2; break;
	case PAD_INPUT_UP:		convertedPadCode = 3; break;
	case PAD_INPUT_1:		convertedPadCode = 4; break;
	case PAD_INPUT_2:		convertedPadCode = 5; break;
	case PAD_INPUT_3:		convertedPadCode = 6; break;
	case PAD_INPUT_4:		convertedPadCode = 7; break;
	case PAD_INPUT_10:		convertedPadCode = 8; break;
	default:break;
	}

	return padState[padNum - 1][convertedPadCode];
}

bool IsOutsideWindow( int posX, int posY ){

	if( posX < 0 || posX > WINDOW_WIDTH ||
		posY < 30 || posY > WINDOW_HEIGHT ){
		return true;
	}

	return false;
}

int CenterAdjustment( int length ){
	return GetFontSize() * length / 4;
}
