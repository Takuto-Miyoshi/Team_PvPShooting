
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
#include "Header/Car.h"

#define USE_CONTROLLER

int GameScene::counter = 0;
int GameScene::startCounter = 0;
int GameScene::readyHandle = 0;
int GameScene::introHandle = 0;
int GameScene::finishHandle = 0;
int GameScene::pauseHandle = 0;
int GameScene::endCounter = 0;
bool GameScene::isOperatable = false;
ObjectBase* GameScene::objectVault[OBJECT_MAX];
int GameScene::backGroundHandle = 0;
bool GameScene::isPaused = false;
int GameScene::pointGaugeHandle = 0;
int GameScene::clockFrameHandle = 0;

int GameScene::USlashHandle[2] = {};
int GameScene::ULSlashHandle[2] = {};
int GameScene::URSlashHandle[2] = {};
int GameScene::LSlashHandle[2] = {};
int GameScene::RSlashHandle[2] = {};
int GameScene::DSlashHandle[2] = {};
int GameScene::DLSlashHandle[2] = {};
int GameScene::DRSlashHandle[2] = {};

int GameScene::UBulletHandle[2] = {};
int GameScene::ULBulletHandle[2] = {};
int GameScene::URBulletHandle[2] = {};
int GameScene::LBulletHandle[2] = {};
int GameScene::RBulletHandle[2] = {};
int GameScene::DBulletHandle[2] = {};
int GameScene::DLBulletHandle[2] = {};
int GameScene::DRBulletHandle[2] = {};

int GameScene::nobunagaChargeHandle[Sprite::chargeFrame] = {};
int GameScene::napoleonChargeHandle[Sprite::chargeFrame] = {};

int GameScene::UNobunagaAttackHandle[Sprite::attackFrame] = {};
int GameScene::LNobunagaAttackHandle[Sprite::attackFrame] = {};
int GameScene::RNobunagaAttackHandle[Sprite::attackFrame] = {};
int GameScene::DNobunagaAttackHandle[Sprite::attackFrame] = {};

int GameScene::UNapoleonAttackHandle[Sprite::attackFrame] = {};
int GameScene::LNapoleonAttackHandle[Sprite::attackFrame] = {};
int GameScene::RNapoleonAttackHandle[Sprite::attackFrame] = {};
int GameScene::DNapoleonAttackHandle[Sprite::attackFrame] = {};

int GameScene::UNobunagaWalkHandle[Sprite::walkFrame] = {};
int GameScene::LNobunagaWalkHandle[Sprite::walkFrame] = {};
int GameScene::RNobunagaWalkHandle[Sprite::walkFrame] = {};
int GameScene::DNobunagaWalkHandle[Sprite::walkFrame] = {};

int GameScene::UNapoleonWalkHandle[Sprite::walkFrame] = {};
int GameScene::LNapoleonWalkHandle[Sprite::walkFrame] = {};
int GameScene::RNapoleonWalkHandle[Sprite::walkFrame] = {};
int GameScene::DNapoleonWalkHandle[Sprite::walkFrame] = {};

int GameScene::UNobunagaWaitHandle[Sprite::waitFrame] = {};
int GameScene::LNobunagaWaitHandle[Sprite::waitFrame] = {};
int GameScene::RNobunagaWaitHandle[Sprite::waitFrame] = {};
int GameScene::DNobunagaWaitHandle[Sprite::waitFrame] = {};

int GameScene::UNapoleonWaitHandle[Sprite::waitFrame] = {};
int GameScene::LNapoleonWaitHandle[Sprite::waitFrame] = {};
int GameScene::RNapoleonWaitHandle[Sprite::waitFrame] = {};
int GameScene::DNapoleonWaitHandle[Sprite::waitFrame] = {};

int GameScene::treeHandle[Sprite::treeFrame] = {};
int GameScene::flagHandle[Sprite::flagFrame] = {};
int GameScene::stoneHandle = 0;
int GameScene::boxHandle[Sprite::boxFrame] = {};
int GameScene::explosionHandle[Sprite::explosionFrame] = {};
int GameScene::tunnelHandle[Sprite::tunnelFrame] = {};
int GameScene::carHandle[Sprite::carFrame] = {};

int GameScene::hitEffectHandle[Sprite::hitFrame] = {};

int GameScene::carSEHandle = 0;

