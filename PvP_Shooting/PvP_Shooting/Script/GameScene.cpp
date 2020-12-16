
#include "Header/GameScene.h"
#include "Header/Common.h"
#include "Header/ObjectBase.h"
#include "Header/Player.h"

#include "Header/Stone.h"
#include "Header/Flag.h"
#include "Header/Tree.h"
#include "Header/Explosion.h"
#include "Header/Box.h"
#include "Header/Tunnel.h"

int GameScene::counter = 0;
int GameScene::startCounter = 0;
int GameScene::endCounter = 0;
bool GameScene::isOperatable = false;
ObjectBase* GameScene::objectVault[OBJECT_MAX];

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

	Stone* obj = new Stone( 500, 500 );
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
		SceneBase::playerList[i]->Invincible();
		HitManager( SceneBase::playerList[i] );
	}

	for( int obj = 0; obj < OBJECT_MAX; obj++ ){
		if( objectVault[obj] != nullptr ){
			objectVault[obj]->Control();
		}
	}
}

void GameScene::Draw() {

	SortObjectVault();
	for( int obj = 0; obj < OBJECT_MAX; obj++ ){
		if( objectVault[obj] != nullptr ){
			objectVault[obj]->Draw();
		}
	}

	DrawString( 10, 10, "OnPlay", COLOR_RED );

	DrawFormatString( playerList[0]->GetPosX(), playerList[0]->GetPosY() - 40, COLOR_RED, "SCORE : %d", playerList[0]->GetScore( battleCount + 1 ) );
	DrawFormatString( playerList[1]->GetPosX(), playerList[1]->GetPosY() - 40, COLOR_BLUE, "SCORE : %d", playerList[1]->GetScore( battleCount + 1 ) );

	if( battleCount >= 3 )SceneFade( SceneList::Result, 255, 255 / 60, COLOR_BLACK, COLOR_BLUE );
	else SceneFade( SceneList::Setting, 255, 255 / 60, COLOR_BLACK, COLOR_GREEN );
}

