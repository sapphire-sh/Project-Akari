#ifndef __BITMAP_H__
#define __BITMAP_H__

namespace akari {;

class Terrain;

class Bitmap {
public:
	void ImportBMP(const akari::Terrain &terr, const wchar_t *path);
	void ExportBMP(const akari::Terrain &terr, const wchar_t *path);
};

};

#endif