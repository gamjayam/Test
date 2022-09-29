#include "Player.h"
#include"inputMgr.h"

Player::Player(const Texture& player, const Texture& rip, const Texture& axe,
	const SoundBuffer& ChopBuffer, const SoundBuffer& DeathBuffer)

	:SpriteGameObject(player), texPlayer(player), texRip(rip) , originalPos(2),
	isAlive(true), isChopping(false)
{
	this->axe.setTexture(axe);
	Utils::SetOrigin(this->axe, Origins::MR);
	Vector2f size = GetSize();
	axePos.x = -size.x * 0.5f + 50;
	axePos.y = -size.y * 0.5f + 25;
	pos = Sides::Right;
	SetOrigin(Origins::BC);



	DeathSound.setBuffer(DeathBuffer);
	ChopSound.setBuffer(ChopBuffer);

}	

void Player::Set(Vector2f center)
{
	centerPos = center;
}

void Player::Init()
{
	sprite.setTexture(texPlayer, true);
	Utils::SetOrigin(sprite, Origins::BC);
	SetFlipX(pos == Sides::Left);
	 
	Vector2f size = GetSize();
	
	originalPos[(int)Sides::Left].x = centerPos.x - size.x * 2;
	originalPos[(int)Sides::Left].y = centerPos.y;

	originalPos[(int)Sides::Right].x = centerPos.x + size.x * 2;
	originalPos[(int)Sides::Right].y = centerPos.y;

	texLog.loadFromFile("graphics/log.png");
	for (int i = 0; i < 100; i++)
	{
		auto log = new EffectLog(texLog, 5.f);
		unuseLogs.push_back(log);
	}


	isAlive = true;
	isChopping = false;


	SetPosition(originalPos[(int)pos]);
}

void Player::Release()
{
	for (auto log : unuseLogs)
	{
		delete log;
	}
	unuseLogs.clear();

	for (auto log : useLogs)
	{
		delete log;
	}
	useLogs.clear();
}

void Player::Updata(float dt)
{
	SpriteGameObject::Updata(dt);
	auto it = useLogs.begin();
	while (it != useLogs.end())
	{
		(*it)->Updata(dt);
		if (!(*it)->GetActive())
		{
			unuseLogs.push_back(*it);
			it = useLogs.erase(it);
		}
		else
		{
			++it;
		}
	}

	if (!isAlive)
		return;



}

void Player::Draw(RenderWindow& window)
{
	SpriteGameObject::Draw(window);
	
	if (isChopping)
	{
		window.draw(axe);
	}

	for (auto& log : useLogs)
	{
		log->Draw(window);
	}

}

void Player::SetPosition(Vector2f pos)
{
	SpriteGameObject::SetPosition(pos);

	Vector2f axePos2 = axePos;
	if (axe.getScale().x < 0)
	{
		axePos2.x *= -1;
	}

	axe.setPosition(pos + axePos2);
}

void Player::SetFlipX(bool flip)
{
	SpriteGameObject::SetFlipX(flip);

	Vector2f scale = axe.getScale();
	scale.x = flip ? -abs(scale.x) : abs(scale.x);
	axe.setScale(scale);
}

void Player::ShowLogEffect()
{
	if (unuseLogs.empty())
		return;

	auto log = unuseLogs.front();
	unuseLogs.pop_front();
	useLogs.push_back(log);

	Vector2f force;
	force.x = pos == Sides::Left ? 1500 : -1500;
	force.y = -1500;

	float aForce = pos == Sides::Left ? 360 * 8 : -360 * 8;

	Vector2f pos = centerPos;
	pos.y = axe.getPosition().y;

	log->SetPosition(pos);
	log->Fire(force, aForce);

}

bool Player::GetAlive() const
{
	return isAlive;
}

Sides Player::GetPos() const
{
	return Sides();
}

void Player::Die()
{
	isAlive = false;
	isChopping = false;

	sprite.setTexture(texRip, true);
	SetFlipX(false);
	Utils::SetOrigin(sprite, Origins::BC);
	
	DeathSound.play();


}

void Player::Chop(Sides side)
{
	
	pos = side;

	SetFlipX(pos == Sides::Left);
	SetPosition(originalPos[(int)pos]);

	ShowLogEffect();
	ChopSound.play();
}
