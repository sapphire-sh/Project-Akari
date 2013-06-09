#include "stdafx.h"
#include <fstream>
#include "bitmap.h"
#include "terrain.h"

#define HEADER_SIZE 13

using akari::Bitmap;

void Bitmap::ImportBMP(const akari::Terrain &terr, const wchar_t *path) {

}

void Bitmap::ExportBMP(const akari::Terrain &terr, const wchar_t *path) {
	std::ofstream outp;
    outp.open(path, std::ios::out | std::ios::binary);
	
	int width = terr.GetWidth();
	int height = terr.GetHeight();

    //Usage
    //함수 주석 ㄱ
    for(int h=0; h<height; ++h) {
        for(int w=0; w<width; ++w) {
            //적절히 변환?
            //-1 ~ 1? 시행착오 ㄱㄱ
            int depth = terr.GetDepth(w, h) * 127 + 128 ;
        }
    }

	char padding = 0x00;

	outp << "BM";

	int filesize = 54 + 4 * 0x100 + (ceil(width / 4) * 4) * height;
	int header[HEADER_SIZE] = {filesize, 0, 1078, 40, width, height, 524289, 0, 6, 2834, 2834, 0, 0};

	for(int i = 0; i < HEADER_SIZE; ++i) {
		outp.write((char*) &header[i], sizeof(header[i]));
	}

	for(int i = 0; i < 0x100; ++i) {
		for(int j = 0; j < 3; ++j) {
			outp.write((char*) &i, sizeof(char));
		}
		outp.write((char*) &padding, sizeof(padding));
	}

	for(int i = 0; i < width; ++i) {
		for(int j = 0; j < height; ++j) {
			char color = terr.GetDepth(i, j);
			outp.write((char*) &color, sizeof(char));
		}
		for(int j = 0; j < (4 - (width % 4)); ++j) {
			outp.write((char*) &padding, sizeof(padding));
		}
	}

	outp.close();
}
