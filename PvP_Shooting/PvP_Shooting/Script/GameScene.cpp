
#include "Header/Common.h"
#include "Header/SceneBase.h"
#include "Header/GameScene.h"
#include "Header/Player.h"

int GameScene::counter = 0;
int GameScene::startCounter = 0;
int GameScene::endCounter = 0;
bool GameScene::isOperatable = false;

GameScene::GameScene() {
	counter = 0;
	startCounter = 0;
	endCounter = 0;
	for( int p = 0; p < PLAYER_MAX; p++ ){
		for( int b = 0; b < BULLET_MAX; b++ ){
			playerList[p]->DeleteBullet( b );
		}
		playerList[p]->SetPosY( WINDOW_HEIGHT / 2 - PLAYER_HEIGHT / 2 );
	}
	playerList[0]->SetPosX( 200 );
	playerList[1]->SetPosX( WINDOW_WIDTH - 200 - PLAYER_WIDTH );
}

GameScene::~GameScene() {

}

void GameScene::Execute() {

	GameManager();
	Control();
	Draw();
}

void GameScene::Control() {

	if( fadeMode != FadeMode::None ) return;
	if( isOperatable != true )return;

	for( int i = 0; i < PLAYER_MAX; i++ ){
		SceneBase::playerList[i]->Move();
		SceneBase::playerList[i]->Shoot();
		SceneBase::playerList[i]->Respawn();
		HitManager( SceneBase::playerList[i] );
	}
}

void GameScene::Draw() {

	for( int i = 0; i < PLAYER_MAX; i++ ){
		playerList[i]->Draw();
	}

	DrawString( 10, 10, "OnPlay", COLOR_RED );

	if( battleCount >= 3 )SceneFade( SceneList::Result, 255, 255 / 60, COLOR_BLACK, COLOR_BLUE );
	else SceneFade( SceneList::Setting, 255, 255 / 60, COLOR_BLACK, COLOR_GREEN );
}

void GameScene::HitManager( Player* target ){

	for( int playerNum = 0; playerNum < PLAYER_MAX; playerNum++ ){
		for( int bulletNum = 0; bulletNum < BULLET_MAX; bulletNum++ ){
			// 例外は弾く
			if( playerList[playerNum]->GetBulletData( bulletNum ) != nullptr &&
				target->GetPlayerNumber() != playerList[playerNum]->GetPlayerNumber() &&
				target->GetAlive() == true ){
				// -------------------------------------------当たり判定---------------------------------------------------------
				if( ( target->GetPosX() + PLAYER_WIDTH ) > playerList[playerNum]->GetBulletData( bulletNum )->GetPosX() &&
					target->GetPosX() < ( playerList[playerNum]->GetBulletData( bulletNum )->GetPosX() + BULLET_WIDTH ) &&
					( target->GetPosY() + PLAYER_HEIGHT ) > playerList[playerNum]->GetBulletData( bulletNum )->GetPosY() &&
					target->GetPosY() < ( playerList[playerNum]->GetBulletData( bulletNum )->GetPosY() + BULLET_HEIGHT ) ){
					//-----------------------------------------------------------------------------------------------------------
					playerList[playerNum]->DeleteBullet( bulletNum );
					target->DeathProcessing();
					playerList[playerNum]->AddScore( 1, SceneBase::battleCount + 1 );
				}
			}
		}
	}
}

void GameScene::GameManager(){

	isOperatable = false;

	if( counter == 0 ){ Start(); return; }
	if( counter == 60 * 60 ){ End(); return; }

	counter++;
	isOperatable = true;

	DrawFormatString( WINDOW_WIDTH / 2 - CenterAdjustment( 3 ), 100, COLOR_GREEN, "%2d", 60 - counter / 60 );
}

void GameScene::Start(){

	static LPCTSTR countDownText = "   3   ";

	switch( startCounter ){
	case 0: countDownText = "   3   "; break;
	case 60:countDownText = "   2   "; break;
	case 120:countDownText = "   1   "; break;
	case 180:countDownText = "Start!!"; break;
	case 210:counter++; break;
	}

	startCounter++;

	DrawString( WINDOW_WIDTH / 2 - CenterAdjustment( 7 ), WINDOW_HEIGHT / 2, countDownText, COLOR_RED );

}

void GameScene::End(){

	if( endCounter >= 60 ){
		fadeMode = FadeMode::Out;
		battleCount++;
		counter++;
	}
	endCounter++;

	DrawString( WINDOW_WIDTH / 2 - CenterAdjustment( 8 ), WINDOW_HEIGHT / 2, "Finish!!", COLOR_RED );
}