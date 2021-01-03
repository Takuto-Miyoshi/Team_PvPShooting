
#include "Header/Common.h"
#include "Header/ObjectBase.h"
#include "Header/Tunnel.h"
#include "Header/GameScene.h"

Tunnel::Tunnel(){

	posX = 0;
	posY = 0;
	centerY = 1980;
	spriteNumber = 0;
}

Tunnel::~Tunnel(){

}

void Tunnel::Draw(){

	for( int i = 0; i < 2; i++ ){
		posX = ( i == 0 ) ? 0 : WINDOW_WIDTH - TUNNEL_WIDTH;
		DrawGraph( posX, posY, GameScene::GetObjectHandle( Tag::Tunnel, i ), true );
	}
}

void Tunnel::Control(){

}
