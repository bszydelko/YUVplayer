#pragma once
#include "olcPixelGameEngine.h"
#include "YUVvideo.h"



// Override base class with your custom functionality
class YUVplayer : public olc::PixelGameEngine
{
public:
	YUVvideo* _video;
	YUVplayer(YUVvideo* video);
public:
	bool OnUserCreate() override;
	bool OnUserUpdate(float fElapsedTime) override;
};
