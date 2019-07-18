#pragma once
#include "entity.h"

class Tower;

class Explosion :public Entity
{
	//Class methods
public:
	Explosion();
	~Explosion();

	bool Initialise(Sprite* sprite, Tower* aTower);
	void Process(float deltaTime);
	void Draw(BackBuffer& backBuffer);

	bool IsAnimating();
private:

protected:

	//Member data
public:

private:
	Tower* m_tower;

protected:
};

