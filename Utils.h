#pragma once
#include<SFML/Graphics.hpp>
#include <random>

using namespace sf;
using namespace std;

enum class Origins
{
	TL,
	TC,
	TR,
	ML,
	MC,
	MR,
	BL,
	BC,
	BR,
};


class Utils
{
public:
	static void SetOrigin(Text& obj, Origins origin);
	static void SetOrigin(Sprite& obj, Origins origin);
	static void SetOrigin(Transformable& obj, Origins origin, FloatRect rect);

	static int RandomRange(int min, int maxExclude);
	static float RandomRange(float min, float max);

private:
	static random_device rd;
	static mt19937 gen;


};

