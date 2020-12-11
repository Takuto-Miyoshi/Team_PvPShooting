﻿
#include "Header/Common.h"
#include "Header/Player.h"
#include "Header/SceneBase.h"
#include "Header/TitleScene.h"
#include "Header/SettingScene.h"
#include "Header/GameScene.h"
#include "Header/ResultScene.h"

FadeMode SceneBase::fadeMode = FadeMode::None;
SceneList SceneBase::currentScene = SceneList::Title;

#define USE_CONTROLLER
#ifdef USE_CONTROLLER
Player* SceneBase::player1 = new Player( true, DX_INPUT_PAD1, 1, PAD_INPUT_UP, PAD_INPUT_RIGHT, PAD_INPUT_LEFT, PAD_INPUT_DOWN, PAD_INPUT_2, PAD_INPUT_1, PAD_INPUT_4, spriteList[0] );
Player* SceneBase::player2 = new Player( true, DX_INPUT_PAD2, 2, PAD_INPUT_UP, PAD_INPUT_RIGHT, PAD_INPUT_LEFT, PAD_INPUT_DOWN, PAD_INPUT_2, PAD_INPUT_1, PAD_INPUT_4, spriteList[0] );
#else
Player* SceneBase::player1 = new Player( false, 0, 1, KEY_INPUT_UP, KEY_INPUT_RIGHT, KEY_INPUT_LEFT, KEY_INPUT_DOWN, KEY_INPUT_Z, KEY_INPUT_X, KEY_INPUT_C, spriteList[0] );
Player* SceneBase::player2 = new Player( false, 0, 2, KEY_INPUT_W, KEY_INPUT_D, KEY_INPUT_A, KEY_INPUT_S, KEY_INPUT_J, KEY_INPUT_K, KEY_INPUT_L, spriteList[0] );
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
	{ 1, spriteList[2] },
	{ 2, spriteList[3] },
	{ 3, spriteList[4] }
};

int SceneBase::previousScene = 0;
int SceneBase::battleCount = 0;

int SceneBase::players = 0;
Stage SceneBase::stage = stageList[0];

SceneBase::SceneBase() {

}

SceneBase::~SceneBase() {

}

enum SceneList SceneBase::GetCurrentScene() {
	return currentScene;
}

void SceneBase::ReleaseScene() {
	delete pSceneBase[GetCurrentScene()];
	pSceneBase[GetCurrentScene()] = nullptr;
}

void SceneBase::CreateScene() {
	// シーン処理を始める前のシーンを取得する
	previousScene = currentScene;

	// 移行先のシーンがnullならnewする
	if ( pSceneBase[currentScene] != nullptr ) return;

	switch ( currentScene )
	{
	case SceneList::Title:
		pSceneBase[currentScene] = new TitleScene();
		break;
	case SceneList::Setting:
		pSceneBase[currentScene] = new SettingScene();
		break;
	case SceneList::OnPlay:
		pSceneBase[currentScene] = new GameScene();
		break;
	case SceneList::Result:
		pSceneBase[currentScene] = new ResultScene();
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
	if ( previousScene != SceneBase::GetCurrentScene() ) {
		delete pSceneBase[previousScene];
		pSceneBase[previousScene] = nullptr;
	}
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
