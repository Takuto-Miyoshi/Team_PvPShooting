
#include "Header/Common.h"
#include "Header/SceneBase.h"
#include "Header/ResultScene.h"

// #define USE_CONTROLLER

int ResultScene::winBannerHandle[Sprite::UI::winBannerFrame] = {};
int ResultScene::spriteNum = 0;
int ResultScene::counter = 0;

ResultScene::ResultScene() {
	winner = 0;
	SceneBase::backToTitleSEHandle = LoadSoundMem( Sounds::SE::backToTitle );
	for( int i = 0; i < Sprite::UI::winBannerFrame; i++ ){
		winBannerHandle[i] = LoadGraph( Sprite::UI::winBanner[i] );
	}

	Result();
	PlaySoundMem( resultJingleHandle, DX_PLAYTYPE_BACK );
}

ResultScene::~ResultScene() {

}

void ResultScene::Execute() {
	Control();
	Draw();
}

void ResultScene::Control() {

	if( fadeMode != FadeMode::None ) return;

	counter++;
	if( counter >= FRAME_RATE / 10 ) {
		spriteNum++;
		counter = 0;
		if( spriteNum >= Sprite::UI::winBannerFrame ) spriteNum = 0;
	}

#ifdef USE_CONTROLLER
	if( ( GetPadStatus( player1->GetPlayerNumber(), PAD_INPUT_8 ) == InputState::Pressed ) ||
		( GetPadStatus( player1->GetPlayerNumber(), PAD_INPUT_9 ) == InputState::Pressed ) ||
		( GetPadStatus( player1->GetPlayerNumber(), PAD_INPUT_10 ) == InputState::Pressed ) ){
#else
	if( GetKeyStatus( KEY_INPUT_RETURN ) == InputState::Pressed ){
#endif
		fadeMode = FadeMode::Out;
		PlaySoundMem( SceneBase::backToTitleSEHandle, DX_PLAYTYPE_BACK );
	}
}

void ResultScene::Draw() {
	DrawGraph( 0, 0, resultBackHandle, false );

	if( winner != 0 ){
		DrawGraph( 629, 138, winBannerHandle[spriteNum], true );
	}
	SceneFade( SceneList::Title, 255 / 60, COLOR_BLACK );
}

void ResultScene::Result(){

	if( SceneBase::player1->GetScore( -1 ) == SceneBase::player2->GetScore( -1 ) )winner = 0;
	else winner = ( SceneBase::player1->GetScore( -1 ) > SceneBase::player2->GetScore( -1 ) ) ? 1 : 2;

	switch( winner ){
	case 0:
		resultBackHandle = LoadGraph( Sprite::UI::resultDraw );
		resultJingleHandle = LoadSoundMem( Sounds::SE::resultDraw );
		break;
	case 1:
		resultBackHandle = LoadGraph( Sprite::UI::resultNobunaga );
		resultJingleHandle = LoadSoundMem( Sounds::SE::result );
		break;
	case 2:
		resultBackHandle = LoadGraph( Sprite::UI::resultNapoleon );
		resultJingleHandle = LoadSoundMem( Sounds::SE::result );
		break;
	}
}
