
#include "Header/GameScene.h"

Player player1( 1, KEY_INPUT_UP, KEY_INPUT_RIGHT, KEY_INPUT_LEFT, KEY_INPUT_DOWN, KEY_INPUT_Z, KEY_INPUT_X, spriteList[0]);
Player player2( 2, KEY_INPUT_W, KEY_INPUT_D, KEY_INPUT_A, KEY_INPUT_S, KEY_INPUT_C, KEY_INPUT_V, spriteList[0] );
Player playerList[PLAYER_MAX] {
	player1,
	player2
};

GameScene::GameScene() {

}

GameScene::~GameScene() {

}

void GameScene::Execute() {

	Control();
	Draw();
}

void GameScene::Control() {

	for ( int i = 0; i < PLAYER_MAX; i++ ){
		playerList[i].Move();
		playerList[i].Shoot();
		playerList[i].Invincible();
		HitManager( &playerList[i] );
	}


	if ( fadeMode != FadeMode::None ) return;

	if ( CheckHitKey( KEY_INPUT_2 ) ) {
		fadeMode = FadeMode::Out;
	}
}

void GameScene::Draw() {

	for( int i = 0; i < PLAYER_MAX; i++ ){
		playerList[i].Draw();
	}

	DrawString( 10, 10, "OnPlay", COLOR_RED );
	DrawString( 10, 30, "Press 2 to Result Scene", COLOR_RED );

	SceneFade( SceneList::Result, 255 / 120, 255 / 60, COLOR_WHITE, COLOR_BLUE, 30 );
}

void GameScene::HitManager( Player* target ){

	for( int playerNum = 0; playerNum < PLAYER_MAX; playerNum++ ){
		for( int bulletNum = 0; bulletNum < BULLET_MAX; bulletNum++ ){
			// 例外は弾く
			if( playerList[playerNum].GetBulletData( bulletNum ) != nullptr &&
				target->GetPlayerNumber() != playerList[playerNum].GetPlayerNumber() &&
				target->GetAlive() == true ){
				// ----------------------------------当たり判定---------------------------------
				if ( Collision( target->GetPosX(),
					( target->GetPosX() + PLAYER_SPRITE_WIDTH ),
					target->GetPosY(),
					( target->GetPosY() + PLAYER_SPRITE_HEIGHT ),
					playerList[playerNum].GetBulletData( bulletNum )->GetPosX() + BULLET_RADIUS,
					playerList[playerNum].GetBulletData( bulletNum )->GetPosY() + BULLET_RADIUS,
					BULLET_RADIUS ) == true ) {
					//--------------------------------------------------------------------------
					playerList[playerNum].DeleteBullet( bulletNum );
					target->DeathProcessing();
					playerList[playerNum].AddScore( 1 );
				}
			}
		}
	}
}

bool GameScene::Collision( int l, int r, int t, int b, int x, int y, int radius ) {
	if( l - radius > x || r + radius < x || t - radius > y || b + radius < y ) {
		return false;
	}
	if( l > x && t > y && !( ( l - x ) * ( l - x ) + ( t - y ) * ( t - y ) < radius * radius ) ) {
		return false;
	}
	if( r < x && t > y && !( ( r - x ) * ( r - x ) + ( t - y ) * ( t - y ) < radius * radius ) ) {
		return false;
	}
	if( l > x && b < y && !( ( l - x ) * ( l - x ) + ( b - y ) * ( b - y ) < radius * radius ) ) {
		return false;
	}
	if( r < x && b < y && !( ( r - x ) * ( r - x ) + ( b - y ) * ( b - y ) < radius * radius ) ) {
		return false;
	}

	return true;
}
