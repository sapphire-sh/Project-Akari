// Ŭnicode please
#ifndef __TERRAIN_H__
#define __TERRAIN_H__

namespace akari {;

class Terrain {
    typedef std::vector<glm::vec3> VertexList;
    struct _Plane_Index {
        unsigned int _1, _2, _3;
    };
	struct _Line_Index {
		unsigned int _1, _2;
	};
	struct _Color {
		float _red, _green, _blue, _alpha;
	};
    typedef std::vector<_Plane_Index> PlaneIndexList;
	typedef std::vector<_Line_Index> LineIndexList;
	typedef std::vector<_Color> ColorList;

public:
    Terrain(int _width, int _height, int _depth);
    ~Terrain();

public:
    void Init(int _width, int _height, int _depth);
    void Reset(int _width, int _height, int _depth);

    void Draw(float elapsed, bool is_rotating);
	void Update(glm::vec3 eye, glm::vec3 lookat);
	float isMet(glm::vec3 eye, glm::vec3 lookat, glm::vec3 plane, float d);
	bool isInTriangle(glm::vec3 point, glm::vec3 A, glm::vec3 B, glm::vec3 C);
	void setStartEnd (int *start, int *end,glm::vec3 eye, glm::vec3 lookat);
	void setQueue(int *start, int *end, int *queue, int *cnt);
	void Click();

public:
    const int GetWidth() const;
    const int GetHeight() const;
	const float GetDepth(int width, int height) const;

private:
    VertexList vertex_list_;
    PlaneIndexList plane_index_list_;
	ColorList diagonal_color_list_, plane_color_list_;
	LineIndexList outline_index_list_, diagonal_index_list_,selected_index_list_;
	int width, height;	//of points
	int depth;
};

};

#endif