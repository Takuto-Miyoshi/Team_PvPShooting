
#include "Header/Common.h"
#include "Header/ObjectBase.h"
#include "Header/Flag.h"
#include "Header/GameScene.h"

Flag::Flag( int initX, int initY ){
	posX = initX;
	posY = initY;
	spriteNumber = 0;
	animationCounter = 0;

	centerY = initY + FLAG_HEIGHT / 4 * 3;
}

Flag::~Flag(){

}

void Flag::Draw(){
	DrawGraph( posX, posY, GameScene::GetObjectHandle( Tag::Flag, spriteNumber ), true );
}

void Flag::Control(){
	animationCounter++;

	if( animationCounter > 12 ){
		spriteNumber++;
		if( spriteNumber >= Sprite::flagFrame )spriteNumber = 0;

		animationCounter = 0;
	}
}
