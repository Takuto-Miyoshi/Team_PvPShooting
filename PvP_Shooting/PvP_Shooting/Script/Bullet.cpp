
#include "Header/Bullet.h"
#include "Header/GameScene.h"

Bullet::Bullet( int playerNum, int InitPosX, int InitPosY, Direction direction, bool isCharged ) {
	playerNumber = playerNum;
	posX = InitPosX;
	posY = InitPosY;
	centerY = 0;
	dir = direction;
	spritePath = "";

	changeChargeShot = isCharged;
	speed = ( changeChargeShot == true ) ? BULLET_CHARGE_SPEED : BULLET_SPEED;
}

Bullet::~Bullet(){

}

void Bullet::Move(){

	switch ( dir )
	{
	case Direction::Up:
		posY -= speed;
		break;
	case Direction::Right:
		posX += speed;
		break;
	case Direction::Left:
		posX -= speed;
		break;
	case Direction::Down:
		posY += speed;
		break;
	case Direction::UpperRight:
		posX += speed;
		posY -= speed;
		break;
	case Direction::UpperLeft:
		posX -= speed;
		posY -= speed;
		break;
	case Direction::LowerRight:
		posX += speed;
		posY += speed;
		break;
	case Direction::LowerLeft:
		posX -= speed;
		posY += speed;
		break;
	default:
		break;
	}

	spriteNumber = ( changeChargeShot == true ) ? 1 : 0;
	centerY = posY + BULLET_HEIGHT / 2;
}

void Bullet::Draw() {

	DrawGraph( posX, posY, GameScene::GetBulletHandle( playerNumber, dir, changeChargeShot ), true );
}

int Bullet::GetPosX()const{
	return posX;
}

int Bullet::GetPosY()const{
	return posY;
}

Direction Bullet::GetDirection() {
	return dir;
}
