
#include "Header/Common.h"

int Player::pos_x = WINDOW_WIDTH / 2;
int Player::pos_y = WINDOW_HEIGHT / 2;
int Player::speed = 1;

Player::Player() {

}

Player::~Player() {

}

void Player::Move() {
	if (CheckHitKey(KEY_INPUT_UP)) {
		pos_y -= speed;
	}
	else if (CheckHitKey(KEY_INPUT_DOWN)) {
		pos_y += speed;
	}

	if (CheckHitKey(KEY_INPUT_RIGHT)) {
		pos_x += speed;
	}
	else if (CheckHitKey(KEY_INPUT_LEFT)) {
		pos_x -= speed;
	}
}

void Player::Draw() {
	LoadGraphScreen(pos_x, pos_y, "Sprite/", false);
}
