
#include "Header/Player.h"
#include "Header/GameScene.h"

#define USE_CONTROLLER

Player::Player( int padNum, int playerNum, int keyUp, int keyRight, int keyLeft, int keyDown, int keyShot, int keyBomb, int keyUlt ){
	playerNumber = playerNum;
	isAlive = true;
	invincibleCount = 0;

	posX = 100;
	posY = 100;
	centerY = 0;
	speed = PLAYER_SPEED;
	shootingCoolTime = 0;
	chargeCount = 0;
	for( int i = 0; i < ROUND_MAX; i++ )score[i] = 0;

	padNumber = padNum;
	upMovingKey = keyUp;
	rightMovingKey = keyRight;
	leftMovingKey = keyLeft;
	downMovingKey = keyDown;
	shotKey = keyShot;
	bombKey = keyBomb;
	ultKey = keyUlt;
	spritePath = "";
	dir = ( playerNum == 1 ) ? Direction::Right : Direction::Left;

	for( int i = 0; i < BULLET_MAX; i++ )bullets[i] = nullptr;

	isMoved = false;
	isAttacked = false;
	spriteNumber = 0;
	animationCounter = 0;

	GameScene::EntryObject( this );
}

Player::~Player() {

}

void Player::Move() {

	isMoved = false;
	int tempX = posX;
	int tempY = posY;

#ifdef USE_CONTROLLER
	if( GetPadStatus( playerNumber, upMovingKey ) == InputState::Pressing ){
		posY -= speed;
		dir = Direction::Up;
	}
	else if( GetPadStatus( playerNumber, downMovingKey ) == InputState::Pressing ){
		posY += speed;
		dir = Direction::Down;
	}

	if( GetPadStatus( playerNumber, rightMovingKey ) == InputState::Pressing ){
		posX += speed;
		dir = Direction::Right;
	}
	else if( GetPadStatus( playerNumber, leftMovingKey ) == InputState::Pressing ){
		posX -= speed;
		dir = Direction::Left;
	}

	if( GetPadStatus( playerNumber, upMovingKey ) == InputState::Pressing ) {
		if( GetPadStatus( playerNumber, rightMovingKey ) == InputState::Pressing ) {
			dir = Direction::UpperRight;
		}
		else if( GetPadStatus( playerNumber, leftMovingKey ) == InputState::Pressing ) {
			dir = Direction::UpperLeft;
		}
	}
	else if( GetPadStatus( playerNumber, downMovingKey ) == InputState::Pressing ) {
		if( GetPadStatus( playerNumber, rightMovingKey ) == InputState::Pressing ) {
			dir = Direction::LowerRight;
		}
		else if( GetPadStatus( playerNumber, leftMovingKey ) == InputState::Pressing ) {
			dir = Direction::LowerLeft;
		}
	}

#else
	if( GetKeyStatus( upMovingKey ) == InputState::Pressing ) {
		posY -= speed;
		dir = Direction::Up;
	}
	else if( GetKeyStatus( downMovingKey ) == InputState::Pressing ) {
		posY += speed;
		dir = Direction::Down;
	}

	if( GetKeyStatus( rightMovingKey ) == InputState::Pressing ) {
		posX += speed;
		dir = Direction::Right;
	}
	else if( GetKeyStatus( leftMovingKey ) == InputState::Pressing ) {
		posX -= speed;
		dir = Direction::Left;
	}

	if( GetKeyStatus( upMovingKey ) == InputState::Pressing ) {
		if( GetKeyStatus( rightMovingKey ) == InputState::Pressing ) {
			dir = Direction::UpperRight;
		}
		else if( GetKeyStatus( leftMovingKey ) == InputState::Pressing ) {
			dir = Direction::UpperLeft;
		}
	}
	else if( GetKeyStatus( downMovingKey ) == InputState::Pressing ) {
		if( GetKeyStatus( rightMovingKey ) == InputState::Pressing ) {
			dir = Direction::LowerRight;
		}
		else if( GetKeyStatus( leftMovingKey ) == InputState::Pressing ) {
			dir = Direction::LowerLeft;
		}
	}
#endif

	// 移動したかの判定
	if( tempX != posX || tempY != posY ) isMoved = true;

	// 画面外なら戻す
	if( posY < 0 ) posY = 0;
	if( posY > WINDOW_HEIGHT - PLAYER_HEIGHT ) posY = WINDOW_HEIGHT - PLAYER_HEIGHT;
	if( posX < 0 ) posX = 0;
	if( posX > WINDOW_WIDTH - PLAYER_WIDTH ) posX = WINDOW_WIDTH - PLAYER_WIDTH;

	// 位置調整
	centerY = posY + PLAYER_HEIGHT / 2;
}

