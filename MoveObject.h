#pragma once
#include "SpriteGameObject.h"


enum class Object
{
	Bee,
	Cloud,
};

class MoveObject :	public SpriteGameObject
{
protected:
	Object objects;
	float speed;
	Vector2i speedRange;
	Vector2i yRange;

	Vector2f direction;

	Vector2f startPos;
	Vector2f endPos;

public:
	MoveObject(const Texture& tex, Vector2f pos = Vector2f());
	virtual ~MoveObject();

	virtual void Init() override;
	virtual void Updata(float dt) override;

	void Set(Vector2i sRange, Vector2i yRange, Vector2f start, Vector2f end);


};

