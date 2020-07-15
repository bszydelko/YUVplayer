#pragma once
#include <string>
#include "olcPixelGameEngine.h"
#include <fstream>


struct YUVframe
{
	uint8_t* _Y_pixels = nullptr;
	uint8_t* _U_pixels = nullptr;
	uint8_t* _V_pixels = nullptr;

	int32_t _width;
	int32_t _height;
	int32_t _chromaSubsampling;

	std::streamsize _Y_size;
	std::streamsize _U_size;
	std::streamsize _V_size;

	// a:b:c subsampling
	int32_t _c;
	int32_t _b;
	int32_t _a;

	YUVframe();
	YUVframe(int32_t width, int32_t height, int32_t chromaSubsampling);
	~YUVframe();

	void set(int32_t w, int32_t h, uint8_t y, uint8_t u, uint8_t v);
	olc::Pixel getRGB(int32_t w, int32_t h);
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


