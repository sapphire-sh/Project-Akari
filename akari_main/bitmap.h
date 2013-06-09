#ifndef __BITMAP_H__
#define __BITMAP_H__

namespace akari {;

class Terrain;

class Bitmap {
public:
	void import(akari::Terrain terr);
	void export(akari::Terrain terr);
};

};

#endif