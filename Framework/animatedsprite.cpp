// This includes:
#include "animatedsprite.h"

// Local includes:
#include "texture.h"
#include "backbuffer.h"
#include "iniParser.h"

AnimatedSprite::AnimatedSprite()
	: m_timeElapsed(0.0f)
	, m_currentColumnNo(0)
	, m_currentRowNo(0)
	, m_paused(false)
	, m_animating(true)
	, m_pFrames(0)
{

}

AnimatedSprite::~AnimatedSprite()
{

}

bool
AnimatedSprite::Initialise(Texture& texture)
{
	SetWidth(0);
	
	std::string fileName = texture.GetFileName();
	m_loop = true;
	m_paused = false;
	m_pFrames = new std::vector<std::pair<int, int>>();

	int start = 0;

	if (IniParser::GetInstance().LoadIniFile("assets\\Animations.ini") && IniParser::GetInstance().DoesSectionExist(fileName))
	{ //Is the correct file loaded? and then does the sprite exist within the ini file.
		this->SetFrameSpeed(IniParser::GetInstance().GetValueAsFloat(fileName, "Speed"));
		this->SetTotalColumns(IniParser::GetInstance().GetValueAsInt(fileName, "Column"));
		this->SetTotalRows(IniParser::GetInstance().GetValueAsInt(fileName, "Row"));
		start = IniParser::GetInstance().GetValueAsInt(fileName, "StartFrame");
		this->SetLooping(IniParser::GetInstance().GetValueAsBoolean(fileName, "IsLooping"));
	
	
	}
	else
	{ //Load the sprite with default settings

	}

	if (!m_pFrames->empty()){

		m_pFrames = new std::vector<std::pair<int, int>>();
		//(total columns*currentRow + currentColumn)
		for (int m = 0; m < m_width; m++)
		{
			int heightVal = m_height/m_totalRows * m;
			for (int n = 0; n < m_height; n++)
			{
				int widthVal = m_width / m_totalColumns * n;
				std::pair<int, int> temp;
				temp.first = widthVal;
				temp.second = heightVal;
			}
		}
	}
	m_currentColumnNo = start;

	StartAnimating();

	return Sprite::Initialise(texture);
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
			m_currentFrame = m_pFrames->at(m_currentColumnNo);
			m_timeElapsed = 0;
			if (!(m_pFrames->size()<=1)){
				if (m_currentColumnNo >= (m_pFrames->size() - 1))
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

int
AnimatedSprite::GetWidth()
{
	return m_pTexture->GetWidth() / m_totalColumns;
}

int
AnimatedSprite::GetHeight()
{
	return m_pTexture->GetHeight() / m_totalRows;
}

std::pair<int, int>
AnimatedSprite::GetCurrentFrame()
{
	return m_currentFrame;
}

void
AnimatedSprite::SetTotalColumns(int col)
{
	m_totalColumns = col;
}

void
AnimatedSprite::SetTotalRows(int row)
{
	m_totalRows = row;
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
	m_currentColumnNo = 0;
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
AnimatedSprite::GetCurrentColumnNo()
{
	return m_currentColumnNo;
}

void
AnimatedSprite::SetCurrentColumnNo(int currentFrameNo)
{
	m_currentColumnNo = currentFrameNo;
	if (!m_pFrames->empty())
	{
		m_currentFrame = m_pFrames->at(m_totalColumns * m_currentRowNo + m_currentColumnNo);
	}
}
int
AnimatedSprite::GetNoOfFrames()
{
	return m_pFrames->size();
}

void
AnimatedSprite::SetCurrentRowNo(int row)
{
	m_currentRowNo = row;
	if (!m_pFrames->empty())
	{
		m_currentFrame = m_pFrames->at(m_totalColumns * m_currentRowNo + m_currentColumnNo);
	}
}
int
AnimatedSprite::GetCurrentRow()
{
	return m_currentRowNo;
}