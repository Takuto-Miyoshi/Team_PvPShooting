
#include "Header/Common.h"
#include "Header/SceneBase.h"
#include "Header/TitleScene.h"

#define USE_CONTROLLER

TitleScene::TitleScene() {
	ruleShowing = false;
	spriteCounter = -1;

	backGroundHandle = LoadGraph( Sprite::UI::titleScreen );
	ruleSprite[0] = LoadGraph( Sprite::UI::descriptionRule1 );
	ruleSprite[1] = LoadGraph( Sprite::UI::descriptionRule2 );
	ruleSprite[2] = LoadGraph( Sprite::UI::descriptionControl );

	SceneBase::startTitleSEHandle = LoadSoundMem( Sounds::SE::titleStart );
	SceneBase::cursorSEHandle = LoadSoundMem( Sounds::SE::cursor );
	SceneBase::enterSEHandle = LoadSoundMem( Sounds::SE::enter );

	SceneBase::BGMHandle = LoadSoundMem( Sounds::BGM::title );
	tutorialBGMHandle = LoadSoundMem( Sounds::BGM::tutorial );
	ChangeVolumeSoundMem( 128, tutorialBGMHandle );

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
	if( ( GetPadStatus( player1->GetPlayerNumber(), PAD_INPUT_8 ) == InputState::Pressed ) ||
		( GetPadStatus( player1->GetPlayerNumber(), PAD_INPUT_9 ) == InputState::Pressed ) ||
		( GetPadStatus( player1->GetPlayerNumber(), PAD_INPUT_10 ) == InputState::Pressed ) ){
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
			StopSoundMem( SceneBase::BGMHandle );
			PlaySoundMem( tutorialBGMHandle, DX_PLAYTYPE_LOOP );
		}
		else{
			PlaySoundMem( SceneBase::cursorSEHandle, DX_PLAYTYPE_BACK );
		}

		if( spriteCounter >= COUNTER_MAX ){
			StopSoundMem( tutorialBGMHandle );
			PlaySoundMem( SceneBase::BGMHandle, DX_PLAYTYPE_LOOP, FALSE );
		}
	}

#ifdef USE_CONTROLLER
	if( GetPadStatus( player1->GetPlayerNumber(), player1->bombKey ) == InputState::Pressed ){
#else
	if( GetKeyStatus( player1->bombKey ) == InputState::Pressed ){
#endif
		if( spriteCounter >= 0 )spriteCounter--;

		if( ruleShowing == true )PlaySoundMem( SceneBase::cursorSEHandle, DX_PLAYTYPE_BACK );

		if( spriteCounter < 0 ){
			StopSoundMem( BGMHandle );
			StopSoundMem( tutorialBGMHandle );
			PlaySoundMem( SceneBase::BGMHandle, DX_PLAYTYPE_LOOP, FALSE );
		}
	}

	if( spriteCounter >= COUNTER_MAX ) spriteCounter = -1;
	ruleShowing = ( spriteCounter < 0 ) ? false : true;
}

void TitleScene::Draw() {

	DrawGraph( 0, 0, backGroundHandle, false );

	if( ruleShowing == true ) DrawGraph( 0, 0, ruleSprite[spriteCounter], false );

	SceneFade( SceneList::Setting, 255 / 30, COLOR_BLACK );
}
