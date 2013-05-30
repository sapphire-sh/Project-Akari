// Ŭnicode please
#ifndef __TERRAIN_H__
#define __TERRAIN_H__
class Terrain {
    typedef std::vector<glm::vec3> VertexList;
    struct _Plane_Index {
        unsigned int _1, _2, _3;
    };
	struct _Line_Index {
		unsigned int _1, _2;
	};
    typedef std::vector<_Plane_Index> PlaneIndexList;
	typedef std::vector<_Line_Index> LineIndexList;
	typedef std::vector<bool> BoolVector;

public:
    Terrain(int _width, int _height, int _depth);
    ~Terrain();

public:
    void Draw(float elapsed);

private:
    VertexList vertex_list_;
    PlaneIndexList plane_index_list_;
	LineIndexList outline_index_list_, diagonal_index_list_;
	BoolVector isntPlane;
	int width, height;	//of points
	int depth;
};
#endif

/*
class Terrain {
    typedef std::vector<glm::vec3> VertexList;
    struct _Index {
        unsigned int _1, _2, _3, _4;
    };
    typedef std::vector<_Index> IndexList;

public:
    Terrain(int width, int height);
    ~Terrain();

public:
    void Draw(float elapsed);

private:
    VertexList vertex_list_;
    IndexList index_list_;

};

#endif
*/