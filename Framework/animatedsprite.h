#ifndef __ANIMATEDSPRITE_H__
#define __ANIMATEDSPRITE_H__

#include "sprite.h"

#include <vector>

class BackBuffer;
class Texture;

class AnimatedSprite : public Sprite
{
	// Methods:
public:
	AnimatedSprite();
	~AnimatedSprite();

	bool Initialise(Texture& texture);

	void Process(float deltaTime);
	void Draw(BackBuffer& backbuffer);

	void SetFrameSpeed(float f);

	int GetWidth();
	int GetHeight();

	void SetTotalColumns(int col);
	int GetCurrentColumnNo();
	void SetCurrentColumnNo(int currentFrameNo);

	std::pair<int, int> GetCurrentFrame();
	int GetNoOfFrames();
	
	void SetTotalRows(int row);
	void SetCurrentRowNo(int row);
	int GetCurrentRow();

	void Pause();
	bool IsPaused();

	bool IsAnimating();
	void StartAnimating();

	bool IsLooping();
	void SetLooping(bool b);

protected:

private:

	// Fields:
public:

protected:
	std::vector<std::pair<int, int>>* m_pFrames; //NEEDS TO BE 2 DIMENTIONS

	float m_frameSpeed;
	int m_frameHeight;

	int m_totalColumns;
	int m_totalRows;

	float m_timeElapsed;
	std::pair<int, int> m_currentFrame;
	int m_currentColumnNo;
	int m_currentRowNo;

	bool m_paused;
	bool m_loop;
	bool m_animating;

private:

};

#endif // __ANIMATEDSPRITE_H__
