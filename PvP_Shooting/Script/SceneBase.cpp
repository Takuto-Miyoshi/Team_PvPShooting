
#include "Header/Common.h"

FadeMode SceneBase::fadeMode = FadeMode::None;
SceneList SceneBase::currentScene = SceneList::Title;

SceneBase* SceneBase::sc_title  = nullptr;
SceneBase* SceneBase::sc_onPlay = nullptr;
SceneBase* SceneBase::sc_result = nullptr;
SceneBase* SceneBase::pSceneBase[3] = {
	sc_title,
	sc_onPlay,
	sc_result
};

int SceneBase::previousScene = 0;

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
