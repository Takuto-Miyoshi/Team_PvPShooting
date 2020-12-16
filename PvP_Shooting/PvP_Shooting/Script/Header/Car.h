
#ifndef CAR_H
#define CAR_H

class Car
{
public:
	Car( Direction dir );
	~Car();

	/// @brief 描画処理
	void Draw();

	/// @brief データ処理
	/// @return 処理が終わったらtrueを返す
	bool Control();

private:
	int posX;
	int posY;
	int centerY;
	LPCTSTR spritePath;
	int spriteNumber;
	int animationCounter;
	Direction direction;
	int speed;
	int graphHandle;
};

#endif // !CAR_H
