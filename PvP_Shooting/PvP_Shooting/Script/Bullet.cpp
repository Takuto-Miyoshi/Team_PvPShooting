
#include "Header/Bullet.h"

Bullet::Bullet( int InitPosX, int InitPosY, Direction direction, LPCTSTR spritePath ) {
	posX = InitPosX;
	posY = InitPosY;
	speed = 4;
	dir = direction;
	spriteFolderPath = spritePath;
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
