
#include "Header/Common.h"
#include "Header/SceneBase.h"
#include "Header/TitleScene.h"

TitleScene::TitleScene() {
	ruleShowing = false;
	spriteCounter = 0;
	SceneBase::Reset();
}

TitleScene::~TitleScene() {

}

void TitleScene::Execute() {
	Control();
	Draw();
}

void TitleScene::Control() {

	if ( fadeMode != FadeMode::None ) return;

	if( GetKeyStatus( KEY_INPUT_SPACE ) == InputState::Pressed ){
		ruleShowing = ( ruleShowing == false ) ? true : false;
		spriteCounter = 0;
	}
	if( GetKeyStatus( KEY_INPUT_RETURN ) == InputState::Pressed )fadeMode = FadeMode::Out;
}

void TitleScene::Draw() {

	DrawString( 10, 10, "Title", COLOR_RED );
	DrawString( 10, 30, "Press Enter Start", COLOR_RED );

	if( ruleShowing == true ){
		ShowRule();
	}

	SceneFade( SceneList::Setting, 255 / 60, COLOR_WHITE, 60 );
}

void TitleScene::ShowRule(){

	LoadGraphScreen( 0, 0, RuleSprite[spriteCounter], false );

	if( GetKeyStatus( KEY_INPUT_RIGHT ) == InputState::Pressed ){
		if( spriteCounter < COUNTER_MAX )spriteCounter++;
	}
	else if( GetKeyStatus( KEY_INPUT_LEFT ) == InputState::Pressed ){
		if( spriteCounter > 0 )spriteCounter--;
	}
}
