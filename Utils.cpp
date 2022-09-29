#include "Utils.h"

random_device Utils::rd;
mt19937 Utils::gen(Utils::rd());


void Utils::SetOrigin(Text& obj, Origins origin)
{

	SetOrigin(obj, origin, obj.getLocalBounds());

	/////////////////////////////////////////////////////////////////

	//FloatRect bounds = obj.getLocalBounds();
	//Vector2f originPos;
	//originPos.x = bounds.width * ((int)origin % 3) * 0.5f;
	//originPos.y = bounds.height * ((int)origin / 3) * 0.5f;
	//obj.setOrigin(originPos);

	/////////////////////////////////////////////////////////////////

	//FloatRect rect = obj.getLocalBounds();
	//
	//switch (origin)
	//{
	//case Origins::TL:
	//	obj.setOrigin(rect.width * 0, rect.height * 0);
	//	break;
	//case Origins::TC:
	//	obj.setOrigin(rect.width * 0.5f, rect.height * 0);
	//	break;
	//case Origins::TR:
	//	obj.setOrigin(rect.width , rect.height * 0);
	//	break;
	//case Origins::ML:
	//	obj.setOrigin(rect.width * 0, rect.height * 0.5f);
	//	break;
	//case Origins::MC:
	//	obj.setOrigin(rect.width * 0.5f, rect.height * 0.5f);
	//	break;
	//case Origins::MR:
	//	obj.setOrigin(rect.width, rect.height * 0.5f);
	//	break;
	//case Origins::BL:
	//	obj.setOrigin(rect.width * 0, rect.height);
	//	break;
	//case Origins::BC:
	//	obj.setOrigin(rect.width * 0.5f, rect.height);
	//	break;
	//case Origins::BR:
	//	obj.setOrigin(rect.width, rect.height);
	//	break;
	//default:
	//	break;
	//}
}

void Utils::SetOrigin(Sprite& obj, Origins origin)
{

	SetOrigin(obj, origin, obj.getLocalBounds());

	/////////////////////////////////////////////////////////////////

	//FloatRect bounds = obj.getLocalBounds();
	//Vector2f originPos;
	//originPos.x = ((int)origin % 3) * 0.5f;
	//originPos.y = ((int)origin / 3) * 0.5f;
	//obj.setOrigin(originPos);

	/////////////////////////////////////////////////////////////////

	//FloatRect rect = obj.getLocalBounds();

	//switch (origin)
	//{
	//case Origins::TL:
	//	obj.setOrigin(rect.width * 0, rect.height * 0);
	//	break;
	//case Origins::TC:
	//	obj.setOrigin(rect.width * 0.5f, rect.height * 0);
	//	break;
	//case Origins::TR:
	//	obj.setOrigin(rect.width, rect.height * 0);
	//	break;
	//case Origins::ML:
	//	obj.setOrigin(rect.width * 0, rect.height * 0.5f);
	//	break;
	//case Origins::MC:
	//	obj.setOrigin(rect.width * 0.5f, rect.height * 0.5f);
	//	break;
	//case Origins::MR:
	//	obj.setOrigin(rect.width, rect.height * 0.5f);
	//	break;
	//case Origins::BL:
	//	obj.setOrigin(rect.width * 0, rect.height);
	//	break;
	//case Origins::BC:
	//	obj.setOrigin(rect.width * 0.5f, rect.height);
	//	break;
	//case Origins::BR:
	//	obj.setOrigin(rect.width, rect.height);
	//	break;
	//default:
	//	break;
	//}
}

void Utils::SetOrigin(Transformable& obj, Origins origin, FloatRect rect)
{
	Vector2f originPos(rect.width, rect.height);
	originPos.x *= ((int)origin % 3) * 0.5f;
	originPos.y *= ((int)origin / 3) * 0.5f;
	obj.setOrigin(originPos);

}

int Utils::RandomRange(int min, int maxExclude)
{
	return (gen() % (maxExclude - min)) + min;
}

float Utils::RandomRange(float min, float max)
{
	uniform_real_distribution<float> dist(min, max - 1);
	return dist(gen);
}


