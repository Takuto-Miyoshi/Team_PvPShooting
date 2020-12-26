
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
	if( GetPadStatus( player1->GetPlayerNumber(), PAD_INPUT_8 ) == InputState::Pressed ) fadeMode = FadeMode::Out;

	if( GetPadStatus( player1->GetPlayerNumber(), player1->shotKey ) == InputState::Pressed ){
		if( spriteCounter < COUNTER_MAX )spriteCounter++;
	}

	if( GetPadStatus( player1->GetPlayerNumber(), player1->bombKey ) == InputState::Pressed ){
		if( spriteCounter >= 0 )spriteCounter--;
	}
#else
	if( GetKeyStatus( KEY_INPUT_RETURN ) == InputState::Pressed )fadeMode = FadeMode::Out;

	if( GetKeyStatus( player1->shotKey ) == InputState::Pressed ){
		spriteCounter++;
	}

	if( GetKeyStatus( player1->bombKey ) == InputState::Pressed ){
		if( spriteCounter >= 0 ) spriteCounter--;
	}
#endif

	if( spriteCounter >= COUNTER_MAX ) spriteCounter = -1;
	ruleShowing = ( spriteCounter < 0 ) ? false : true;
}

void TitleScene::Draw() {

	LoadGraphScreen( 0, 0, Sprite::UI::titleScreen, false );

	if( ruleShowing == true ) LoadGraphScreen( 0, 0, ruleSprite[spriteCounter], false );

	SceneFade( SceneList::Setting, 255 / 30, COLOR_WHITE );
}
