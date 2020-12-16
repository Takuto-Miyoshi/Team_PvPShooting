
#include "Header/Common.h"
#include "Header/Player.h"
#include "Header/SceneBase.h"
#include "Header/TitleScene.h"
#include "Header/SettingScene.h"
#include "Header/GameScene.h"
#include "Header/ResultScene.h"

// #define USE_CONTROLLER

FadeMode SceneBase::fadeMode = FadeMode::None;
SceneList SceneBase::currentScene = SceneList::Title;

#ifdef USE_CONTROLLER
Player* SceneBase::player1 = new Player ( DX_INPUT_PAD1, 1, PAD_INPUT_UP, PAD_INPUT_RIGHT, PAD_INPUT_LEFT, PAD_INPUT_DOWN, PAD_INPUT_2, PAD_INPUT_1, PAD_INPUT_4 );
Player* SceneBase::player2 = new Player ( DX_INPUT_PAD2, 2, PAD_INPUT_UP, PAD_INPUT_RIGHT, PAD_INPUT_LEFT, PAD_INPUT_DOWN, PAD_INPUT_2, PAD_INPUT_1, PAD_INPUT_4 );
#else
Player* SceneBase::player1 = new Player ( 0, 1, KEY_INPUT_UP, KEY_INPUT_RIGHT, KEY_INPUT_LEFT, KEY_INPUT_DOWN, KEY_INPUT_Z, KEY_INPUT_X, KEY_INPUT_C );
Player* SceneBase::player2 = new Player ( 0, 2, KEY_INPUT_W, KEY_INPUT_D, KEY_INPUT_A, KEY_INPUT_S, KEY_INPUT_J, KEY_INPUT_K, KEY_INPUT_L );
#endif

Player* SceneBase::playerList[PLAYER_MAX] {
	player1,
	player2
};

SceneBase* SceneBase::sc_title  = nullptr;
SceneBase* SceneBase::sc_setting = nullptr;
SceneBase* SceneBase::sc_onPlay = nullptr;
SceneBase* SceneBase::sc_result = nullptr;
SceneBase* SceneBase::pSceneBase[4] = {
	sc_title,
	sc_setting,
	sc_onPlay,
	sc_result
};

Stage SceneBase::stageList[3] {
	{ 1, Sprite::stgPreview1 },
	{ 2, Sprite::stgPreview2 },
	{ 3, Sprite::stgPreview3 }
};

int SceneBase::previousScene = 0;
int SceneBase::battleCount = 0;

int SceneBase::players = 0;
Stage SceneBase::stage = stageList[0];

SceneBase::SceneBase() {

}

SceneBase::~SceneBase() {

}

int SceneBase::GetCurrentScene() {
	switch( currentScene )
	{
	case SceneList::Title:return 0; break;
	case SceneList::Setting:return 1; break;
	case SceneList::OnPlay:return 2; break;
	case SceneList::Result:return 3; break;
	default:return 0; break;
	}
}

void SceneBase::ReleaseScene() {
	delete pSceneBase[GetCurrentScene()];
	pSceneBase[GetCurrentScene()] = nullptr;
}

void SceneBase::CreateScene() {

	// シーン処理を始める前のシーンを取得する
	previousScene = GetCurrentScene();

	// 移行先のシーンがnullならnewする
	if ( pSceneBase[GetCurrentScene()] != nullptr ) return;

	switch ( currentScene )
	{
	case SceneList::Title:
		pSceneBase[GetCurrentScene()] = new TitleScene();
		break;
	case SceneList::Setting:
		pSceneBase[GetCurrentScene()] = new SettingScene();
		break;
	case SceneList::OnPlay:
		pSceneBase[GetCurrentScene()] = new GameScene();
		break;
	case SceneList::Result:
		pSceneBase[GetCurrentScene()] = new ResultScene();
		break;
	default:
		break;
	}
}

void SceneBase::ExecuteScene() {
	// シーンの処理
	if ( pSceneBase[previousScene] == nullptr ) return;
	pSceneBase[previousScene]->Execute();
}

void SceneBase::ReleaseCurrentScene() {
	// シーンに変化があるなら今のシーンはdeleteする
	if ( previousScene != GetCurrentScene() ) {
		delete pSceneBase[previousScene];
		pSceneBase[previousScene] = nullptr;
	}
}

Player* SceneBase::GetPlayerData( int playerNumber ){
	return playerList[playerNumber];
}

void SceneBase::SceneFade( SceneList destinationScene, int fadePower, int fadeColor, int waitTime) {
	if ( fadeMode == FadeMode::In ) {
		if ( FadeIn( fadePower, fadeColor, waitTime ) ) {
			fadeMode = FadeMode::None;
		}
	}
	else if ( fadeMode == FadeMode::Out ) {
		if ( FadeOut( fadePower, fadeColor, waitTime ) ) {
			currentScene = destinationScene;
			fadeMode = FadeMode::In;
		}
	}
}

void SceneBase::SceneFade( SceneList destinationScene, int inPower, int outPower, int inColor, int outColor, int inWaitTime, int outWaitTime ) {
	if ( fadeMode == FadeMode::In ) {
		if ( FadeIn( inPower, inColor, inWaitTime ) ) {
			fadeMode = FadeMode::None;
		}
	}
	else if ( fadeMode == FadeMode::Out ) {
		if ( FadeOut( outPower, outColor, outWaitTime ) ) {
			currentScene = destinationScene;
			fadeMode = FadeMode::In;
		}
	}
}

void SceneBase::SetStage( Stage stg ){
	stage = stg;
}

Stage SceneBase::GetStage(){
	return stage;
}

void SceneBase::Reset(){

	battleCount = 0;

	for( int i = 0; i < PLAYER_MAX; i++ ){
		playerList[i]->SetAlive( true );
		playerList[i]->ResetScore();
		playerList[i]->SetPosY( WINDOW_HEIGHT / 2 - PLAYER_HEIGHT / 2 );
	}

	playerList[0]->SetPosX( 200 );
	playerList[1]->SetPosX( WINDOW_WIDTH - 200 - PLAYER_WIDTH );
}
