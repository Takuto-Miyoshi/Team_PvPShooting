
#ifndef OBJECT_BASE_H
#define OBJECT_BASE_H

class ObjectBase
{
public:
	ObjectBase();
	virtual ~ObjectBase();

	virtual int GetPosX()const = 0;

	virtual int GetPosY()const = 0;

	virtual int GetCenterY()const = 0;

	virtual int GetSpriteWidth()const = 0;

	virtual int GetSpriteHeight()const = 0;

	virtual int GetHitOffsetUY() const = 0;

	virtual int GetHitOffsetDY() const = 0;

	virtual int GetSpriteNumber() const = 0;

	virtual void SetSpriteNumber( int value ) = 0;

	virtual Tag GetTag() const = 0;

	virtual void Draw() = 0;

	virtual void Control() = 0;

private:
	void GimmickControl();
};

#endif // !GIMMICK_H
