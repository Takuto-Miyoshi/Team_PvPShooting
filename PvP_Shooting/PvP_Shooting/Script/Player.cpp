
#include "Header/Player.h"

//#define USE_CONTROLLER

Player::Player( bool isUsePad, int padNumber, int playerNum, int keyUp, int keyRight, int keyLeft, int keyDown, int keyShot, int keyBomb, int keyUlt, LPCTSTR spritePath ){
	playerNumber = playerNum;
	isAlive = true;
	invincibleCount = 0;

	posX = 100;
	posY = 100;
	speed = PLAYER_SPEED;
	shootingCoolTime = 0;
	chargeCount = 0;
	for( int i = 0; i < ROUND_MAX; i++ )score[i] = 0;

	usePad = isUsePad;
	padNum = padNumber;
	upMovingKey = keyUp;
	rightMovingKey = keyRight;
	leftMovingKey = keyLeft;
	downMovingKey = keyDown;
	shotKey = keyShot;
	bombKey = keyBomb;
	ultKey = keyUlt;
	spriteFolderPath = spritePath;
	dir = Direction::Down;

	for( int i = 0; i < BULLET_MAX; i++ )bullets[i] = nullptr;
}

Player::~Player() {

}

void Player::Move() {

#ifdef USE_CONTROLLER
	if( GetPadStatus( playerNumber, upMovingKey ) == InputState::Pressing ){
		posY -= speed;
		dir = Direction::Up;
	}
	else if( GetPadStatus( playerNumber, downMovingKey ) == InputState::Pressing ){
		posY += speed;
		dir = Direction::Down;
	}

	if( GetPadStatus( playerNumber, rightMovingKey ) == InputState::Pressing ){
		posX += speed;
		dir = Direction::Right;
	}
	else if( GetPadStatus( playerNumber, leftMovingKey ) == InputState::Pressing ){
		posX -= speed;
		dir = Direction::Left;
	}

#else
	if( GetKeyStatus( upMovingKey ) == InputState::Pressing ) {
		posY -= speed;
		dir = Direction::Up;
	}
	else if( GetKeyStatus( downMovingKey ) == InputState::Pressing ) {
		posY += speed;
		dir = Direction::Down;
	}

	if( GetKeyStatus( rightMovingKey ) == InputState::Pressing ) {
		posX += speed;
		dir = Direction::Right;
	}
	else if( GetKeyStatus( leftMovingKey ) == InputState::Pressing ) {
		posX -= speed;
		dir = Direction::Left;
	}

	if ( GetKeyStatus( upMovingKey ) == InputState::Pressing ) {
		if ( GetKeyStatus( rightMovingKey ) == InputState::Pressing ) {
			dir = Direction::UpperRight;
		}
		else if ( GetKeyStatus( leftMovingKey ) == InputState::Pressing ) {		
			dir = Direction::UpperLeft;
		}
	}
	else if ( GetKeyStatus( downMovingKey ) == InputState::Pressing ) {
		if ( GetKeyStatus( rightMovingKey ) == InputState::Pressing ) {
			dir = Direction::LowerRight;
		}
		else if ( GetKeyStatus( leftMovingKey ) == InputState::Pressing ) {
			dir = Direction::LowerLeft;
		}
	}
#endif
}

void Player::Draw() {

	if ( isAlive == true ) {
		LoadGraphScreen( posX, posY, spriteFolderPath, false );
		for ( int i = 0; i < BULLET_MAX; i++ ) {
			if ( bullets[i] != nullptr ) bullets[i]->Draw();
		}
	}
	else {
		if( invincibleCount >= 12 && invincibleCount < 24 || invincibleCount >= 36 && invincibleCount < 48 ) {
			LoadGraphScreen( posX, posY, spriteFolderPath, false );
		}
	}
}

void Player::Shoot() {

	if( isAlive == false ) return;

	shootingCoolTime++;

	// 画面外ならdelete
	for( int i = 0; i < BULLET_MAX; i++ ){
		if( bullets[i] != nullptr ){
			if( IsOutsideWindow( bullets[i]->GetPosX(), bullets[i]->GetPosY() ) == true )DeleteBullet( i );
		}
	}

	// 射撃キーが押されたら弾を生成
	if( shootingCoolTime > SHOOTING_COOL_TIME ){
#ifdef USE_CONTROLLER
		if( GetPadStatus( playerNumber, shotKey ) == InputState::Pressing ){
#else
		if( GetKeyStatus( shotKey ) == InputState::Pressing ){
#endif
			chargeCount++;
		}
#ifdef USE_CONTROLLER
		else if( GetPadStatus( playerNumber, shotKey ) == InputState::Released ){
#else
		else if( GetKeyStatus( shotKey ) == InputState::Released ){
#endif
			bool tempCharge = false;
			if( chargeCount >= CHARGE_COUNT ){
				tempCharge = true;
			}

			for( int i = 0; i < BULLET_MAX; i++ ){
				if( bullets[i] == nullptr ){
					bullets[i] = new Bullet( posX + PLAYER_WIDTH / 2 - BULLET_WIDTH / 2,
						posY + PLAYER_HEIGHT / 2 - BULLET_HEIGHT / 2, dir, spriteList[1], tempCharge );
					shootingCoolTime = 0;
					chargeCount = 0;
					break;
				}
			}
		}
	}

	for( int i = 0; i < BULLET_MAX; i++ ){
		if( bullets[i] != nullptr ) bullets[i]->Move();
	}
}

void Player::Bomb(){

}

void Player::Hit(){


}

void Player::Invincible(){

	if( isAlive == false ){
		invincibleCount++;
		if( invincibleCount > INVINCIBLE_TIME ){
			invincibleCount = 0;
			isAlive = true;
		}
	}
}

int Player::GetPlayerNumber(){
	return playerNumber;
}

int Player::GetPosX()const{
	return posX;
}

int Player::GetPosY()const{
	return posY;
}

void Player::SetPosX( int x ){
	posX = x;
}

void Player::SetPosY( int y ){
	posY = y;
}

Bullet* Player::GetBulletData( int arrayNum )const {
	return bullets[arrayNum];
}

bool Player::GetAlive()const {
	return isAlive;
}

void Player::SetAlive( bool state ){
	isAlive = state;
}

int Player::GetScore( int round )const{

	if( round == -1 )return ( score[0] + score[1] + score[2] );

	if( round <= 0 || round > ROUND_MAX )return 0;
	return score[round - 1];
}

void Player::ResetScore(){

	for( int i = 0; i < ROUND_MAX; i++ )score[i] = 0;
}

void Player::AddScore( int value, int round ){
	if( round <= 0 || round > ROUND_MAX )return;
	score[round - 1] += ( value );
}

void Player::DeleteBullet( int arrayNum ){
	if( bullets[arrayNum] == nullptr ) return;
	delete bullets[arrayNum];
	bullets[arrayNum] = nullptr;
}

void Player::DeathProcessing(){
	isAlive = false;
	for( int i = 0; i < BULLET_MAX; i++ ){
		DeleteBullet( i );
	}
}
