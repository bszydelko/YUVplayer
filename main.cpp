#define OLC_PGE_APPLICATION
#include "YUVvideo.h"
#include "YUVplayer.h"



int main(int argc, char* argv[])
{

	/*if (argc != 5)
	{
		std::cout << "Wrong parameters!" << std::endl;
		return EXIT_FAILURE;
	}
	std::string filename = argv[1];
	int32_t width = std::stoi(argv[2]);
	int32_t height = std::stoi(argv[3]);
	int32_t chromaSubsampling = std::stoi(argv[4]);*/

	std::string filename = "akiyo_qcif.yuv";
	int32_t width = 176;
	int32_t height = 144;
	int32_t chromaSubsampling = 420;

	std::cout << "Trying to open: " << std::endl;
	std::cout << "	Filename: " << filename << std::endl;
	std::cout << "	Width: " << width << std::endl;
	std::cout << "	Height: " << height << std::endl;
	std::cout << "	Chroma subsampling: " << chromaSubsampling << std::endl;

	

	YUVvideo video(filename, width, height, chromaSubsampling);
	if (video.error())
	{
		std::cout << "\nFile does not exist!" << std::endl;
		return EXIT_FAILURE;
	}
	else std::cout << "\nSuccess!" << std::endl;

	YUVplayer player(&video);

	
	
	int32_t video_radio = width / height;

	int32_t pixel_w = 1920 / width;
	int32_t pixel_h = 1080 / height;

	if (player.Construct(width, height, 4, 4))
		player.Start();
	return 0;
}