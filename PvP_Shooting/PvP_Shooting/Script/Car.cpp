
#include "Header/Common.h"
#include "Header/ObjectBase.h"
#include "Header/Car.h"
#include "Header/GameScene.h"

Car::Car( Direction dir ){

	// 生成地点
	switch( dir )
	{
		// 右
	case Direction::Up:
	case Direction::Right:
	case Direction::UpperRight:
	case Direction::LowerRight:
	posX = WINDOW_WIDTH;
	posY = WINDOW_HEIGHT / 4 - CAR_HEIGHT / 2;
	direction = Direction::Right;
		break;
		// 左
	case Direction::Down:
	case Direction::Left:
	case Direction::UpperLeft:
	case Direction::LowerLeft:
	default:
	posX = 0 - CAR_WIDTH;
	posY = WINDOW_HEIGHT / 4 * 3 - CAR_HEIGHT / 2;
	direction = Direction::Left;
		break;
	}

	spriteNumber = 0;
	animationCounter = 0;
	speed = 14;
	centerY = posY + CAR_HEIGHT / 2;
}

Car::~Car(){

}

void Car::Draw(){
	switch( direction )
	{
	case Direction::Right:	DrawGraph( posX, posY, GameScene::GetObjectHandle( Tag::Car, spriteNumber ), true );		break;
	case Direction::Left:	DrawTurnGraph( posX, posY, GameScene::GetObjectHandle( Tag::Car, spriteNumber ), true );	break;
	}
}

void Car::Control(){

	switch( direction )
	{
	case Direction::Right:	posX -= speed; break;
	case Direction::Left:	posX += speed; break;
	}

	animationCounter++;

	if( animationCounter > 6 ){
		spriteNumber++;
		if( spriteNumber >= Sprite::carFrame )spriteNumber = 0;

		animationCounter = 0;
	}
}
