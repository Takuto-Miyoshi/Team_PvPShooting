﻿
#include "Header/Common.h"
#include "Header/ObjectBase.h"
#include "Header/Box.h"
#include "Header/GameScene.h"
#include "Header/Explosion.h"

Explosion* explosion = nullptr;

Box::Box( int initX, int initY ){
	posX = initX;
	posY = initY;
	spriteNumber = 0;

	centerX = initX + BOX_WIDTH / 2;
	centerY = initY + BOX_HEIGHT / 2;

	isSummoned = false;
	explosionSEHandle = LoadSoundMem( Sounds::SE::explosion );
}

Box::~Box(){

}

void Box::Draw(){
	DrawGraph( posX, posY, GameScene::GetObjectHandle( Tag::Box, spriteNumber ), true );
	if( explosion != nullptr ) explosion->Draw();
}

void Box::Control(){

	if( spriteNumber == Sprite::boxFrame - 1 ) ExplosionExec();

	if( spriteNumber >= Sprite::boxFrame )spriteNumber = Sprite::boxFrame - 1;
}

void Box::ExplosionExec(){

	if( isSummoned == true ){
		if( explosion == nullptr ) return;

		if( explosion->Control() == true ){
			delete explosion;
			explosion = nullptr;
			return;
		}
	}
	else{
		PlaySoundMem( explosionSEHandle, DX_PLAYTYPE_BACK );
		explosion = new Explosion( centerX - EXPLOSION_WIDTH / 2, posY + BOX_HEIGHT - EXPLOSION_HEIGHT );
		isSummoned = true;
	}
}