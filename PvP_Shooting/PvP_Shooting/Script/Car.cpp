
#include "Header/Common.h"
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
	posX = 0 - CAR_WIDTH;
	posY = WINDOW_HEIGHT / 4 * 3 - CAR_HEIGHT / 2;
	direction = Direction::Left;
		break;
	}

	spriteNumber = 0;
	spritePath = Sprite::Gimmick::car[spriteNumber];
	animationCounter = 0;
	speed = 14;
}

Car::~Car(){

}

void Car::Draw(){
	switch( direction )
	{
	case Direction::Right:	DrawGraph( posX, posY, graphHandle, true );		break;
	case Direction::Left:	DrawTurnGraph( posX, posY, graphHandle, true );	break;
	}
}

bool Car::Control(){

	for( int p = 0; p < PLAYER_MAX; p++ ){
		Player* target = SceneBase::GetPlayerData( p );

		if( target->GetAlive() == true ){
			// プレイヤーと車の判定
			if( ( ( target->GetPosX() + PLAYER_WIDTH ) > posX ) && ( target->GetPosX() < ( posX + CAR_WIDTH ) ) &&
				( target->GetPosY() + PLAYER_HEIGHT ) > ( posY + CAR_OFFSET_UY ) && ( ( target->GetPosY() + target->GetHitOffsetUY() ) < ( posY + CAR_HEIGHT ) ) ){
				target->BackStep();
				target->DeathProcessing();
				target->AddScore( -1, SceneBase::GetBattleCount() + 1 );
			}
		}

		// 車と弾の判定
		for( int b = 0; b < BULLET_MAX; b++ ){
			if( target->GetBulletData( b ) != nullptr ){
				if( GameScene::Collision(
					posX,
					posX + CAR_WIDTH,
					posY + CAR_OFFSET_UY,
					posY + CAR_HEIGHT - CAR_OFFSET_DY,
					target->GetBulletData( b )->GetPosX() + BULLET_RADIUS,
					target->GetBulletData( b )->GetPosY() + BULLET_RADIUS,
					BULLET_RADIUS ) == true ){
					target->DeleteBullet( b );
				}
			}
		}
	}

	switch( direction )
	{
	case Direction::Right:	posX -= speed; break;
	case Direction::Left:	posX += speed; break;
	}

	animationCounter++;

	if( animationCounter > 6 ){
		spriteNumber++;
		if( spriteNumber >= Sprite::carFrame )spriteNumber = 0;

		graphHandle = LoadGraph( Sprite::Gimmick::car[spriteNumber] );
		animationCounter = 0;
	}

	return ( posX < 0 - CAR_WIDTH * 2 || posX > WINDOW_WIDTH + CAR_WIDTH );
}
