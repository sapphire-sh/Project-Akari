// Ŭnicode please
#include "stdafx.h"
#include "terrain.h"

Terrain::Terrain(int _width, int _height, int _depth) {

    //vertex, index init
	width = _width;
	height = _height;
	depth = _depth;
    vertex_list_.resize((_width) * (_height));
    plane_index_list_.resize((_width - 1) * (_height - 1) * 2);
	outline_index_list_.resize((_width - 1) * (_height - 1) * 2);
	diagonal_index_list_.resize((_width - 1) * (_height - 1));
	isntPlane.resize((_width - 1) * (_height - 1));

    int idx = 0;
    for(int h=0; h<_height; ++h) {
        for(int w=0; w<_width ; ++w) {
            /*
                (0, 0)      (w, 0)


                (0, h)      (w, h)
            */
			if(h==_height-1&&w==_width-1)
				h=_height-1;
            vertex_list_[idx].x = (-(_width/2) + w) * 0.1f;
            vertex_list_[idx].y = _depth;
            vertex_list_[idx].z = (-(_height/2) + h) * 0.1f;
			idx++;
        }
    }

	idx=0;
    for(int h=0; h<_height-1; ++h) {
        for(int w=0; w<_width-1; ++w) {
            //quad index
            plane_index_list_[idx]._1 = h * _height + w;
            plane_index_list_[idx]._2 = (h + 1) * _height + w;
            plane_index_list_[idx]._3 = h * _height + (w + 1);
			idx++;
			plane_index_list_[idx]._1 = h * _height + (w + 1);
            plane_index_list_[idx]._2 = (h + 1) * _height + w;
            plane_index_list_[idx]._3 = (h + 1) * _height + (w + 1);
			idx++;
        }
    }
	idx=0;
	for(int h=0; h<_height-1; ++h) {
        for(int w=0; w<_width-1; ++w) {
            //quad index
            outline_index_list_[idx]._1 = h * _height + w;
            outline_index_list_[idx]._2 = (h + 1) * _height + w;
			idx++;
			outline_index_list_[idx]._1 = h * _height + w;
            outline_index_list_[idx]._2 = h * _height + (w + 1);
			idx++;
        }
    }
	idx = 0;
	for(int h=0; h<_height-1; ++h) {
        for(int w=0; w<_width-1; ++w) {
            //quad index
            diagonal_index_list_[idx]._1 = h * _height + w;
            diagonal_index_list_[idx]._2 = (h + 1) * _height + (w + 1);
			isntPlane[idx] = false;
			idx++;
        }
    }
}

Terrain::~Terrain() {

}

void Terrain::Draw(float elapsed) {
    glPushMatrix();
    glPushAttrib(GL_CURRENT_BIT);
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, &vertex_list_[0]);

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glLineWidth(0);
    glColor4f(0.5, 0.5, 0.5, 1);
    glDrawElements(GL_TRIANGLES, plane_index_list_.size() * 3, GL_UNSIGNED_INT, &plane_index_list_[0]);

    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glLineWidth(0.5);
    glColor4f(0, 0, 0, 1);
    glDrawElements(GL_LINES, outline_index_list_.size() * 2, GL_UNSIGNED_INT, &outline_index_list_[0]);

	int idx =0;
	for(int i=0; i<width - 1; i++) {
		for(int j=0; j<height - 1; j++) {
			if(isntPlane[idx]) {
				glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
				glLineWidth(0.5);
				glColor4f(0, 0, 0, 1);
				glDrawElements(GL_LINES, 2, GL_UNSIGNED_INT, &diagonal_index_list_[(i * (height-1) + j)]);
			}
		}
	}
    
	glDisableClientState(GL_VERTEX_ARRAY);
    glPopAttrib();
    glPopMatrix();
}
/*
Terrain::Terrain(int width, int height) {

    //vertex, index init
    vertex_list_.resize((width + 1) * (height + 1));
    index_list_.resize(width * height);

    int idx = 0;
    for(int h=0; h<height + 1; ++h) {
        for(int w=0; w<width + 1; ++w) {
            
            //    (0, 0)      (w, 0)


            //    (0, h)      (w, h)
            
            idx = h * height + w;
            vertex_list_[idx].x = (-(width/2) + w) * 0.1f;
            vertex_list_[idx].y = 0;
            vertex_list_[idx].z = (-(height/2) + h) * 0.1f;
        }
    }

    for(int h=0; h<height; ++h) {
        for(int w=0; w<width; ++w) {
            idx = h * height + w;
            //quad index
            index_list_[idx]._1 = h * height + w;
            index_list_[idx]._2 = (h + 1) * height + w;
            index_list_[idx]._3 = (h + 1) * height + (w + 1);
            index_list_[idx]._4 = h * height + (w + 1);
        }
    }
}

Terrain::~Terrain() {

}

void Terrain::Draw(float elapsed) {
    glPushMatrix();
    glPushAttrib(GL_CURRENT_BIT);
    glEnableClientState(GL_VERTEX_ARRAY);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glLineWidth(0.5);
    glColor4f(0, 0, 0, 1);
    glVertexPointer(3, GL_FLOAT, 0, &vertex_list_[0]);
    glDrawElements(GL_QUADS, index_list_.size() * 4, GL_UNSIGNED_INT, &index_list_[0]);
    glDisableClientState(GL_VERTEX_ARRAY);
    glPopAttrib();
    glPopMatrix();
}*/