void Player::Draw() {

	// アニメーション
	// 攻撃
	if( isAttacked == true ){
		if( spriteNumber >= Sprite::attackFrame ){
			isAttacked = false;
		}
		else if( playerNumber == 1 ){
			switch( dir )
			{
			case Direction::Up:
			case Direction::UpperRight:
			case Direction::UpperLeft:
				spritePath = Sprite::Nobunaga::attackUp[spriteNumber];
				break;
			case Direction::Down:
			case Direction::LowerRight:
			case Direction::LowerLeft:
				spritePath = Sprite::Nobunaga::attackDown[spriteNumber];
				break;
			case Direction::Right:
				spritePath = Sprite::Nobunaga::attackRight[spriteNumber];
				break;
			case Direction::Left:
				spritePath = Sprite::Nobunaga::attackLeft[spriteNumber];
				break;
			default:break;
			}
		}
		else{
			switch( dir )
			{
			case Direction::Up:
			case Direction::UpperRight:
			case Direction::UpperLeft:
				spritePath = Sprite::Napoleon::attackUp[spriteNumber];
				break;
			case Direction::Down:
			case Direction::LowerRight:
			case Direction::LowerLeft:
				spritePath = Sprite::Napoleon::attackDown[spriteNumber];
				break;
			case Direction::Right:
				spritePath = Sprite::Napoleon::attackRight[spriteNumber];
				break;
			case Direction::Left:
				spritePath = Sprite::Napoleon::attackLeft[spriteNumber];
				break;
			default:break;
			}
		}
	}
	// 移動
	else if( isMoved == true ){
		if( spriteNumber >= Sprite::walkFrame ){
			spriteNumber = 1;
		}
		else if( playerNumber == 1 ){
			switch( dir )
			{
			case Direction::Up:
			case Direction::UpperRight:
			case Direction::UpperLeft:
				spritePath = Sprite::Nobunaga::walkUp[spriteNumber];
				break;
			case Direction::Down:
			case Direction::LowerRight:
			case Direction::LowerLeft:
				spritePath = Sprite::Nobunaga::walkDown[spriteNumber];
				break;
			case Direction::Right:
				spritePath = Sprite::Nobunaga::walkRight[spriteNumber];
				break;
			case Direction::Left:
				spritePath = Sprite::Nobunaga::walkLeft[spriteNumber];
				break;
			default:break;
			}
		}
		else{
			switch( dir )
			{
			case Direction::Up:
			case Direction::UpperRight:
			case Direction::UpperLeft:
				spritePath = Sprite::Napoleon::walkUp[spriteNumber];
				break;
			case Direction::Down:
			case Direction::LowerRight:
			case Direction::LowerLeft:
				spritePath = Sprite::Napoleon::walkDown[spriteNumber];
				break;
			case Direction::Right:
				spritePath = Sprite::Napoleon::walkRight[spriteNumber];
				break;
			case Direction::Left:
				spritePath = Sprite::Napoleon::walkLeft[spriteNumber];
				break;
			default:break;
			}
		}
	}
	// 待機
	else{
		if( spriteNumber >= Sprite::waitFrame ){
			spriteNumber = 0;
		}
		else if( playerNumber == 1 ){
			switch( dir )
			{
			case Direction::Up:
			case Direction::UpperRight:
			case Direction::UpperLeft:
				spritePath = Sprite::Nobunaga::waitUp[spriteNumber];
				break;
			case Direction::Down:
			case Direction::LowerRight:
			case Direction::LowerLeft:
				spritePath = Sprite::Nobunaga::waitDown[spriteNumber];
				break;
			case Direction::Right:
				spritePath = Sprite::Nobunaga::waitRight[spriteNumber];
				break;
			case Direction::Left:
				spritePath = Sprite::Nobunaga::waitLeft[spriteNumber];
				break;
			default:break;
			}
		}
		else{
			switch( dir )
			{
			case Direction::Up:
			case Direction::UpperRight:
			case Direction::UpperLeft:
				spritePath = Sprite::Napoleon::waitUp[spriteNumber];
				break;
			case Direction::Down:
			case Direction::LowerRight:
			case Direction::LowerLeft:
				spritePath = Sprite::Napoleon::waitDown[spriteNumber];
				break;
			case Direction::Right:
				spritePath = Sprite::Napoleon::waitRight[spriteNumber];
				break;
			case Direction::Left:
				spritePath = Sprite::Napoleon::waitLeft[spriteNumber];
				break;
			default:break;
			}
		}
	}

	// 点滅
	if( isAlive == true || ( invincibleCount >= 12 && invincibleCount < 24 || invincibleCount >= 36 && invincibleCount < 48 ) ) {
		LoadGraphScreen( posX - PLAYER_OFFSET_X, posY, spritePath, true );
	}

	animationCounter++;
	if( animationCounter >= 6 ){
		animationCounter = 0;
		spriteNumber++;
	}

	for( int i = 0; i < BULLET_MAX; i++ ){
		if( bullets[i] != nullptr )bullets[i]->Draw();
	}

}

