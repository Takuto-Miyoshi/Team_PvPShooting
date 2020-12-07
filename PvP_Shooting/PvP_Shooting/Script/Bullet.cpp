
#include "Header/Bullet.h"

Bullet::Bullet( int InitPosX, int InitPosY, Direction direction, LPCTSTR spritePath, bool isCharged ) {
	posX = InitPosX;
	posY = InitPosY;
	dir = direction;
	spriteFolderPath = spritePath;

	changeChargeShot = isCharged;
	speed = ( changeChargeShot == true ) ? BULLET_CHARGE_SPEED : BULLET_SPEED;
}

Bullet::~Bullet(){

}

void Bullet::Move(){

	switch ( dir )
	{
	case Up:
		posY -= speed;
		break;
	case Right:
		posX += speed;
		break;
	case Left:
		posX -= speed;
		break;
	case Down:
		posY += speed;
		break;
	case UpperRight:
		posX += speed;
		posY -= speed;
		break;
	case UpperLeft:
		posX -= speed;
		posY -= speed;
		break;
	case LowerRight:
		posX += speed;
		posY += speed;
		break;
	case LowerLeft:
		posX -= speed;
		posY += speed;
		break;
	default:
		break;
	}
}

void Bullet::Draw(){
	LoadGraphScreen( posX, posY, spriteFolderPath, true );
}

int Bullet::GetPosX(){
	return posX;
}

int Bullet::GetPosY(){
	return posY;
}
