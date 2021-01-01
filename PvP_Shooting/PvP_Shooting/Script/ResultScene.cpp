﻿
#include "Header/Common.h"
#include "Header/SceneBase.h"
#include "Header/ResultScene.h"

#define USE_CONTROLLER

ResultScene::ResultScene() {
	SceneBase::backToTitleSEHandle = LoadSoundMem( Sounds::SE::backToTitle );
}

ResultScene::~ResultScene() {

}

void ResultScene::Execute() {
	Control();
	Draw();
}

void ResultScene::Control() {

	if( fadeMode != FadeMode::None ) return;

#ifdef USE_CONTROLLER
	if( GetPadStatus( player1->GetPlayerNumber(), PAD_INPUT_8 ) == InputState::Pressed ){
#else
	if( GetKeyStatus( KEY_INPUT_RETURN ) == InputState::Pressed ){
#endif
		fadeMode = FadeMode::Out;
		PlaySoundMem( SceneBase::backToTitleSEHandle, DX_PLAYTYPE_BACK );
	}
}

void ResultScene::Draw() {

	DrawString( 10, 10, "Result", COLOR_RED );
	DrawString( 10, 30, "Press 3 to Title Scene", COLOR_RED );

	DrawResult();

	SceneFade( SceneList::Title, 255 / 60, COLOR_BLUE );
}

void ResultScene::DrawResult(){

	int winner = -1;
	if( SceneBase::player1->GetScore( -1 ) == SceneBase::player2->GetScore( -1 ) )winner = 0;
	else winner = ( SceneBase::player1->GetScore( -1 ) > SceneBase::player2->GetScore( -1 ) ) ? 1 : 2;

	for( int p = 0; p < PLAYER_MAX; p++ ){
		int drawX = 400;
		int drawY = 300;
		if( p == 1 )drawX = WINDOW_WIDTH - 400;
		DrawFormatString( drawX - CenterAdjustment( 2 ), drawY, COLOR_RED, "%dP", p + 1 );
		drawY += 100;
		for( int r = 0; r < ROUND_MAX; r++ ){
			DrawFormatString( drawX - CenterAdjustment( 7 ), drawY, COLOR_WHITE, "%dR : %2d", r + 1, playerList[p]->GetScore( r + 1 ) );
			drawY += 100;
		}
		DrawFormatString( drawX - CenterAdjustment( 11 ), drawY, COLOR_WHITE, "Total : %3d", playerList[p]->GetScore( -1 ) );
	}

	// 結果
	LPCTSTR winnerScreen = "";
	switch( winner ){
	case 0:winnerScreen = Sprite::UI::resultDraw; break;
	case 1:winnerScreen = Sprite::UI::resultNobunaga; break;
	case 2:winnerScreen = Sprite::UI::resultNapoleon; break;
	}
	LoadGraphScreen( 0, 0, winnerScreen, false );
}
