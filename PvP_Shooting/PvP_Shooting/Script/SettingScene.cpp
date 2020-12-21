
#include "Header/Common.h"
#include "Header/SceneBase.h"
#include "Header/SettingScene.h"

// #define USE_CONTROLLER

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

	if( fadeMode != FadeMode::None ) return;

	switch( settingStep ){
	case -2:fadeMode = FadeMode::Out; return; break;
	case -1:settingStep = 0;
	case 0:SetStage(); break;
	default:Confirm(); return; break;
	}

#ifdef USE_CONTROLLER
	if( GetPadStatus( player1->GetPlayerNumber(), player1->shotKey ) == InputState::Pressed )settingStep++;
	else if( GetPadStatus( player1->GetPlayerNumber(), player1->bombKey ) == InputState::Pressed )settingStep--;
#else
	if( GetKeyStatus( player1->shotKey ) == InputState::Pressed )settingStep++;
	else if( GetKeyStatus( player1->bombKey ) == InputState::Pressed )settingStep--;
#endif
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
#ifdef USE_CONTROLLER
	if( GetPadStatus( player1->GetPlayerNumber(), player1->rightMovingKey ) == InputState::Pressed )currentSelection++;
	else if( GetPadStatus( player1->GetPlayerNumber(), player1->leftMovingKey ) == InputState::Pressed )currentSelection--;
#else
	if( GetKeyStatus( player1->rightMovingKey ) == InputState::Pressed )currentSelection++;
	else if( GetKeyStatus( player1->leftMovingKey ) == InputState::Pressed )currentSelection--;
#endif

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

void SettingScene::Confirm(){

	LoadGraphScreen( 300, WINDOW_HEIGHT / 2 - PREVIEW_HEIGHT / 2, SceneBase::GetStage().preview, false );

	static int currentSelection = 0;
	static int triangleY = WINDOW_HEIGHT / 2 - PREVIEW_HEIGHT / 3 + 100 + GetFontSize() / 2;

	// カーソル表示
#ifdef USE_CONTROLLER
	if( GetPadStatus( player1->GetPlayerNumber(), player1->downMovingKey ) == InputState::Pressed )currentSelection++;
	else if( GetPadStatus( player1->GetPlayerNumber(), player1->upMovingKey ) == InputState::Pressed )currentSelection--;
#else
	if( GetKeyStatus( player1->downMovingKey ) == InputState::Pressed )currentSelection++;
	else if( GetKeyStatus( player1->upMovingKey ) == InputState::Pressed )currentSelection--;
#endif

	switch( currentSelection )	{
	case -1:currentSelection = 1;	break;
	case 0:triangleY = WINDOW_HEIGHT / 2 - PREVIEW_HEIGHT / 3 + 100 + GetFontSize() / 2; break;
	case 1:triangleY = WINDOW_HEIGHT / 2 - PREVIEW_HEIGHT / 3 + 200 + GetFontSize() / 2; break;
	default:currentSelection = 0;	break;
	}

	DrawTriangle( WINDOW_WIDTH / 2, triangleY + 25,
			 	  WINDOW_WIDTH / 2 + 50, triangleY,
			 	  WINDOW_WIDTH / 2, triangleY - 25, COLOR_RED, true );

	DrawString( WINDOW_WIDTH / 2 + 200 - CenterAdjustment( 26 ), WINDOW_HEIGHT / 2 - PREVIEW_HEIGHT / 3, "このステージでいいですか？", COLOR_GREEN, COLOR_RED );
	DrawString( WINDOW_WIDTH / 2 + 200 - CenterAdjustment( 4 ), WINDOW_HEIGHT / 2 - PREVIEW_HEIGHT / 3 + 100, "はい", COLOR_GREEN, COLOR_RED );
	DrawString( WINDOW_WIDTH / 2 + 200 - CenterAdjustment( 6 ), WINDOW_HEIGHT / 2 - PREVIEW_HEIGHT / 3 + 200, "いいえ", COLOR_GREEN, COLOR_RED );

#ifdef USE_CONTROLLER
	if( GetPadStatus( player1->GetPlayerNumber(), player1->shotKey ) == InputState::Pressed ){
#else
	if( GetKeyStatus( player1->shotKey ) == InputState::Pressed ){
#endif
		settingStep = ( currentSelection == 0 ) ? -2 : 0;
	}
}
