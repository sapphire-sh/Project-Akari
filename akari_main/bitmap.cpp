#include "fstream"
#include "bitmap.h"
#include "terrain.h"

#define HEADER_SIZE 13

using akari::Bitmap;

void import(akari::Terrain terr) {

}

void export(akari::Terrain terr) {
	std::ofstream outp;
	outp.open("export.bmp");
	
	int width = terr.GetWidth();
	int height = terr.GetHeight();

	int filesize = 54 + 4 * width * height;

	int header[HEADER_SIZE] = {filesize, 0, 54, 40, width, height, 1572865, 0, 0, 0, 0, 0, 0};

	outp << "BM";
	for(int i = 0; i < HEADER_SIZE; ++i) {
		outp.write((char*) &header[i], sizeof(header[i]));
	}

	for(int i = 0; i < width; ++i) {
		for(int j = 0; j < height; ++j) {
			char a = 0xff;
			char r = 0x7f;
			char g = 0x01;
			char b = 0xff;
			outp.write((char*) &a, sizeof(a));
			outp.write((char*) &g, sizeof(g));
			outp.write((char*) &r, sizeof(r));
			outp.write((char*) &b, sizeof(b));
			outp.write((char*) &g, sizeof(g));
			outp.write((char*) &r, sizeof(r));
		}
	}

	outp.close();
}

