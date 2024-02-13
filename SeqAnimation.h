#pragma once

#include "Animation.h"
#include "TextureManager.h"
#include "SDL.h"
#include <vector>
#include <map>
#include <string>

struct Sequence {
	int Speed, FrameCount, Width, Height;
	std::vector<std::string> TextureIDs;
};

class SeqAnimation : Animation
{
public:
	SeqAnimation(bool repeat = true);

	virtual void Update(float dt);
	void Parse(std::string source);
	void SetCurrentSeq(std::string seqID);
	void SetRepeat(bool repeat) { m_Repeat = repeat; }
	void DrawFrame(float x, float y, float xScale = 1, float yScale = 1, SDL_RendererFlip flip = SDL_FLIP_NONE);

private:
	Sequence m_CurrSeq;
	std::map<std::string, Sequence> m_SeqMap;
};

