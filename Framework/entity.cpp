// COMP710 GP 2D Framework 2017

// This include:
#include "entity.h"

// Local includes:
#include "animatedsprite.h"
#include "backbuffer.h"

// Library includes:
#include <cassert>

Entity::Entity()
: m_pSprite(0)
, m_x(0.0f)
, m_y(0.0f)
, m_velocityX(0.0f)
, m_velocityY(0.0f)
, m_dead(false)
{

}

Entity::~Entity()
{

}

bool
Entity::Initialise(Sprite* sprite)
{
	assert(sprite);
	m_pSprite = sprite;

	return (true);
}

void
Entity::Process(float deltaTime)
{
	m_pSprite->Process(deltaTime);
}

void 
Entity::Draw(BackBuffer& backBuffer)
{
	assert(m_pAnimatedSprite);
	m_pSprite->SetX(static_cast<int>(m_x));
	m_pSprite->SetY(static_cast<int>(m_y));
	m_pSprite->Draw(backBuffer);
}

bool
Entity::IsCollidingWith(Entity& e)
{
	int px = e.GetPositionX() - this->GetPositionX();
	int py = e.GetPositionY() - this->GetPositionY();
	int distance = std::sqrt((px*px) + (py*py));

	if (distance <= m_pSprite->GetWidth())
	{
		return true;
	}

	return (false);
}

bool
Entity::IsDead() const
{
	if (m_dead)
	{
		return true;
	}
	else
	{
		return false;
	}
}
bool Entity::IsAnimating()
{
	return ((AnimatedSprite*)m_pSprite)->IsAnimating();
}

void 
Entity::SetDead(bool dead)
{
	m_dead = dead;
}

void
Entity::SetPosition(float x, float y)
{
	m_x = x;
	m_y = y;
}

void
Entity::SetPositionX(float x)
{
	m_x = x;
}

void
Entity::SetPositionY(float y)
{
	m_y = y;
}

float 
Entity::GetPositionX() const
{
	return (m_x);
}

float 
Entity::GetPositionY() const
{
	return (m_y);
}

float 
Entity::GetHorizontalVelocity() const
{
	return (m_velocityX);
}

float 
Entity::GetVerticalVelocity() const
{
	return (m_velocityY);
}

void 
Entity::SetHorizontalVelocity(float x)
{
	m_velocityX = x;
}

void 
Entity::SetVerticalVelocity(float y)
{
	m_velocityY = y;
}

void
Entity::SetFrameRow(int y){
	((AnimatedSprite*)m_pSprite)->SetCurrentRowNo(y);
}

float
Entity::GetWidth()
{
	return m_pSprite->GetWidth();
}

float
Entity::GetHeight()
{
	return m_pSprite->GetHeight();
}

