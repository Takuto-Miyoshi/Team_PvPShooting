
#include "Header/Common.h"
#include "Header/SceneBase.h"
#include "Header/ResultScene.h"

#define USE_CONTROLLER

ResultScene::ResultScene() {
	SceneBase::backToTitleSEHandle = LoadSoundMem( Sounds::SE::backToTitle );
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
	DrawGraph( 0, 0, resultBackHandle, false );
	SceneFade( SceneList::Title, 255 / 60, COLOR_BLUE );
}

void ResultScene::Result(){

	int winner = -1;
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
