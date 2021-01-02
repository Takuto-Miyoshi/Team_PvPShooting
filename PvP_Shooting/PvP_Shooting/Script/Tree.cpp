
#include "Header/Common.h"
#include "Header/ObjectBase.h"
#include "Header/Tree.h"
#include "Header/GameScene.h"

Tree::Tree( int initX, int initY ){
	posX = initX;
	posY = initY;
	spriteNumber = 0;
	spritePath = Sprite::Gimmick::tree[spriteNumber];

	centerY = initY + TREE_HEIGHT / 2;
}

Tree::~Tree(){

}

void Tree::Draw(){
	LoadGraphScreen( posX, posY, spritePath, true );
}

void Tree::Control(){
	if( spriteNumber >= Sprite::treeFrame ) spriteNumber = Sprite::treeFrame - 1;

	spritePath = Sprite::Gimmick::tree[spriteNumber];
}
