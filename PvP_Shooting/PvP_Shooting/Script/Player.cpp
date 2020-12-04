﻿
#include "Header/Player.h"

Player::Player( int playerNum, int keyUp, int keyRight, int keyLeft, int keyDown, int keyShot, int keyBomb, LPCTSTR spritePath ) {
	playerNumber = playerNum;
	isAlive = true;
	invincibleCount = 0;

	posX = 100;
	posY = 100;
	speed = 2;
	shootingCoolTime = 0;
	score = 0;

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
}

void Player::Draw() {

	if ( isAlive == true ) {
		LoadGraphScreen( posX, posY, spriteFolderPath, false );
		for ( int i = 0; i < BULLET_MAX; i++ ) {
			if ( bullets[i] != nullptr ) bullets[i]->Draw();
		}
	}
	else {
		if( invincibleCount >= 12 && invincibleCount < 24 || invincibleCount >= 36 && invincibleCount <48 ) {
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
	if( GetKeyStatus( shotKey ) == InputState::Pressed &&
		shootingCoolTime > SHOOTING_COOL_TIME ){
		for( int i = 0; i < BULLET_MAX; i++ ){
			if( bullets[i] == nullptr ){
				bullets[i] = new Bullet( posX, posY, dir, spriteList[1] );
				shootingCoolTime = 0;
				break;
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
