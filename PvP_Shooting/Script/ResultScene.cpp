
#include "Header/Common.h"

ResultScene::ResultScene() {

}

ResultScene::~ResultScene() {

}

void ResultScene::Execute() {
	Control();
	Draw();
}

void ResultScene::Control() {

	if ( fadeMode != FadeMode::None ) return;

	if ( CheckHitKey( KEY_INPUT_3 ) ) {
		fadeMode = FadeMode::Out;
	}
}

void ResultScene::Draw() {

	DrawString( 10, 10, "Result", COLOR_RED );
	DrawString( 10, 30, "Press 3 to Title Scene", COLOR_RED );

	SceneFade( SceneList::Title, 255 / 60, COLOR_BLUE );
}
