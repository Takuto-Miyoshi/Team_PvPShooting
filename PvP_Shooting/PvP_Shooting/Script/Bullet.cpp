
#include "Header/Bullet.h"

Bullet::Bullet( int playerNum, int InitPosX, int InitPosY, Direction direction, bool isCharged ) {
	playerNumber = playerNum;
	posX = InitPosX;
	posY = InitPosY;
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
}

void Bullet::Draw() {

	if( playerNumber == 1 ) {
		switch( dir )
		{
		case Direction::Up:
			spritePath = Sprite::Nobunaga::bulletUp[spriteNumber];
			break;
		case Direction::UpperRight:
			spritePath = Sprite::Nobunaga::bulletUpperRight[spriteNumber];
			break;
		case Direction::UpperLeft:
			spritePath = Sprite::Nobunaga::bulletUpperLeft[spriteNumber];
			break;
		case Direction::Down:
			spritePath = Sprite::Nobunaga::bulletDown[spriteNumber];
			break;
		case Direction::LowerRight:
			spritePath = Sprite::Nobunaga::bulletLowerRight[spriteNumber];
			break;
		case Direction::LowerLeft:
			spritePath = Sprite::Nobunaga::bulletLowerLeft[spriteNumber];
			break;
		case Direction::Right:
			spritePath = Sprite::Nobunaga::bulletRight[spriteNumber];
			break;
		case Direction::Left:
			spritePath = Sprite::Nobunaga::bulletLeft[spriteNumber];
			break;
		default:break;
		}
	}
	else {
		switch( dir )
		{
		case Direction::Up:
			spritePath = Sprite::Napoleon::bulletUp[spriteNumber];
			break;
		case Direction::UpperRight:
			spritePath = Sprite::Napoleon::bulletUpperRight[spriteNumber];
			break;
		case Direction::UpperLeft:
			spritePath = Sprite::Napoleon::bulletUpperLeft[spriteNumber];
			break;
		case Direction::Down:
			spritePath = Sprite::Napoleon::bulletDown[spriteNumber];
			break;
		case Direction::LowerRight:
			spritePath = Sprite::Napoleon::bulletLowerRight[spriteNumber];
			break;
		case Direction::LowerLeft:
			spritePath = Sprite::Napoleon::bulletLowerLeft[spriteNumber];
			break;
		case Direction::Right:
			spritePath = Sprite::Napoleon::bulletRight[spriteNumber];
			break;
		case Direction::Left:
			spritePath = Sprite::Napoleon::bulletLeft[spriteNumber];
			break;
		default:break;
		}
	}
	
	LoadGraphScreen( posX, posY, spritePath, true );
}

int Bullet::GetPosX(){
	return posX;
}

int Bullet::GetPosY(){
	return posY;
}

Direction Bullet::GetDirection() {
	return dir;
}
