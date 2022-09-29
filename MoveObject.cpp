#include "MoveObject.h"

//MoveObject::MoveObject(const Texture& tex, Object objects , Vector2f pos)
//	:SpriteGameObject(tex, pos), objects(objects)
//{
//	Init();
//}

MoveObject::MoveObject(const Texture& tex, Vector2f pos)
	:SpriteGameObject(tex, pos)
{
}

MoveObject::~MoveObject()
{
	//Release();
}

void MoveObject::Init()
{
	speed = (rand() % (speedRange.y - speedRange.x)) + speedRange.x;

	startPos.y = (rand() % (yRange.y - yRange.x)) + yRange.x;
	endPos.y = startPos.y;

	SetPosition(startPos);

	//switch (objects)
	//{
	//case Object::Bee :
	//{
	//	speed = (rand() % (speedRange.y - speedRange.x)) + speedRange.x;



	//	direction.x = -1;

	//	startPos.x = 2000;
	//	startPos.y = (rand() % 500) + 300;

	//	endPos.x = -100;
	//	endPos.y = startPos.y;

	//	SetPosition(startPos);
	//	
	//}
	//break;
	//case Object::Cloud :
	//{
	//	speed = (rand() & 300) + 200;
	//	direction.x = -1;

	//	startPos.x = 2000;
	//	startPos.y = (rand() % 300) + 10;

	//	endPos.x = -300;
	//	endPos.y = startPos.y;

	//	SetPosition(startPos);
	//}
	//break;
	//}
	//
	//
}

void MoveObject::Updata(float dt)
{
	Vector2f pos = GetPosition();
	float distanceX = endPos.x - pos.x;


	if (abs(distanceX) < 10)
		Init();

	Translate(direction * speed * dt);

}

void MoveObject::Set(Vector2i sRange, Vector2i yRange, Vector2f start,  Vector2f end)
{
	speedRange = sRange;
	this->yRange = yRange;
	startPos = start;
	endPos = end;

	direction = (endPos.x > startPos.x) ? 
		Vector2f(1, 0) : Vector2f(-1, 0);
}
