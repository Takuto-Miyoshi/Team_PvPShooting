
#include "Header/Common.h"
#include "Header/ObjectBase.h"
#include "Header/Stone.h"
#include "Header/GameScene.h"

Stone::Stone( int initX, int initY ){
	posX = initX;
	posY = initY;

	centerY = initY + STONE_HEIGHT / 2;
}

Stone::~Stone(){

}

void Stone::Draw(){
	LoadGraphScreen( posX, posY, Sprite::Gimmick::stone, true );
}

void Stone::Control(){

}
