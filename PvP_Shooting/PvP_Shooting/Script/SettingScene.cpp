
#include "Header/Common.h"
#include "Header/SceneBase.h"
#include "Header/SettingScene.h"

// #define USE_CONTROLLER

SettingScene::SettingScene() {
	settingStep = 0;

	destinationScene = SceneList::OnPlay;

	preview.x1 = WINDOW_WIDTH / 2 - PREVIEW_WIDTH - 150;
	preview.y1 = WINDOW_HEIGHT / 2 - PREVIEW_HEIGHT / 2;
	preview.x2 = WINDOW_WIDTH / 2 + 150;
	preview.y2 = WINDOW_HEIGHT / 2 - PREVIEW_HEIGHT / 2;
	preview.handle1 = LoadGraph( stageList[0].preview );
	preview.handle2 = LoadGraph( stageList[1].preview );
	preview.currentSelection = 0;

	confirm.x1 = WINDOW_WIDTH / 2 + 200;
	confirm.x2 = WINDOW_WIDTH / 2 + 200;
	confirm.y1 = WINDOW_HEIGHT / 2 - 70;
	confirm.y2 = WINDOW_HEIGHT / 2 + 60;
	confirm.handle1 = LoadGraph( Sprite::UI::selectYes );
	confirm.handle2 = LoadGraph( Sprite::UI::selectNo );
	confirm.currentSelection = 0;

	roundInfoHandle = LoadGraph( Sprite::UI::roundInfo[battleCount] );
	alternativeBackHandle = LoadGraph( Sprite::UI::alternativeBack );
	stagePreviewHandle[0] = LoadGraph( Sprite::UI::stagePreview1 );
	stagePreviewHandle[1] = LoadGraph( Sprite::UI::stagePreview2 );
	backGroundHandle = LoadGraph( Sprite::UI::stageSelectScreen );

	SceneBase::backToTitleSEHandle = LoadSoundMem( Sounds::SE::backToTitle );
	SceneBase::cursorSEHandle = LoadSoundMem( Sounds::SE::cursor );

	SceneBase::BGMHandle = LoadSoundMem( Sounds::BGM::stageSelect );

	SceneBase::SetStage( SceneBase::stageList[preview.currentSelection] );
}

SettingScene::~SettingScene() {

}

void SettingScene::Execute() {
	Control();
	Draw();
}

void SettingScene::Control() {

	if( fadeMode != FadeMode::None ) return;

#ifdef USE_CONTROLLER
	if( ( GetPadStatus( player1->GetPlayerNumber(), PAD_INPUT_8 ) == InputState::Pressed ) ||
		( GetPadStatus( player1->GetPlayerNumber(), PAD_INPUT_9 ) == InputState::Pressed ) ||
		( GetPadStatus( player1->GetPlayerNumber(), PAD_INPUT_10 ) == InputState::Pressed ) ){
#else
	if( GetKeyStatus( KEY_INPUT_RETURN ) == InputState::Pressed ) {
#endif
		destinationScene = SceneList::Title;
		fadeMode = FadeMode::Out;
		PlaySoundMem( SceneBase::backToTitleSEHandle, DX_PLAYTYPE_BACK );
		return;
	}

	switch( settingStep )
	{
	case 0: SetStage(); break;
	case 1: Confirm(); break;
	default: settingStep = 0; break;
	}
}

void SettingScene::Draw() {

	SettingScene::DrawBackground();

	// ラウンド数表示
	DrawGraph( 0, 0, roundInfoHandle, true );

	switch( settingStep )
	{
	case 0:
		// プレビュー表示
		DrawExtendGraph( preview.x1 - 50, preview.y1 - 50, preview.x1 + PREVIEW_WIDTH + 50, preview.y1 + PREVIEW_HEIGHT + 50, preview.handle1, false );
		DrawGraph( preview.x2, preview.y2, preview.handle2, false );
		break;
	case 1:
		// 確認
		DrawGraph( 0, WINDOW_HEIGHT / 2 - 256, alternativeBackHandle, false );
		DrawGraph( 300, WINDOW_HEIGHT / 2 - PREVIEW_HEIGHT / 2, stagePreviewHandle[SceneBase::GetStage().number - 1], false );
		DrawExtendGraph( confirm.x1 - 32, confirm.y1 - 10, confirm.x1 + 352, confirm.y1 + 110, confirm.handle1, true );
		DrawGraph( confirm.x2, confirm.y2, confirm.handle2, true );
		break;
	}

	SceneFade( destinationScene, 255 / 30, COLOR_BLACK );
}

void SettingScene::SetStage(){

	// 方向キーで情報を入れ替える
#ifdef USE_CONTROLLER
	if( GetPadStatus( player1->GetPlayerNumber(), player1->rightMovingKey ) == InputState::Pressed ||
		GetPadStatus( player1->GetPlayerNumber(), player1->leftMovingKey ) == InputState::Pressed ){
#else
	if( GetKeyStatus( player1->rightMovingKey ) == InputState::Pressed ||
		GetKeyStatus( player1->leftMovingKey ) == InputState::Pressed ){
#endif
		SettingScene::ReplaceData( &preview );

		PlaySoundMem( SceneBase::cursorSEHandle, DX_PLAYTYPE_BACK );

		SceneBase::SetStage( SceneBase::stageList[preview.currentSelection] );
	}

#ifdef USE_CONTROLLER
	if( GetPadStatus( player1->GetPlayerNumber(), player1->shotKey ) == InputState::Pressed )settingStep++;
#else
	if( GetKeyStatus( player1->shotKey ) == InputState::Pressed )settingStep++;
#endif
}

void SettingScene::Confirm(){

	// 方向キーで情報を入れ替える
#ifdef USE_CONTROLLER
	if( GetPadStatus( player1->GetPlayerNumber(), player1->upMovingKey ) == InputState::Pressed ||
		GetPadStatus( player1->GetPlayerNumber(), player1->downMovingKey ) == InputState::Pressed ){
#else
	if( GetKeyStatus( player1->upMovingKey ) == InputState::Pressed ||
		GetKeyStatus( player1->downMovingKey ) == InputState::Pressed ){
#endif
		SettingScene::ReplaceData( &confirm );

		PlaySoundMem( SceneBase::cursorSEHandle, DX_PLAYTYPE_BACK );
	}

#ifdef USE_CONTROLLER
	if( GetPadStatus( player1->GetPlayerNumber(), player1->shotKey ) == InputState::Pressed ){
#else
	if( GetKeyStatus( player1->shotKey ) == InputState::Pressed ){
#endif
		switch( confirm.currentSelection )
		{
		case 0:
			fadeMode = FadeMode::Out;
			break;
		default:
			settingStep--;
			break;
		}
	}
}

void SettingScene::ReplaceData( AlternativeData* data ){
	int temp = data->x1;
	data->x1 = data->x2;
	data->x2 = temp;

	temp = data->y1;
	data->y1 = data->y2;
	data->y2 = temp;

	temp = data->handle1;
	data->handle1 = data->handle2;
	data->handle2 = temp;

	data->currentSelection++;
	data->currentSelection = data->currentSelection % 2;
}

void SettingScene::DrawBackground(){

	int x = -WINDOW_WIDTH / 2;

	x += SceneBase::playerList[0]->GetScore( -1 ) * 48;
	x -= SceneBase::playerList[1]->GetScore( -1 ) * 48;

	if( x < -WINDOW_WIDTH ){
		x = -WINDOW_WIDTH + 48;
	}
	else if( x > 0 ){
		x = -48;
	}

	// 描画
	DrawGraph( x, 0, backGroundHandle, false );
}
