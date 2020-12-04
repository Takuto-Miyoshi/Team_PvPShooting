
#include "Header/Player.h"

Player::Player( int playerNum, int keyUp, int keyRight, int keyLeft, int keyDown, int keyShot, int keyBomb, LPCTSTR spritePath ) {
	playerNumber = playerNum;
	isAlive = true;
	respawnCount = 0;

	posX = 100;
	posY = 100;
	speed = PLAYER_SPEED;
	shootingCoolTime = 0;
	score = 0;
	chargeCount = 0;

	upMovingKey = keyUp;
	rightMovingKey = keyRight;
	leftMovingKey = keyLeft;
	downMovingKey = keyDown;
	shotKey = keyShot;
	bombKey = keyBomb;
	spriteFolderPath = spritePath;
	dir = Direction::Down;
}

Player::~Player() {

}

void Player::Move() {

	if( isAlive == false ) return;

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
}

void Player::Draw() {

	if( isAlive == false ) return;

	LoadGraphScreen( posX, posY, spriteFolderPath, false );
	for( int i = 0; i < BULLET_MAX; i++ ){
		if( bullets[i] != nullptr ) bullets[i]->Draw();
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

	DrawFormatString( 100, 100, COLOR_WHITE, "charge %d", chargeCount );

	if( shootingCoolTime > SHOOTING_COOL_TIME ){
		if( GetKeyStatus( shotKey ) == InputState::Pressing ){
			chargeCount++;
		}
		else if( GetKeyStatus( shotKey ) == InputState::Released ){
			bool tempCharge = false;
			if( chargeCount >= CHARGE_COUNT ){
				tempCharge = true;
			}

			for( int i = 0; i < BULLET_MAX; i++ ){
				if( bullets[i] == nullptr ){
					bullets[i] = new Bullet( posX + PLAYER_SPRITE_WIDTH / 2 - BULLET_SPRITE_WIDTH / 2,
						posY + PLAYER_SPRITE_HEIGHT / 2 - BULLET_SPRITE_HEIGHT / 2, dir, spriteList[1], tempCharge );
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

void Player::Respawn(){

	if( isAlive == false ){
		respawnCount++;
		if( respawnCount > RESPAWN_REQUIRED_TIME ){
			respawnCount = 0;
			isAlive = true;
		}
	}
}

int Player::GetPlayerNumber(){
	return playerNumber;
}

int Player::GetPosX(){
	return posX;
}

int Player::GetPosY(){
	return posY;
}

Bullet* Player::GetBulletData( int arrayNum ) {
	return bullets[arrayNum];
}

bool Player::GetAlive(){
	return isAlive;
}

void Player::SetAlive( bool state ){
	isAlive = state;
}

int Player::GetScore(){
	return score;
}

void Player::SetScore( int value ){
	score = value;
}

void Player::AddScore( int value ){
	score += ( value );
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