int GameScene::clockNumber[10] = {};

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

	summonCounter = -FRAME_RATE * 2;

	isSummoned = false;

	StageSetUp();

	playerList[0]->Reset();
	playerList[1]->Reset();

	pauseSEHandle = LoadSoundMem( Sounds::SE::pause );
	battleStartSEHandle = LoadSoundMem( Sounds::SE::battleStart );
	battleEndSEHandle = LoadSoundMem( Sounds::SE::battleEnd );
	carSEHandle = LoadSoundMem( Sounds::SE::carMoved );

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

	if( SceneBase::GetStage().number == 2 ) CarExec();

	for( int obj = 0; obj < OBJECT_MAX; obj++ ){
		if( objectVault[obj] != nullptr ){
			objectVault[obj]->Control();

			if( objectVault[obj]->GetTag() == Tag::Car ){
				if( objectVault[obj]->GetPosX() < 0 - CAR_WIDTH * 2 || objectVault[obj]->GetPosX() > WINDOW_WIDTH + CAR_WIDTH ){
					StopSoundMem( carSEHandle );
					delete objectVault[obj];
					objectVault[obj] = nullptr;
					isSummoned = false;
				}
			}
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

	if( counter == 0 && startCounter >= FRAME_RATE ) DrawGraph( 0, WINDOW_HEIGHT / 2 - 192, introHandle, false );
	else if( counter == 0 ) DrawGraph( 0, WINDOW_HEIGHT / 2 - 192, readyHandle, false );
	else if( counter >= FRAME_RATE * PLAY_TIME ) DrawGraph( 0, WINDOW_HEIGHT / 2 - 192, finishHandle, false );
	else if( isPaused == true ) DrawGraph( 0, WINDOW_HEIGHT / 2 - 192, pauseHandle, false );

	if( battleCount >= 3 )SceneFade( SceneList::Result, 255, 255 / 60, COLOR_BLACK, COLOR_BLACK );
	else SceneFade( SceneList::Setting, 255, 255 / 60, COLOR_BLACK, COLOR_BLACK );
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
	case FRAME_RATE:
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
		objectVault[7] = nullptr;
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
		objectVault[7] = nullptr;
		backGroundHandle = LoadGraph( Sprite::BackGround::stage2 );
		break;
	}

	objectVault[8] = playerList[0];
	objectVault[9] = playerList[1];

	playerList[0]->SetPosX( 70 );
	playerList[0]->SetPosY( 820 );
	playerList[1]->SetPosX( 1687 );
	playerList[1]->SetPosY( 83 );

	readyHandle = LoadGraph( Sprite::UI::ready );
	introHandle = LoadGraph( Sprite::UI::start );
	finishHandle = LoadGraph( Sprite::UI::end );
	pauseHandle = LoadGraph( Sprite::UI::pause );

	for( int i = 0; i < 2; i++ ){
		USlashHandle[i] = LoadGraph( Sprite::Nobunaga::bulletUp[i] );
		ULSlashHandle[i] = LoadGraph( Sprite::Nobunaga::bulletUpperLeft[i] );
		URSlashHandle[i] = LoadGraph( Sprite::Nobunaga::bulletUpperRight[i] );
		LSlashHandle[i] = LoadGraph( Sprite::Nobunaga::bulletLeft[i] );
		RSlashHandle[i] = LoadGraph( Sprite::Nobunaga::bulletRight[i] );
		DSlashHandle[i] = LoadGraph( Sprite::Nobunaga::bulletDown[i] );
		DLSlashHandle[i] = LoadGraph( Sprite::Nobunaga::bulletLowerLeft[i] );
		DRSlashHandle[i] = LoadGraph( Sprite::Nobunaga::bulletLowerRight[i] );

		UBulletHandle[i] = LoadGraph( Sprite::Napoleon::bulletUp[i] );
		ULBulletHandle[i] = LoadGraph( Sprite::Napoleon::bulletUpperLeft[i] );
		URBulletHandle[i] = LoadGraph( Sprite::Napoleon::bulletUpperRight[i] );
		LBulletHandle[i] = LoadGraph( Sprite::Napoleon::bulletLeft[i] );
		RBulletHandle[i] = LoadGraph( Sprite::Napoleon::bulletRight[i] );
		DBulletHandle[i] = LoadGraph( Sprite::Napoleon::bulletDown[i] );
		DLBulletHandle[i] = LoadGraph( Sprite::Napoleon::bulletLowerLeft[i] );
		DRBulletHandle[i] = LoadGraph( Sprite::Napoleon::bulletLowerRight[i] );
	}

	for( int i = 0; i < Sprite::chargeFrame; i++ ){
		nobunagaChargeHandle[i] = LoadGraph( Sprite::Nobunaga::chargeEffect[i] );
		napoleonChargeHandle[i] = LoadGraph( Sprite::Napoleon::chargeEffect[i] );
	}

	for( int i = 0; i < Sprite::attackFrame; i++ ){
		UNobunagaAttackHandle[i] = LoadGraph( Sprite::Nobunaga::attackUp[i] );
		LNobunagaAttackHandle[i] = LoadGraph( Sprite::Nobunaga::attackLeft[i] );
		RNobunagaAttackHandle[i] = LoadGraph( Sprite::Nobunaga::attackRight[i] );
		DNobunagaAttackHandle[i] = LoadGraph( Sprite::Nobunaga::attackDown[i] );

		UNapoleonAttackHandle[i] = LoadGraph( Sprite::Napoleon::attackUp[i] );
		LNapoleonAttackHandle[i] = LoadGraph( Sprite::Napoleon::attackLeft[i] );
		RNapoleonAttackHandle[i] = LoadGraph( Sprite::Napoleon::attackRight[i] );
		DNapoleonAttackHandle[i] = LoadGraph( Sprite::Napoleon::attackDown[i] );
	}

	for( int i = 0; i < Sprite::walkFrame; i++ ){

		UNobunagaWalkHandle[i] = LoadGraph( Sprite::Nobunaga::walkUp[i] );
		LNobunagaWalkHandle[i] = LoadGraph( Sprite::Nobunaga::walkLeft[i] );
		RNobunagaWalkHandle[i] = LoadGraph( Sprite::Nobunaga::walkRight[i] );
		DNobunagaWalkHandle[i] = LoadGraph( Sprite::Nobunaga::walkDown[i] );

		UNapoleonWalkHandle[i] = LoadGraph( Sprite::Napoleon::walkUp[i] );
		LNapoleonWalkHandle[i] = LoadGraph( Sprite::Napoleon::walkLeft[i] );
		RNapoleonWalkHandle[i] = LoadGraph( Sprite::Napoleon::walkRight[i] );
		DNapoleonWalkHandle[i] = LoadGraph( Sprite::Napoleon::walkDown[i] );
	}

	for( int i = 0; i < Sprite::waitFrame; i++ ){
		UNobunagaWaitHandle[i] = LoadGraph( Sprite::Nobunaga::waitUp[i] );
		LNobunagaWaitHandle[i] = LoadGraph( Sprite::Nobunaga::waitLeft[i] );
		RNobunagaWaitHandle[i] = LoadGraph( Sprite::Nobunaga::waitRight[i] );
		DNobunagaWaitHandle[i] = LoadGraph( Sprite::Nobunaga::waitDown[i] );

		UNapoleonWaitHandle[i] = LoadGraph( Sprite::Napoleon::waitUp[i] );
		LNapoleonWaitHandle[i] = LoadGraph( Sprite::Napoleon::waitLeft[i] );
		RNapoleonWaitHandle[i] = LoadGraph( Sprite::Napoleon::waitRight[i] );
		DNapoleonWaitHandle[i] = LoadGraph( Sprite::Napoleon::waitDown[i] );
	}

	for( int i = 0; i < Sprite::treeFrame; i++ ){
		treeHandle[i] = LoadGraph( Sprite::Gimmick::tree[i] );
	}

	for( int i = 0; i < Sprite::flagFrame; i++ ){
		flagHandle[i] = LoadGraph( Sprite::Gimmick::flag[i] );
	}

	stoneHandle = LoadGraph( Sprite::Gimmick::stone );

	for( int i = 0; i < Sprite::boxFrame; i++ ){
		boxHandle[i] = LoadGraph( Sprite::Gimmick::box[i] );
	}

	for( int i = 0; i < Sprite::explosionFrame; i++ ){
		explosionHandle[i] = LoadGraph( Sprite::Gimmick::explosion[i] );
	}

	for( int i = 0; i < Sprite::tunnelFrame; i++ ){
		tunnelHandle[i] = LoadGraph( Sprite::Gimmick::tunnel[i] );
	}

	for( int i = 0; i < Sprite::carFrame; i++ ){
		carHandle[i] = LoadGraph( Sprite::Gimmick::car[i] );
	}

	for( int i = 0; i < Sprite::chargeFrame; i++ ){
		hitEffectHandle[i] = LoadGraph( Sprite::hitEffect[i] );
	}

	pointGaugeHandle = LoadGraph( Sprite::UI::pointGauge );
	clockFrameHandle = LoadGraph( Sprite::UI::clockFrame );

	for( int i = 0; i < 10; i++ ){
		clockNumber[i] = LoadGraph( Sprite::UI::clockNumber[i] );
	}
}

