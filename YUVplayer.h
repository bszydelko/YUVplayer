#pragma once
#include "olcPixelGameEngine.h"
#include "YUVvideo.h"



// Override base class with your custom functionality
class YUVplayer : public olc::PixelGameEngine
{
private:
	YUVvideo* _video;
	float _videoLength;
	int32_t _frameCount;
	float _frameLength;
public:
	YUVplayer(YUVvideo* video);
	bool OnUserCreate() override;
	bool OnUserUpdate(float fElapsedTime) override;
};