void Player::Shoot() {

	if( isAlive == false ) return;

	shootingCoolTime++;

	// 画面外ならdelete
	for( int i = 0; i < BULLET_MAX; i++ ){
		if( bullets[i] != nullptr ){
			if( IsOutsideWindow( bullets[i]->GetPosX(), bullets[i]->GetPosY() ) == true )DeleteBullet( i );
		}
	}

	// 射撃キーが押されたら弾を生成
	if( shootingCoolTime > SHOOTING_COOL_TIME ){
#ifdef USE_CONTROLLER
		if( GetPadStatus( playerNumber, shotKey ) == InputState::Pressing ){
#else
		if( GetKeyStatus( shotKey ) == InputState::Pressing ){
#endif
			chargeCount++;
		}
#ifdef USE_CONTROLLER
		else if( GetPadStatus( playerNumber, shotKey ) == InputState::Released ){
#else
		else if( GetKeyStatus( shotKey ) == InputState::Released ){
#endif
			bool tempCharge = false;
			if( chargeCount >= CHARGE_COUNT ){
				tempCharge = true;
			}

			for( int i = 0; i < BULLET_MAX; i++ ){
				if( bullets[i] == nullptr ){
					bullets[i] = new Bullet( playerNumber, posX, posY, dir, tempCharge );
					shootingCoolTime = 0;
					chargeCount = 0;
					isAttacked = true;
					spriteNumber = 0;
					break;
				}
			}
		}
	}

	for( int i = 0; i < BULLET_MAX; i++ ){
		if( bullets[i] != nullptr ) bullets[i]->Move();
	}
}

void Player::Control(){

}

void Player::Bomb(){

}

void Player::Hit(){

	for( int i = 0; i < OBJECT_MAX; i++ ){
		ObjectBase* objData = GameScene::GetObjectData( i );
		if( objData != nullptr ){
			if( GetTag() != objData->GetTag() ){
				// プレイヤーとトンネルの判定
				if( objData->GetTag() == Tag::Tunnel ){
					if( posX < TUNNEL_WIDTH || posX > WINDOW_WIDTH - TUNNEL_WIDTH - PLAYER_WIDTH ) BackStep();
				}
				// プレイヤーとオブジェクトの判定
				else if( ( ( posX + PLAYER_WIDTH ) > objData->GetPosX() ) && ( posX < ( objData->GetPosX() + objData->GetSpriteWidth() ) ) &&
					( posY + PLAYER_HEIGHT ) > ( objData->GetPosY() + objData->GetHitOffsetUY() ) && ( ( posY + GetHitOffsetUY() ) < ( objData->GetPosY() + objData->GetSpriteHeight() ) ) ){

					BackStep();
				}

				// 弾とオブジェクトの判定
				for( int b = 0; b < BULLET_MAX; b++ ){
					if( bullets[b] != nullptr ){
						if( objData->GetTag() == Tag::Tunnel ){
							if( bullets[b]->GetPosX() < TUNNEL_WIDTH || bullets[b]->GetPosX() > WINDOW_WIDTH - TUNNEL_WIDTH - BULLET_WIDTH ) DeleteBullet( b );
						}
						else{
							if( GameScene::Collision(
								objData->GetPosX(),
								objData->GetPosX() + objData->GetSpriteWidth(),
								objData->GetPosY() + objData->GetHitOffsetUY(),
								objData->GetPosY() + objData->GetSpriteHeight() - objData->GetHitOffsetDY(),
								bullets[b]->GetPosX() + BULLET_RADIUS,
								bullets[b]->GetPosY() + BULLET_RADIUS,
								BULLET_RADIUS ) == true ){
								switch( objData->GetTag() )
								{
								case Tag::Flag:
									break;
								case Tag::Tree:
									objData->SetSpriteNumber( objData->GetSpriteNumber() + 1 );
									if( objData->GetSpriteNumber() < Sprite::treeFrame ) DeleteBullet( b );
									break;
								case Tag::Box:
									objData->SetSpriteNumber( objData->GetSpriteNumber() + 1 );
									if( objData->GetSpriteNumber() < Sprite::boxFrame ) DeleteBullet( b );
									break;
								default: DeleteBullet( b );
									break;
								}
							}
						}
					}
				}
			}
		}
	}
}

void Player::Invincible(){

	if( isAlive == false ){
		invincibleCount++;
		if( invincibleCount > INVINCIBLE_TIME ){
			invincibleCount = 0;
			shootingCoolTime = SHOOTING_COOL_TIME;
			isAlive = true;
		}
	}
}

int Player::GetPlayerNumber(){
	return playerNumber;
}

int Player::GetPosX()const{
	return posX;
}

int Player::GetPosY()const{
	return posY;
}

int Player::GetCenterY()const{
	return centerY;
}

void Player::SetPosX( int x ){
	posX = x;
}

void Player::SetPosY( int y ){
	posY = y;
}

Bullet* Player::GetBulletData( int arrayNum )const {
	return bullets[arrayNum];
}

bool Player::GetAlive()const {
	return isAlive;
}

void Player::SetAlive( bool state ){
	isAlive = state;
}

int Player::GetScore( int round )const{

	if( round == -1 )return ( score[0] + score[1] + score[2] );

	if( round <= 0 || round > ROUND_MAX )return 0;
	return score[round - 1];
}

void Player::ResetScore(){

	for( int i = 0; i < ROUND_MAX; i++ )score[i] = 0;
}

void Player::AddScore( int value, int round ){
	if( round <= 0 || round > ROUND_MAX )return;
	score[round - 1] += ( value );
}

void Player::DeleteBullet( int arrayNum ){
	if( bullets[arrayNum] == nullptr ) return;
	delete bullets[arrayNum];
	bullets[arrayNum] = nullptr;
}

void Player::DeathProcessing(){
	isAlive = false;
	for( int i = 0; i < BULLET_MAX; i++ ){
		DeleteBullet( i );
	}
}

void Player::BackStep(){
	switch( dir )
	{
	case Direction::Up: posY += speed; break;
	case Direction::Down:posY -= speed; break;
	case Direction::Right:posX -= speed; break;
	case Direction::Left:posX += speed; break;
	case Direction::UpperRight:
		posY += speed;
		posX -= speed;
		break;
	case Direction::UpperLeft:
		posY += speed;
		posX += speed;
		break;
	case Direction::LowerRight:
		posY -= speed;
		posX -= speed;
		break;
	case Direction::LowerLeft:
		posY -= speed;
		posX += speed;
		break;
	default:
		break;
	}
}
