#include "YUVplayer.h"

YUVplayer::YUVplayer(YUVvideo* video) : _video(video)
{
	// Name you application
	sAppName = video->getFilename();
}

bool YUVplayer::OnUserCreate()
{
	// Called once at the start, so create things here
	return true;
}

bool YUVplayer::OnUserUpdate(float fElapsedTime)
{
	// called once per frame, draws random coloured pixels
	if (GetKey(olc::Key::ESCAPE).bPressed) return false;

	//if (GetKey(olc::Key::SPACE).bPressed)
	{
		if (!_video->readFrame()) return false;
		_video->drawFrame(this);
	}



	return true;
}