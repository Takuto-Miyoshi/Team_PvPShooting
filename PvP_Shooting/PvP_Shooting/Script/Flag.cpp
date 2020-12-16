
#include "Header/Common.h"
#include "Header/ObjectBase.h"
#include "Header/Flag.h"
#include "Header/GameScene.h"

Flag::Flag( int initX, int initY ){
	posX = initX;
	posY = initY;
	spriteNumber = 0;
	spritePath = Sprite::Gimmick::flag[spriteNumber] ;
	animationCounter = 0;

	centerY = initY + FLAG_HEIGHT / 4 * 3;

	GameScene::EntryObject( this );
}

Flag::~Flag(){

}

void Flag::Draw(){
	LoadGraphScreen( posX, posY, spritePath, true );
}

void Flag::Control(){
	animationCounter++;

	if( animationCounter > 12 ){
		spriteNumber++;
		if( spriteNumber >= Sprite::flagFrame )spriteNumber = 0;

		spritePath = Sprite::Gimmick::flag[spriteNumber];
		animationCounter = 0;
	}
}
