#include "YUVplayer.h"

YUVplayer::YUVplayer(YUVvideo* video) : _video(video)
{
	// Name you application
	sAppName = video->getFilename();
	_frameCount = 0;
	_videoLength = 0;
	_frameLength = 1.0f / 30.0f;
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

	if (_videoLength != 0 && (_videoLength / _frameCount) >= _frameLength)
	{

		if (!_video->readFrame()) return false;
		_video->drawFrame(this);
		_frameCount++;

	}
	_videoLength += fElapsedTime;

	return true;
}