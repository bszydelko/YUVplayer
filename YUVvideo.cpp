#include "YUVvideo.h"
#include <iostream>


YUVpixel::YUVpixel()
{
	_y = new uint8_t;
	_u = new uint8_t;
	_v = new uint8_t;
}

YUVpixel::YUVpixel(uint8_t y, uint8_t u, uint8_t v)
{
	_y = new uint8_t;
	_u = new uint8_t;
	_v = new uint8_t;

	*_y = y;
	*_u = u;
	*_v = v;
}

YUVpixel::~YUVpixel()
{
	delete _y;
	delete _u;
	delete _v;
}

olc::Pixel YUVpixel::getRGB()
{
	float R = *_y + 1.402 * (*_v - 128);
	float G = *_y - 0.344 * (*_u - 128) - 0.714 * (*_v - 128);
	float B = *_y + 1.772 * (*_u - 128);

	if (R < 0) { R = 0; } if (G < 0) { G = 0; } if (B < 0) { B = 0; }
	if (R > 255) { R = 255; } if (G > 255) { G = 255; } if (B > 255) { B = 255; }

	return olc::Pixel(R, G, B);
}

void YUVpixel::operator=(const YUVpixel &p)
{
	std::memcpy(this->_y, p._y, sizeof(uint8_t));
	std::memcpy(this->_u, p._u, sizeof(uint8_t));
	std::memcpy(this->_v, p._v, sizeof(uint8_t));
}
//==============================================================================================
YUVframe::YUVframe(int32_t width, int32_t height, int32_t chromaSubsampling)
{
	this->_pixels = new YUVpixel[width * height];
}

YUVframe::~YUVframe()
{
	delete [] _pixels;
}

void YUVframe::operator=(const YUVframe& f)
{
	std::memcpy(this->_pixels, f._pixels, sizeof(YUVpixel));
}
//==============================================================================================
YUVvideo::YUVvideo(std::string filename, int width, int height, int chromaSubsampling) : 
	_filename(filename), _width(width), _height(height), _chromaSubsampling(chromaSubsampling)
{
	_error = false;
	_file.open(_filename, std::ios::binary);

	if (!_file.good())
	{
		_error = true;
	}
	_frame = new YUVframe;
}

YUVvideo::~YUVvideo()
{
	_file.close();
	delete _frame;
}

bool YUVvideo::readFrame()
{
	char* y = new char[_width * _height];
	_file.read(y, (long)_width * (long)_height);

	char* u = new char[(_width * _height) / 4];
	_file.read(u, (_width * _height) / 4);

	char* v = new char[(_width * _height) / 4];
	_file.read(v, (_width * _height) / 4);


	YUVframe* f = new YUVframe(_width, _height, _chromaSubsampling);
	YUVpixel p;

	uint8_t mask = 0b00000011;
	uint8_t shift = 6;
	
	for (size_t i = 0; i < _height; i++)
	{
		for (size_t j = 0; j < _width; j++)
		{
			if (i % 2) //bottom row
			{
				p = YUVpixel(
					y[i * _width + j],
					(u[((i * _width + j) - _width) % 4] >> shift) and mask,
					(v[((i * _width + j) - _width) % 4] >> shift) and mask);
			}
			else //top row
			{
				p = YUVpixel(
					y[i * _width + j],
					(u[(i * _width + j) % 4] >> shift) and mask,
					(v[(i * _width + j) % 4] >> shift) and mask);
			}
			f->_pixels[i * _width + j] = p;

			shift -= 2;
			if (shift < 0) shift = 6;
		}
	}

	_frame = f;

	delete []y;
	delete []u;
	delete []v;

	if (_file.eof()) return false;

	return true;
}

bool YUVvideo::drawFrame(olc::PixelGameEngine* pge)
{
	for (size_t i = 0; i < _height; i++)
	{
		for (size_t j = 0; j < _width; j++)
		{
			YUVpixel yuvp = _frame->_pixels[i * _width + j];
			olc::Pixel p = yuvp.getRGB();
			pge->Draw(j, i, p);

		}
	}

	return false;
}

bool YUVvideo::error()
{
	return _error;
}

std::string YUVvideo::getFilename()
{
	return std::string(_filename);
}

int YUVvideo::getWidth()
{
	return _width;
}

int YUVvideo::getHeight()
{
	return _height;
}

int YUVvideo::getChromaSubsampling()
{
	return _chromaSubsampling;
}
YUVframe::YUVframe()
{
}