void GameScene::Pause(){

#ifdef USE_CONTROLLER
	if( ( GetPadStatus( player1->GetPlayerNumber(), PAD_INPUT_8 ) == InputState::Pressed ) ||
		( GetPadStatus( player1->GetPlayerNumber(), PAD_INPUT_9 ) == InputState::Pressed ) ||
		( GetPadStatus( player1->GetPlayerNumber(), PAD_INPUT_10 ) == InputState::Pressed ) ){
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
	DrawGraph( x, 0, pointGaugeHandle, false );
}

void GameScene::Clock(){

	static int firstHandle = 0;
	static int tenthHandle = 0;

	int time = PLAY_TIME - counter / FRAME_RATE;
	int tenthNum = 0;

	while( time >= 10 )	{
		time -= 10;
		tenthNum++;
	}

	switch( tenthNum )
	{
	case 0: tenthHandle = clockNumber[0]; break;
	case 1: tenthHandle = clockNumber[1]; break;
	case 2: tenthHandle = clockNumber[2]; break;
	case 3: tenthHandle = clockNumber[3]; break;
	case 4: tenthHandle = clockNumber[4]; break;
	case 5: tenthHandle = clockNumber[5]; break;
	case 6: tenthHandle = clockNumber[6]; break;
	case 7: tenthHandle = clockNumber[7]; break;
	case 8: tenthHandle = clockNumber[8]; break;
	case 9: tenthHandle = clockNumber[9]; break;
	}

	switch( time )
	{
	case 0: firstHandle = clockNumber[0]; break;
	case 1: firstHandle = clockNumber[1]; break;
	case 2: firstHandle = clockNumber[2]; break;
	case 3: firstHandle = clockNumber[3]; break;
	case 4: firstHandle = clockNumber[4]; break;
	case 5: firstHandle = clockNumber[5]; break;
	case 6: firstHandle = clockNumber[6]; break;
	case 7: firstHandle = clockNumber[7]; break;
	case 8: firstHandle = clockNumber[8]; break;
	case 9: firstHandle = clockNumber[9]; break;
	}

	DrawGraph( 854, 17, clockFrameHandle, true );
	DrawGraph( 898, 66, tenthHandle, true );
	DrawGraph( 961, 67, firstHandle, true );
}

int GameScene::GetBulletHandle( int playerNumber, Direction direction, bool isCharged ){

	int tempCharged = ( isCharged == true ) ? 1 : 0;

	switch( direction )
	{
	case Direction::Up:			return ( playerNumber == 1 ) ? USlashHandle[tempCharged] : UBulletHandle[tempCharged];
	case Direction::Right:		return ( playerNumber == 1 ) ? RSlashHandle[tempCharged] : RBulletHandle[tempCharged];
	case Direction::Left:		return ( playerNumber == 1 ) ? LSlashHandle[tempCharged] : LBulletHandle[tempCharged];
	case Direction::Down:		return ( playerNumber == 1 ) ? DSlashHandle[tempCharged] : DBulletHandle[tempCharged];
	case Direction::UpperRight:	return ( playerNumber == 1 ) ? URSlashHandle[tempCharged] : URBulletHandle[tempCharged];
	case Direction::UpperLeft:	return ( playerNumber == 1 ) ? ULSlashHandle[tempCharged] : ULBulletHandle[tempCharged];
	case Direction::LowerRight:	return ( playerNumber == 1 ) ? DRSlashHandle[tempCharged] : DRBulletHandle[tempCharged];
	case Direction::LowerLeft:
	default:					return ( playerNumber == 1 ) ? DLSlashHandle[tempCharged] : DLBulletHandle[tempCharged];

	}
}

int GameScene::GetPlayerHandle( int playerNumber, Direction direction, Motion motion, int spriteNumber ){

	switch( motion )
	{
	case Motion::Attack:
		if( spriteNumber < 0 || spriteNumber >= Sprite::attackFrame ) spriteNumber = 0;

		switch( direction )
		{
		case Direction::UpperLeft:
		case Direction::UpperRight:
		case Direction::Up:		return ( playerNumber == 1 ) ? UNobunagaAttackHandle[spriteNumber] : UNapoleonAttackHandle[spriteNumber];
		case Direction::Right:	return ( playerNumber == 1 ) ? RNobunagaAttackHandle[spriteNumber] : RNapoleonAttackHandle[spriteNumber];
		case Direction::Left:	return ( playerNumber == 1 ) ? LNobunagaAttackHandle[spriteNumber] : LNapoleonAttackHandle[spriteNumber];
		case Direction::LowerLeft:
		case Direction::LowerRight:
		case Direction::Down:
		default:				return ( playerNumber == 1 ) ? DNobunagaAttackHandle[spriteNumber] : DNapoleonAttackHandle[spriteNumber];
		}
	case Motion::Walk:
		if( spriteNumber < 0 || spriteNumber >= Sprite::walkFrame ) spriteNumber = 0;

		switch( direction )
		{
		case Direction::UpperLeft:
		case Direction::UpperRight:
		case Direction::Up:		return ( playerNumber == 1 ) ? UNobunagaWalkHandle[spriteNumber] : UNapoleonWalkHandle[spriteNumber];
		case Direction::Right:	return ( playerNumber == 1 ) ? RNobunagaWalkHandle[spriteNumber] : RNapoleonWalkHandle[spriteNumber];
		case Direction::Left:	return ( playerNumber == 1 ) ? LNobunagaWalkHandle[spriteNumber] : LNapoleonWalkHandle[spriteNumber];
		case Direction::LowerLeft:
		case Direction::LowerRight:
		case Direction::Down:
		default:				return ( playerNumber == 1 ) ? DNobunagaWalkHandle[spriteNumber] : DNapoleonWalkHandle[spriteNumber];
		}
	case Motion::Wait:
	default:
		if( spriteNumber < 0 || spriteNumber >= Sprite::waitFrame ) spriteNumber = 0;

		switch( direction )
		{
		case Direction::UpperLeft:
		case Direction::UpperRight:
		case Direction::Up:		return ( playerNumber == 1 ) ? UNobunagaWaitHandle[spriteNumber] : UNapoleonWaitHandle[spriteNumber];
		case Direction::Right:	return ( playerNumber == 1 ) ? RNobunagaWaitHandle[spriteNumber] : RNapoleonWaitHandle[spriteNumber];
		case Direction::Left:	return ( playerNumber == 1 ) ? LNobunagaWaitHandle[spriteNumber] : LNapoleonWaitHandle[spriteNumber];
		case Direction::LowerLeft:
		case Direction::LowerRight:
		case Direction::Down:
		default:				return ( playerNumber == 1 ) ? DNobunagaWaitHandle[spriteNumber] : DNapoleonWaitHandle[spriteNumber];
		}
	}
}

int GameScene::GetObjectHandle( Tag objectTag, int spriteNumber ){

	switch( objectTag )
	{
	case Tag::Tree:
		if( spriteNumber < 0 || spriteNumber >= Sprite::treeFrame ) spriteNumber = 0;
		return treeHandle[spriteNumber];
	case Tag::Flag:
		if( spriteNumber < 0 || spriteNumber >= Sprite::flagFrame ) spriteNumber = 0;
		return flagHandle[spriteNumber];
	case Tag::Box:
		if( spriteNumber < 0 || spriteNumber >= Sprite::boxFrame ) spriteNumber = 0;
		return boxHandle[spriteNumber];
	case Tag::Car:
		if( spriteNumber < 0 || spriteNumber >= Sprite::carFrame ) spriteNumber = 0;
		return carHandle[spriteNumber];
	case Tag::Tunnel:
		if( spriteNumber < 0 || spriteNumber >= Sprite::tunnelFrame ) spriteNumber = 0;
		return tunnelHandle[spriteNumber];
	case Tag::Explosion:
		if( spriteNumber < 0 || spriteNumber >= Sprite::explosionFrame ) spriteNumber = 0;
		return explosionHandle[spriteNumber];
	default:
	case Tag::Stone:
		return stoneHandle;
	}
}

int GameScene::GetChargeEffectHandle( int playerNumber, int spriteNumber ){

	if( spriteNumber < 0 || spriteNumber >= Sprite::chargeFrame ) spriteNumber = 0;
	return ( playerNumber == 1 ) ? nobunagaChargeHandle[spriteNumber] : napoleonChargeHandle[spriteNumber];
}

int GameScene::GetHitEffectHandle( int spriteNumber ){

	if( spriteNumber < 0 || spriteNumber >= Sprite::hitFrame ) spriteNumber = 0;
	return hitEffectHandle[spriteNumber];
}

void GameScene::CarExec(){

	if( isSummoned == true ) return;

	summonCounter++;

	if( summonCounter >= 180 ){
		if( GetRand( 1 ) == 0 ){

			for( int i = 0; i < OBJECT_MAX; i++ ){
				if( objectVault[i] == nullptr ){
					objectVault[i] = new Car( Direction::Right );
					break;
				}
			}

			for( int i = 0; i < OBJECT_MAX; i++ ){
				if( objectVault[i] == nullptr ){
					objectVault[i] = new Car( Direction::Left );
					break;
				}
			}

			PlaySoundMem( carSEHandle, DX_PLAYTYPE_LOOP );

			summonCounter = 0;
			isSummoned = true;
		}
	}

}


