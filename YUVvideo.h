#pragma once
#include <string>
#include "olcPixelGameEngine.h"
#include <fstream>



struct YUVpixel
{
	uint8_t* _y = nullptr;
	uint8_t* _u = nullptr;
	uint8_t* _v = nullptr;

	YUVpixel();
	YUVpixel(uint8_t y, uint8_t u, uint8_t v);
	~YUVpixel();

	olc::Pixel getRGB();

	void operator=(const YUVpixel& p);

};

struct YUVframe
{
	YUVpixel* _pixels = nullptr;

	YUVframe();
	YUVframe(int32_t width, int32_t height, int32_t chromaSubsampling);
	~YUVframe();

	void operator=(const YUVframe& f);
};

class YUVvideo
{
private:

	std::ifstream _file;
	bool _error;

	std::string _filename;
	int _width;
	int _height;
	int _chromaSubsampling;

	YUVframe* _frame;

public:
	YUVvideo(std::string filename, int width, int height, int chromaSubsampling);
	~YUVvideo();

	bool readFrame();
	bool drawFrame(olc::PixelGameEngine* pge);

	bool error();
	std::string getFilename();
	int getWidth();
	int getHeight();
	int getChromaSubsampling();
};


