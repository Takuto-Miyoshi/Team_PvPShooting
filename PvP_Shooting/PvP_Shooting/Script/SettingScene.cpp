
#include "Header/Common.h"
#include "Header/SceneBase.h"
#include "Header/SettingScene.h"

SettingScene::SettingScene() {
	settingStep = 0;
}

SettingScene::~SettingScene() {
}

void SettingScene::Execute() {
	Control();
	Draw();
}

void SettingScene::Control() {

	switch( settingStep ){
	case -1:settingStep = 0;
	case 0:SetStage();		 break;
	case 1:Confirm( false ); break;
	case 2:Confirm( true );	 break;
	default:settingStep = 0; break;
	}

	if( fadeMode != FadeMode::None ) return;

	if( GetKeyStatus( KEY_INPUT_RETURN ) == InputState::Pressed )settingStep++;
	else if( GetKeyStatus( KEY_INPUT_SPACE ) == InputState::Pressed )settingStep--;
}

void SettingScene::Draw() {

	DrawString( 10, 10, "Setting", COLOR_RED );

	SceneFade( SceneList::OnPlay, 255 / 60, 255 / 60, COLOR_WHITE, COLOR_BLACK );
}

void SettingScene::SetStage(){

	// ラウンド数表示
	DrawFormatString( WINDOW_WIDTH / 2 - CenterAdjustment( 7 ), 100, COLOR_BLUE, "Round %d", SceneBase::battleCount + 1 );

	// ステージプレビュー
	LoadGraphScreen( WINDOW_WIDTH / 2 - PREVIEW_WIDTH * 2 - PREVIEW_WIDTH / 2,	WINDOW_HEIGHT / 2 - PREVIEW_HEIGHT / 2, stageList[0].preview, false );
	LoadGraphScreen( WINDOW_WIDTH / 2 - PREVIEW_WIDTH / 2,						WINDOW_HEIGHT / 2 - PREVIEW_HEIGHT / 2, stageList[1].preview, false );
	LoadGraphScreen( WINDOW_WIDTH / 2 + PREVIEW_WIDTH + PREVIEW_WIDTH / 2,		WINDOW_HEIGHT / 2 - PREVIEW_HEIGHT / 2, stageList[2].preview, false );

	static int currentSelection = 0;
	static int triangleX = -500;

	// カーソル表示
	if( GetKeyStatus( KEY_INPUT_RIGHT ) == InputState::Pressed )currentSelection++;
	else if( GetKeyStatus( KEY_INPUT_LEFT ) == InputState::Pressed )currentSelection--;

	switch( currentSelection )	{
	case -1	:currentSelection = 2;	break;
	case 0	:triangleX = -PREVIEW_WIDTH * 2; break;
	case 1	:triangleX = 0;					 break;
	case 2	:triangleX =  PREVIEW_WIDTH * 2; break;
	default	:currentSelection = 0;	break;
	}

	DrawTriangle( WINDOW_WIDTH / 2 + triangleX + 50, WINDOW_HEIGHT / 2 - 350,
				  WINDOW_WIDTH / 2 + triangleX,		 WINDOW_HEIGHT / 2 - 250,
				  WINDOW_WIDTH / 2 + triangleX - 50, WINDOW_HEIGHT / 2 - 350, COLOR_RED, true );

	SceneBase::SetStage( SceneBase::stageList[currentSelection] );
}

void SettingScene::Confirm( bool confirmed ){

	LoadGraphScreen( 300, WINDOW_HEIGHT / 2 - PREVIEW_HEIGHT / 2, SceneBase::GetStage().preview, false );
	LPCSTR temp = "READY?";
	if( confirmed == true ){
		temp = "START!!";
		fadeMode = FadeMode::Out;
	}
	DrawString( WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 - PREVIEW_HEIGHT / 3, temp, COLOR_GREEN, COLOR_RED );
}
