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
	void AddFrame(int x, int y);

	void Process(float deltaTime);
	void Draw(BackBuffer& backbuffer);

	void SetFrameSpeed(float f);

	int GetWidth();
	int GetHeight();

	void SetTotalColumns(int col);
	void SetCurrentColumn(int currentFrame);
	int GetCurrentColumn();
	void SetCurrentColumnNo(int currentFrameNo);

	int GetCurrentFrame();
	int GetNoOfFrames();
	
	void SetTotalRows(int row);
	void SetCurrentRow(int row);
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
	std::vector<std::pair<int, int>>* m_pFrames;

	float m_frameSpeed;
	int m_frameHeight;

	int m_totalColumns;
	int m_totalRows;

	float m_timeElapsed;
	int m_currentColumn;
	int m_currentColumnNo;
	int m_currentRow;

	bool m_paused;
	bool m_loop;
	bool m_animating;

private:

};

#endif // __ANIMATEDSPRITE_H__
