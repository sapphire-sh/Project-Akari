// Ŭnicode please
#ifndef __TERRAIN_H__
#define __TERRAIN_H__

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