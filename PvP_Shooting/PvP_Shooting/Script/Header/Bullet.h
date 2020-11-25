
#ifndef BULLET_H
#define BULLET_H

#include "Header/Common.h"

/// @brief �e�̍ő吔
const int BULLET_MAX = 10;

/// @brief �摜�̉���
const int BULLET_SPRITE_WIDTH = 32;

/// @brief �摜�̏c��
const int BULLET_SPRITE_HEIGHT = 32;

class Bullet{

public:
	/// @brief �R���X�g���N�^
	/// @param dir �i�ޕ���
	/// @param spritePath �ǂݍ��މ摜�̃p�X
	Bullet( int InitPosX, int InitPosY, Direction direction, LPCTSTR spritePath );
	~Bullet();

	/// @brief �ړ�
	void Move();
	
	/// @brief �`��
	void Draw();

	/// @brief X���W���擾����
	/// @return X���W
	int GetPosX();

	/// @brief Y���W���擾����
	/// @return Y���W
	int GetPosY();

private:
	int posX;
	int posY;
	int speed;
	Direction dir;

	LPCTSTR spriteFolderPath;
};

#endif // !BULLET_H