void GameScene::HitManager( Player* target ){

	for( int playerNum = 0; playerNum < PLAYER_MAX; playerNum++ ){
		playerList[playerNum]->Hit();
		for( int bulletNum = 0; bulletNum < BULLET_MAX; bulletNum++ ){
			// 例外は弾く
			if( playerList[playerNum]->GetBulletData( bulletNum ) != nullptr &&
				target->GetPlayerNumber() != playerList[playerNum]->GetPlayerNumber() &&
				target->GetAlive() == true ){
				if( target->GetPlayerNumber() == 1 ) {
					// ------------------信長とナポレオンの弾の当たり判定--------------------
					if( Collision( ( target->GetPosX() - PLAYER_HITBOX_WIDTH / 2 ),
						( target->GetPosX() + PLAYER_HITBOX_WIDTH / 2 ),
						( target->GetPosY() - PLAYER_HITBOX_HEIGHT / 2 ),
						( target->GetPosY() + PLAYER_HITBOX_HEIGHT / 2 ),
						playerList[playerNum]->GetBulletData( bulletNum )->GetPosX(),
						playerList[playerNum]->GetBulletData( bulletNum )->GetPosY(),
						BULLET_RADIUS ) == true ) {
						//-------------------------------------------------------------------
						playerList[playerNum]->DeleteBullet( bulletNum );
						target->DeathProcessing();
						playerList[playerNum]->AddScore( 1, SceneBase::battleCount + 1 );
					}
				}
				else {
					switch( playerList[playerNum]->GetBulletData( bulletNum )->GetDirection() ) {
					case Direction::Up:
					case Direction::Down:
					case Direction::UpperLeft:
					case Direction::UpperRight:
					case Direction::LowerLeft:
					case Direction::LowerRight:
						// --------------------ナポレオンと信長の弾(上下と斜め)の当たり判定---------------------------------------------------------------------------------------
						if( ( target->GetPosX() + PLAYER_HITBOX_WIDTH / 2 ) > ( playerList[playerNum]->GetBulletData( bulletNum )->GetPosX() - BULLET_VERTICAL_WIDTH / 2 ) &&
							( target->GetPosX() - PLAYER_HITBOX_WIDTH / 2 ) < ( playerList[playerNum]->GetBulletData( bulletNum )->GetPosX() + BULLET_VERTICAL_WIDTH / 2 ) &&
							( target->GetPosY() + PLAYER_HITBOX_HEIGHT / 2 ) > ( playerList[playerNum]->GetBulletData( bulletNum )->GetPosY() - BULLET_VERTICAL_HEIGHT / 2 ) &&
							( target->GetPosY() - PLAYER_HITBOX_HEIGHT / 2 ) < ( playerList[playerNum]->GetBulletData( bulletNum )->GetPosY() + BULLET_VERTICAL_HEIGHT / 2 ) ) {
							//----------------------------------------------------------------------------------------------------------------------------------------------------
							playerList[playerNum]->DeleteBullet( bulletNum );
							target->DeathProcessing();
							playerList[playerNum]->AddScore( 1, SceneBase::battleCount + 1 );
						}
						break;
					case Direction::Right:
					case Direction::Left:
						// --------------------ナポレオンと信長の弾(左右)の当たり判定-----------------------------------------------------------------------------------------------
						if( ( target->GetPosX() + PLAYER_HITBOX_WIDTH / 2 ) > ( playerList[playerNum]->GetBulletData( bulletNum )->GetPosX() - BULLET_HORIZONTAL_WIDTH / 2 ) &&
							( target->GetPosX() - PLAYER_HITBOX_WIDTH / 2 ) < ( playerList[playerNum]->GetBulletData( bulletNum )->GetPosX() + BULLET_HORIZONTAL_WIDTH / 2 ) &&
							( target->GetPosY() + PLAYER_HITBOX_HEIGHT / 2 ) > ( playerList[playerNum]->GetBulletData( bulletNum )->GetPosY() - BULLET_HORIZONTAL_HEIGHT / 2 ) &&
							( target->GetPosY() - PLAYER_HITBOX_HEIGHT / 2 ) < ( playerList[playerNum]->GetBulletData( bulletNum )->GetPosY() + BULLET_HORIZONTAL_HEIGHT / 2 ) ) {
							//------------------------------------------------------------------------------------------------------------------------------------------------------
							playerList[playerNum]->DeleteBullet( bulletNum );
							target->DeathProcessing();
							playerList[playerNum]->AddScore( 1, SceneBase::battleCount + 1 );
						}
						break;
					}
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

void GameScene::GameManager(){

	isOperatable = false;

	if( counter == 0 ){ Start(); return; }
	if( counter == FRAME_RATE * PLAY_TIME ){ End(); return; }

	counter++;
	isOperatable = true;

	DrawFormatString( WINDOW_WIDTH / 2 - CenterAdjustment( 3 ), 100, COLOR_GREEN, "%2d", 60 - counter / 60 );
}

void GameScene::Start(){

	static LPCTSTR countDownText = "   3   ";

	switch( startCounter ){
	case 0: countDownText = "   3   ";	break;
	case FRAME_RATE:countDownText = "   2   "; break;
	case FRAME_RATE * 2:countDownText = "   1   "; break;
	case FRAME_RATE * 3:countDownText = "Start!!"; break;
	case FRAME_RATE * 4:counter++; break;
	}

	startCounter++;

	DrawString( WINDOW_WIDTH / 2 - CenterAdjustment( 7 ), WINDOW_HEIGHT / 2, countDownText, COLOR_RED );

}

void GameScene::End(){

	if( endCounter >= FRAME_RATE ){
		fadeMode = FadeMode::Out;
		battleCount++;
		counter++;
	}
	endCounter++;

	DrawString( WINDOW_WIDTH / 2 - CenterAdjustment( 8 ), WINDOW_HEIGHT / 2, "Finish!!", COLOR_RED );
}

int GameScene::EntryObject( ObjectBase* object ){
	for( int i = 0; i < OBJECT_MAX; i++ ){
		if( objectVault[i] == nullptr ){
			objectVault[i] = object;
			return i;
		}
	}

	return -1;
}

void GameScene::SortObjectVault(){
	for( int obj = 0; obj < OBJECT_MAX - 1; obj++ ){
		for( int i = obj + 1; i < OBJECT_MAX; i++ ){
			if( objectVault[obj] == nullptr ) break;

			if( objectVault[i] != nullptr ){
				if( objectVault[obj]->GetCenterY() > objectVault[i]->GetCenterY() ){
					ObjectBase* temp = objectVault[obj];
					objectVault[obj] = objectVault[i];
					objectVault[i] = temp;
				}
			}
		}
	}
}

ObjectBase* GameScene::GetObjectData( int arrayNum ){
	return objectVault[arrayNum];
}

void GameScene::ReleaseObject(){
	for( int i = 0; i < OBJECT_MAX; i++ ){
		delete objectVault[i];
		objectVault[i] = nullptr;
	}
}

void GameScene::ReleaseObject( int arrayNum ){
	delete objectVault[arrayNum];
	objectVault[arrayNum] = nullptr;
}
