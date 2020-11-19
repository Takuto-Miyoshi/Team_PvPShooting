
#include "Header/Common.h"

TitleScene::TitleScene() {

}

TitleScene::~TitleScene() {

}

void TitleScene::Execute() {
	Control();
	Draw();
}

void TitleScene::Control() {

	if ( fadeMode != FadeMode::None ) return;

	if ( CheckHitKey( KEY_INPUT_1 ) ) {
		fadeMode = FadeMode::Out;
	}
}

void TitleScene::Draw() {

	DrawString( 10, 10, "Title", COLOR_RED );
	DrawString( 10, 30, "Press 1 to OnPlay Scene", COLOR_RED );

	SceneFade( SceneList::OnPlay, 255 / 60, COLOR_WHITE, 60 );
}
