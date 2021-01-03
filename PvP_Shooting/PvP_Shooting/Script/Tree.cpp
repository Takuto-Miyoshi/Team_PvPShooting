
#include "Header/Common.h"
#include "Header/ObjectBase.h"
#include "Header/Tree.h"
#include "Header/GameScene.h"

Tree::Tree( int initX, int initY ){
	posX = initX;
	posY = initY;
	spriteNumber = 0;

	centerY = initY + TREE_HEIGHT / 2;
}

Tree::~Tree(){

}

void Tree::Draw(){
	DrawGraph( posX, posY, GameScene::GetObjectHandle( Tag::Tree, spriteNumber ), true );
}

void Tree::Control(){
	if( spriteNumber >= Sprite::treeFrame ) spriteNumber = Sprite::treeFrame - 1;
}
