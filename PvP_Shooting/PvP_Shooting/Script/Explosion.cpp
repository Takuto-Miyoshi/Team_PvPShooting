
#include "Header/Common.h"
#include "Header/Explosion.h"
#include "Header/GameScene.h"

Explosion::Explosion( int initX, int initY ){
	posX = initX;
	posY = initY;
	spriteNumber = 0;
	spritePath = Sprite::Gimmick::explosion[spriteNumber];
	animationCounter = 0;

	centerY = initY + EXPLOSION_HEIGHT / 2;
}

Explosion::~Explosion(){

}

void Explosion::Draw(){
	LoadGraphScreen( posX, posY, spritePath, true );
}

bool Explosion::Control(){

	for( int p = 0; p < PLAYER_MAX; p++ ){
		Player* target = SceneBase::GetPlayerData( p );

		if( target->GetAlive() == true ){
			if( ( ( target->GetPosX() + PLAYER_WIDTH ) > posX ) && ( target->GetPosX() < ( posX + EXPLOSION_WIDTH ) ) &&
				( target->GetPosY() + PLAYER_HEIGHT ) > ( posY + EXPLOSION_OFFSET_UY ) && ( ( target->GetPosY() + target->GetHitOffsetUY() ) < ( posY + EXPLOSION_HEIGHT ) ) ){

				if( spriteNumber == 3 ){
					target->DeathProcessing();
					target->AddScore( -1, SceneBase::GetBattleCount() + 1 );
				}
			}
		}
	}

	animationCounter++;

	if( animationCounter > 6 ){
		spriteNumber++;
		animationCounter = 0;
		if( spriteNumber == Sprite::explosionFrame ) return true;
	}

	spritePath = Sprite::Gimmick::explosion[spriteNumber];

	return false;
}
