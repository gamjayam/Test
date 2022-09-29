#pragma once
#include "SpriteGameObject.h"
#include<SFML/Graphics.hpp>

class EffectLog : public SpriteGameObject
{
protected:
	// �߷�
	// �ӵ� (����)
	// ���ӵ� (ȸ��)
	//Ÿ�̸�
	Vector2f velocity;
	float angularVelocity;
	float duration;

	float timer;

	bool active;

public:
	//�ӵ�(����), // ���ӵ�(ȸ��)
	static const Vector2f Gravity;			//�߷�
	
	EffectLog(const Texture& tex, float duration);
	virtual ~EffectLog();

	void Fire(const Vector2f v, float av);
	bool GetActive() const;

	virtual void Init() override;
	virtual void Release() override;
	virtual void Updata(float dt) override;
	virtual void Draw(RenderWindow& window) override;







};