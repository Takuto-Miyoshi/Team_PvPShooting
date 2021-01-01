
#include "Header/Common.h"
#include "Header/SceneBase.h"
#include "Header/TitleScene.h"

#define USE_CONTROLLER

/// @brief ルールの画像
const LPCTSTR TitleScene::ruleSprite[] {
	Sprite::UI::descriptionControl,
	Sprite::UI::descriptionRule1,
	Sprite::UI::descriptionRule2
};


TitleScene::TitleScene() {
	ruleShowing = false;
	spriteCounter = -1;

	SceneBase::startTitleSEHandle = LoadSoundMem( Sounds::SE::titleStart );
	SceneBase::cursorSEHandle = LoadSoundMem( Sounds::SE::cursor );
	SceneBase::enterSEHandle = LoadSoundMem( Sounds::SE::enter );

	SceneBase::BGMHandle = LoadSoundMem( Sounds::BGM::title );

	SceneBase::Reset();
}

TitleScene::~TitleScene() {

}

void TitleScene::Execute() {
	Control();
	Draw();
}

void TitleScene::Control() {

	if( fadeMode != FadeMode::None ) return;

#ifdef USE_CONTROLLER
	if( GetPadStatus( player1->GetPlayerNumber(), PAD_INPUT_8 ) == InputState::Pressed ){
#else
	if( GetKeyStatus( KEY_INPUT_RETURN ) == InputState::Pressed ){
#endif
		fadeMode = FadeMode::Out;
		PlaySoundMem( SceneBase::startTitleSEHandle, DX_PLAYTYPE_BACK );
	}

#ifdef USE_CONTROLLER
	if( GetPadStatus( player1->GetPlayerNumber(), player1->shotKey ) == InputState::Pressed ){
#else
	if( GetKeyStatus( player1->shotKey ) == InputState::Pressed ){
#endif
		if( spriteCounter < COUNTER_MAX )spriteCounter++;

		if( ruleShowing == false ){
			PlaySoundMem( SceneBase::enterSEHandle, DX_PLAYTYPE_BACK );
		}
		else{
			PlaySoundMem( SceneBase::cursorSEHandle, DX_PLAYTYPE_BACK );
		}
	}

#ifdef USE_CONTROLLER
	if( GetPadStatus( player1->GetPlayerNumber(), player1->bombKey ) == InputState::Pressed ){
#else
	if( GetKeyStatus( player1->bombKey ) == InputState::Pressed ){
#endif
		if( spriteCounter >= 0 )spriteCounter--;

		if( ruleShowing == true )PlaySoundMem( SceneBase::cursorSEHandle, DX_PLAYTYPE_BACK );
	}

	if( spriteCounter >= COUNTER_MAX ) spriteCounter = -1;
	ruleShowing = ( spriteCounter < 0 ) ? false : true;
}

void TitleScene::Draw() {

	LoadGraphScreen( 0, 0, Sprite::UI::titleScreen, false );

	if( ruleShowing == true ) LoadGraphScreen( 0, 0, ruleSprite[spriteCounter], false );

	SceneFade( SceneList::Setting, 255 / 30, COLOR_WHITE );
}
