
#ifndef EXPLOSION_H
#define EXPLOSION_H

class Explosion
{
public:
	Explosion( int initX, int initY );
	~Explosion();

	/// @brief 描画処理
	void Draw();

	/// @brief 処理
	/// @return 爆発が終わったらtrueを返す
	bool Control();

private:
	int posX;
	int posY;
	int centerY;
	int spriteNumber;
	int animationCounter;
};

#endif // !EXPLOSION_H
