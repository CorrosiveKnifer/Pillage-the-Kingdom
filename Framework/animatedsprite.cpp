// This includes:
#include "animatedsprite.h"

// Local includes:
#include "texture.h"
#include "backbuffer.h"

AnimatedSprite::AnimatedSprite()
	: m_frameWidth(0)
	, m_timeElapsed(0.0f)
	, m_currentColumn(0)
	, m_currentRow(0)
	, m_paused(false)
	, m_animating(true)
	, m_xValues(0)
{

}

AnimatedSprite::~AnimatedSprite()
{

}

bool
AnimatedSprite::Initialise(Texture& texture)
{
	m_frameWidth = 0;

	m_loop = true;
	m_paused = false;
	if (!m_xValues.empty()){
		m_currentColumn = m_xValues[0];
	}
	m_currentColumnNo = 0;
	Sprite::Initialise(texture);

	StartAnimating();

	return (true);
}

void
AnimatedSprite::AddFrame(int x)
{
	m_xValues.push_back(x);
}

void
AnimatedSprite::Process(float deltaTime)
{
	if (!m_paused)
	{
		m_timeElapsed += deltaTime;
		//FIX THIS PROPERLY
		if (m_timeElapsed > m_frameSpeed)
		{
			m_currentColumn = m_xValues[m_currentColumnNo];
			m_timeElapsed = 0;
			if (!(m_xValues.size()<=1)){
				if (m_currentColumnNo >= (m_xValues.size() - 1))
				{
					if (m_loop)
					{
						m_currentColumnNo = 0;
					}
					else
					{
						m_animating = false;
					}
				}
				else
				{
					m_currentColumnNo++;
				}
			}
		}
	}
}

void
AnimatedSprite::Draw(BackBuffer& backbuffer)
{
	backbuffer.DrawAnimatedSprite(*this);
}

void
AnimatedSprite::SetFrameSpeed(float f)
{
	m_frameSpeed = f;
}

void
AnimatedSprite::SetFrameWidth(int w)
{
	m_frameWidth = w;
}

int
AnimatedSprite::GetFrameWidth()
{
	return m_frameWidth;
}

void
AnimatedSprite::SetFrameHeight(int h)
{
	m_frameHeight = h;
}

int
AnimatedSprite::GetFrameHeight()
{
	return m_frameHeight;
}

int
AnimatedSprite::GetCurrentFrame()
{
	return m_currentColumn;
}
void
AnimatedSprite::SetCurrentColumn(int currentFrame)
{
	m_currentColumn = currentFrame;
}

void
AnimatedSprite::Pause()
{
	m_paused = !m_paused;
}

bool
AnimatedSprite::IsPaused()
{
	return m_paused;
}

bool
AnimatedSprite::IsAnimating()
{
	return m_animating;
}

void
AnimatedSprite::StartAnimating()
{
	m_animating = true;

	m_timeElapsed = 0;
	m_currentColumn = 0;
}

bool
AnimatedSprite::IsLooping()
{
	return m_loop;
}

void
AnimatedSprite::SetLooping(bool b)
{
	m_loop = b;
}

int
AnimatedSprite::GetCurrentColumn()
{
	return m_currentColumnNo;
}
void
AnimatedSprite::SetCurrentColumnNo(int currentFrameNo)
{
	m_currentColumnNo = currentFrameNo;
	m_currentColumn = m_xValues[m_currentColumnNo];
}
int
AnimatedSprite::GetNoOfFrames()
{
	return m_xValues.size();
}
void
AnimatedSprite::SetCurrentRow(int row)
{
	m_currentRow = row;
}
int
AnimatedSprite::GetCurrentRow()
{
	return m_currentRow;
}