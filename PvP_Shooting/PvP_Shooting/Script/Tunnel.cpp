
#include "Header/Common.h"
#include "Header/ObjectBase.h"
#include "Header/Tunnel.h"
#include "Header/GameScene.h"
#include "Header/Car.h"

static Car* car[2];

Tunnel::Tunnel(){

	posX = 0;
	posY = 0;
	centerY = 1980;
	spriteNumber = 0;
	spritePath = Sprite::Gimmick::tunnel[spriteNumber];
	summonCounter = 0;

	srand( ( unsigned ) time( NULL ) );

	for( int i = 0; i < 2; i++ ) car[i] = nullptr;

	GameScene::EntryObject( this );
}

Tunnel::~Tunnel(){

}

void Tunnel::Draw(){
	for( int i = 0; i < 2; i++ ){
		if( car[i] != nullptr ) car[i]->Draw();
	}

	for( int i = 0; i < 2; i++ ){
		posX = ( i == 0 ) ? 0 : WINDOW_WIDTH - TUNNEL_WIDTH;
		LoadGraphScreen( posX, posY, Sprite::Gimmick::tunnel[i], true );
	}
}

void Tunnel::Control(){
	for( int i = 0; i < 2; i++ ){
		CarExec( i );
	}
}

void Tunnel::CarExec( int num ){

	static bool isSummoned = false;

	if( isSummoned == true ){

		if( car[num] == nullptr ) return;

		if( car[num]->Control() == true ){
			delete car[num];
			car[num] = nullptr;
			isSummoned = false;
			return;
		}
	}
	else{
		summonCounter++;

		if( summonCounter >= 180 ){
			if( rand() % 2 == 0 ){
				car[0] = new Car( Direction::Right );
				car[1] = new Car( Direction::Left );
				summonCounter = 0;
				isSummoned = true;
			}
		}
	}
}
