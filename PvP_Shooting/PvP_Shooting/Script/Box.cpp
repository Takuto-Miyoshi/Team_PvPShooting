
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
	spritePath = Sprite::Gimmick::box[spriteNumber];

	centerX = initX + BOX_WIDTH / 2;
	centerY = initY + BOX_HEIGHT / 2;

	isSummoned = false;

	GameScene::EntryObject( this );
}

Box::~Box(){

}

void Box::Draw(){
	LoadGraphScreen( posX, posY, spritePath, true );
	if( explosion != nullptr ) explosion->Draw();
}

void Box::Control(){

	if( spriteNumber == Sprite::boxFrame - 1 ) ExplosionExec();

	if( spriteNumber >= Sprite::boxFrame )spriteNumber = Sprite::boxFrame - 1;

	spritePath = Sprite::Gimmick::box[spriteNumber];
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
		explosion = new Explosion( centerX - EXPLOSION_WIDTH / 2, posY + BOX_HEIGHT - EXPLOSION_HEIGHT );
		isSummoned = true;
	}
}