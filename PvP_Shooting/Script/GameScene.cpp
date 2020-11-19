
#include "Header/Common.h"

GameScene::GameScene() {

}

GameScene::~GameScene() {

}

void GameScene::Execute() {
	Control();
	Draw();
}

void GameScene::Control() {
	Player::Move();

	if ( fadeMode != FadeMode::None ) return;

	if ( CheckHitKey( KEY_INPUT_2 ) ) {
		fadeMode = FadeMode::Out;
	}
	
}

void GameScene::Draw() {

	Player::Draw();

	DrawString( 10, 10, "OnPlay", COLOR_RED );
	DrawString( 10, 30, "Press 2 to Result Scene", COLOR_RED );

	SceneFade( SceneList::Result, 255 / 120, 255 / 60, COLOR_WHITE, COLOR_BLUE, 30 );
}
