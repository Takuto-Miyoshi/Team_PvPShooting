
#ifndef STONE_H
#define STONE_H

class Stone : public ObjectBase
{
public:
	Stone( int initX, int initY );
	~Stone();

private:

	/// @brief 描画処理
	void Draw();

	/// @brief データ処理
	void Control();

	/// @brief X座標を取得する
	/// @return X座標
	int GetPosX() const { return posX; }

	/// @brief Y座標を取得する
	/// @return Y座標
	int GetPosY() const { return posY; }

	/// @brief 中心Y座標を取得する
	/// @return 中心Y座標
	int GetCenterY() const { return centerY; }

	/// @brief 自身の横幅を取得する
	/// @return 画像の横幅
	int GetSpriteWidth() const{ return STONE_WIDTH; }

	/// @brief 自身の縦幅を取得する
	/// @return 画像の縦幅
	int GetSpriteHeight() const{ return STONE_HEIGHT; }

	/// @brief 当たり判定の上からのずれ幅を取得する
	/// @return 上からのずれ幅
	int GetHitOffsetUY() const{ return STONE_OFFSET_UY; }

	/// @brief 当たり判定の下からのずれ幅を取得する
	/// @return 下からのずれ幅
	int GetHitOffsetDY() const { return STONE_OFFSET_DY; }

	/// @brief 現在の画像番号を取得する
	/// @return 画像番号
	int GetSpriteNumber() const { return 0; }

	/// @brief 画像番号を設定する
	/// @param value 設定する画像番号
	void SetSpriteNumber( int value ) {}

	/// @brief オブジェクトタグを取得する
	/// @return オブジェクトタグ
	Tag GetTag()const { return Tag::Stone; }

	/// @brief X座標を設定する
	/// @param x X座標
	void SetPosX( int x ) { posX = x; }

	/// @brief Y座標を設定する
	/// @param y Y座標
	void SetPosY( int y ) { posY = y; }

private:
	int posX;
	int posY;

	int centerY;
};
#endif // !STONE_H
