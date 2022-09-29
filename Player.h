#pragma once
#include"SpriteGameObject.h"
#include"Branch.h"
#include "EffectLog.h"
#include <SFML/Graphics.hpp>
#include<list>
#include<SFML/Audio.hpp>

using namespace sf;
using namespace std;


class Player : public SpriteGameObject
{
public:
	Player(const Texture& player,const Texture& rip, const Texture& axe, 
		const SoundBuffer& ChopBuffer, const SoundBuffer& DeathBuffer);

	void Set(Vector2f center);
	virtual void Init() override;
	virtual void Release() override;
	virtual void Updata(float dt) override;
	virtual void Draw(RenderWindow& window) override;
	virtual void SetPosition(Vector2f pos) override;
	virtual void SetFlipX(bool flip) override;
	bool isChopping;
	

	void ShowLogEffect();

	bool GetAlive() const;

	Sides GetPos() const;

	void Die();
	void Chop(Sides side);


protected:
	Sound ChopSound;
	Sound DeathSound;
	Texture texLog;
	list<EffectLog*> unuseLogs;
	list<EffectLog*> useLogs;

	const Texture& texPlayer;
	const Texture& texRip;
	bool isAlive;
	Sprite axe;
	Vector2f axePos;

	Sides pos;
	Vector2f centerPos;
	vector<Vector2f> originalPos;



};

