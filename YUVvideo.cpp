#include "YUVvideo.h"
#include <iostream>


//==============================================================================================
YUVframe::YUVframe(int32_t width, int32_t height, int32_t chromaSubsampling)
{
	_width = width;
	_height = height;
	_chromaSubsampling = chromaSubsampling;

	_c = _chromaSubsampling % 10;
	_b = (_chromaSubsampling / 10) % 10;
	_a = (_chromaSubsampling / 100) % 10;

	_Y_size = _width * _height;
	_U_size = (_width / _b) * (_height / _b);
	_V_size = (_width / _b) * (_height / _b);

	this->_Y_pixels = new uint8_t[_Y_size];
	this->_U_pixels = new uint8_t[_U_size];
	this->_V_pixels = new uint8_t[_V_size];
}

YUVframe::~YUVframe()
{
	delete [] _Y_pixels;
	delete [] _U_pixels;
	delete [] _V_pixels;
}

void YUVframe::set(int32_t w, int32_t h, uint8_t y, uint8_t u, uint8_t v)
{
	if (w >= 0 && w <= _width && h >= 0 && h <= _height)
	{
		_Y_pixels[h * _width + w] = y;
		_U_pixels[(h / _b) * (_width / _b) + (w / _b)] = u;
		_V_pixels[(h / _b) * (_width / _b) + (w / _b)] = v;
	}
}

olc::Pixel YUVframe::getRGB(int32_t w, int32_t h)
{
	float R = _Y_pixels[h * _width + w] + 1.4075 * (_V_pixels[(h / _b) * (_width / _b) + (w / _b)] - 128);
	float G = _Y_pixels[h * _width + w] - 0.3455 * (_U_pixels[(h / _b) * (_width / _b) + (w / _b)] - 128) - (0.7169 * (_V_pixels[(h / _b) * (_width / _b) + (w / _b)] - 128));
	float B = _Y_pixels[h * _width + w] + 1.7790 * (_U_pixels[(h / _b) * (_width / _b) + (w / _b)] - 128);

	if (R < 0) { R = 0; } if (G < 0) { G = 0; } if (B < 0) { B = 0; }
	if (R > 255) { R = 255; } if (G > 255) { G = 255; } if (B > 255) { B = 255; }

	return olc::Pixel(R, G, B);
}

void YUVframe::operator=(const YUVframe& f)
{
	std::memcpy(this->_Y_pixels, f._Y_pixels, _width * _height * sizeof(uint8_t));
	std::memcpy(this->_U_pixels, f._U_pixels, (_width / _b) * (_height / _b) * sizeof(uint8_t));
	std::memcpy(this->_V_pixels, f._V_pixels, (_width / _b) * (_height / _b) * sizeof(uint8_t));
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
	_frame = new YUVframe(_width, _height, _chromaSubsampling);
}

YUVvideo::~YUVvideo()
{
	_file.close();
	delete _frame;
}

bool YUVvideo::readFrame()
{
	_file.read((char*)_frame->_Y_pixels, _frame->_Y_size);
	_file.read((char*)_frame->_U_pixels, _frame->_U_size);
	_file.read((char*)_frame->_V_pixels, _frame->_V_size);

	if (_file.eof()) return false;

	return true;
}

bool YUVvideo::drawFrame(olc::PixelGameEngine* pge)
{
	for (size_t h = 0; h < _height; h++)
	{
		for (size_t w = 0; w < _width; w++)
		{
			pge->Draw(w, h, _frame->getRGB(w, h));
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
