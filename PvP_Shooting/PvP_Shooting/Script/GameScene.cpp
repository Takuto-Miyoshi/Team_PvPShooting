
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

#define USE_CONTROLLER

int GameScene::counter = 0;
int GameScene::startCounter = 0;
int GameScene::introHandle = 0;
int GameScene::endCounter = 0;
bool GameScene::isOperatable = false;
ObjectBase* GameScene::objectVault[OBJECT_MAX];
int GameScene::backGroundHandle = 0;
bool GameScene::isPaused = false;

GameScene::GameScene() {
	counter = 0;
	startCounter = 0;
	endCounter = 0;
	for( int p = 0; p < PLAYER_MAX; p++ ){
		for( int b = 0; b < BULLET_MAX; b++ ){
			playerList[p]->DeleteBullet( b );
		}
		playerList[p]->LoadSoundData();
	}

	StageSetUp();

	pauseSEHandle = LoadSoundMem( Sounds::SE::pause );
	battleStartSEHandle = LoadSoundMem( Sounds::SE::battleStart );
	battleEndSEHandle = LoadSoundMem( Sounds::SE::battleEnd );

	SceneBase::BGMHandle = LoadSoundMem( Sounds::BGM::battle );
}

GameScene::~GameScene() {

}

void GameScene::Execute() {

	if( GameManager() ) Pause();

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

	DrawGraph( 0, 0, backGroundHandle, false );

	PointGauge();
	Clock();

	SortObjectVault();

	for( int obj = 0; obj < OBJECT_MAX; obj++ ){
		if( objectVault[obj] != nullptr ){
			objectVault[obj]->Draw();
		}
	}

	DrawFormatString( playerList[0]->GetPosX(), playerList[0]->GetPosY() - 40, COLOR_RED, "SCORE : %d", playerList[0]->GetScore( battleCount + 1 ) );
	DrawFormatString( playerList[1]->GetPosX(), playerList[1]->GetPosY() - 40, COLOR_BLUE, "SCORE : %d", playerList[1]->GetScore( battleCount + 1 ) );

	if( counter == 0 ) DrawGraph( 0, WINDOW_HEIGHT / 2 - 192, introHandle, false );
	else if( counter >= FRAME_RATE * PLAY_TIME ) LoadGraphScreen( 0, WINDOW_HEIGHT / 2 - 192, Sprite::UI::end, false );
	else if( isPaused == true ) LoadGraphScreen( 0, WINDOW_HEIGHT / 2 - 192, Sprite::UI::pause, false );

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

bool GameScene::GameManager(){

	isOperatable = false;

	if( counter == 0 ){ Start(); return false; }
	if( counter == FRAME_RATE * PLAY_TIME ){ End(); return false; }

	if( isPaused == false ) counter++;
	isOperatable = true;

	return true;
}

void GameScene::Start(){

	switch( startCounter ){
	case 0: introHandle = LoadGraph( Sprite::UI::ready ); break;
	case FRAME_RATE:
		introHandle = LoadGraph( Sprite::UI::start );
		PlaySoundMem( battleStartSEHandle, DX_PLAYTYPE_BACK );
		break;
	case FRAME_RATE + FRAME_RATE / 2: counter++; break;
	}

	startCounter++;
}

void GameScene::End(){

	if( endCounter == 0 ){
		PlaySoundMem( battleEndSEHandle, DX_PLAYTYPE_BACK );
	}
	else if( endCounter >= FRAME_RATE ){
		fadeMode = FadeMode::Out;
		battleCount++;
		counter++;
	}
	endCounter++;
}

void GameScene::SortObjectVault(){
	for( int obj = 0; obj < OBJECT_MAX - 1; obj++ ){
		for( int i = obj + 1; i < OBJECT_MAX; i++ ){
			if( objectVault[obj] == nullptr ) break;

			if( objectVault[i] != nullptr && objectVault[obj] != nullptr ){
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

void GameScene::StageSetUp(){

	switch( SceneBase::GetStage().number )
	{
	case 1:
		objectVault[0] = new Flag( 225, 140 );
		objectVault[1] = new Stone( 730, 260 );
		objectVault[2] = new Flag( 1466, 140 );
		objectVault[3] = new Tree( 417, 383 );
		objectVault[4] = new Stone( 994, 603 );
		objectVault[5] = new Tree( 1352, 476 );
		objectVault[6] = new Stone( 726, 860 );
		backGroundHandle = LoadGraph( Sprite::BackGround::stage1 );
		break;
	default:
		objectVault[0] = new Tunnel();
		objectVault[1] = new Box( 397, 348 );
		objectVault[2] = new Box( 1249, 395 );
		objectVault[3] = new Box( 1441, 395 );
		objectVault[4] = new Box( 662, 859 );
		objectVault[5] = new Box( 1441, 859 );
		objectVault[6] = nullptr;
		backGroundHandle = LoadGraph( Sprite::BackGround::stage2 );
		break;
	}

	objectVault[7] = playerList[0];
	objectVault[8] = playerList[1];

	playerList[0]->SetPosX( 70 );
	playerList[0]->SetPosY( 820 );
	playerList[1]->SetPosX( 1687 );
	playerList[1]->SetPosY( 83 );
}

void GameScene::Pause(){

#ifdef USE_CONTROLLER
	if( GetPadStatus( player1->GetPlayerNumber(), PAD_INPUT_8 ) == InputState::Pressed ) {
#else
	if( GetKeyStatus( KEY_INPUT_RETURN ) == InputState::Pressed ) {
#endif
		PlaySoundMem( pauseSEHandle, DX_PLAYTYPE_BACK );
		isPaused = !isPaused;
	}

	isOperatable = ( isPaused == true ) ? false : true;
}

void GameScene::PointGauge(){

	int x = -WINDOW_WIDTH / 2;

	x += SceneBase::playerList[0]->GetScore( -1 ) * 96;
	x -= SceneBase::playerList[1]->GetScore( -1 ) * 96;

	if( x < -WINDOW_WIDTH + 96 ){
		x = -WINDOW_WIDTH + 96;
	}
	else if( x > -96 ){
		x = -96;
	}

	// 描画
	LoadGraphScreen( x, 0, Sprite::UI::pointGauge, false );
}

void GameScene::Clock(){

	static int firstHandle = LoadGraph( Sprite::UI::clockNumber[0] );
	static int tenthHandle = LoadGraph( Sprite::UI::clockNumber[6] );

	int time = PLAY_TIME - counter / FRAME_RATE;

	switch( time )
	{
	case 59: tenthHandle = LoadGraph( Sprite::UI::clockNumber[5] ); break;
	case 49: tenthHandle = LoadGraph( Sprite::UI::clockNumber[4] ); break;
	case 39: tenthHandle = LoadGraph( Sprite::UI::clockNumber[3] ); break;
	case 29: tenthHandle = LoadGraph( Sprite::UI::clockNumber[2] ); break;
	case 19: tenthHandle = LoadGraph( Sprite::UI::clockNumber[1] ); break;
	case 9:  tenthHandle = LoadGraph( Sprite::UI::clockNumber[0] ); break;
	}

	while( time >= 10 ){
		time -= 10;
	}

	switch( time )
	{
	case 0: firstHandle = LoadGraph( Sprite::UI::clockNumber[0] ); break;
	case 1: firstHandle = LoadGraph( Sprite::UI::clockNumber[1] ); break;
	case 2: firstHandle = LoadGraph( Sprite::UI::clockNumber[2] ); break;
	case 3: firstHandle = LoadGraph( Sprite::UI::clockNumber[3] ); break;
	case 4: firstHandle = LoadGraph( Sprite::UI::clockNumber[4] ); break;
	case 5: firstHandle = LoadGraph( Sprite::UI::clockNumber[5] ); break;
	case 6: firstHandle = LoadGraph( Sprite::UI::clockNumber[6] ); break;
	case 7: firstHandle = LoadGraph( Sprite::UI::clockNumber[7] ); break;
	case 8: firstHandle = LoadGraph( Sprite::UI::clockNumber[8] ); break;
	case 9: firstHandle = LoadGraph( Sprite::UI::clockNumber[9] ); break;
	}

	LoadGraphScreen( 854, 17, Sprite::UI::clockFrame, true );
	DrawGraph( 898, 66, tenthHandle, true );
	DrawGraph( 961, 67, firstHandle, true );
}
