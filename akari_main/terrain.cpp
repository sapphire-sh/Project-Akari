// Ŭnicode please
#include "stdafx.h"
#include "terrain.h"

using akari::Terrain;

Terrain::Terrain(int width, int height) {

    //vertex, index init
    vertex_list_.resize((width + 1) * (height + 1));
    index_list_.resize(width * height);

    int idx = 0;
    for(int h=0; h<height + 1; ++h) {
        for(int w=0; w<width + 1; ++w) {
            /*
                (0, 0)      (w, 0)


                (0, h)      (w, h)
            */
            idx = (width + 1) * h + w;
            vertex_list_[idx].x = (-(width/2) + w);
            vertex_list_[idx].y = 0;
            vertex_list_[idx].z = (-(height/2) + h);
        }
    }

    for(int h=0; h<height; ++h) {
        for(int w=0; w<width; ++w) {
            idx = width * h + w;
            //quad index
            index_list_[idx]._1 = idx;
            index_list_[idx]._2 = idx + (width + 1);
            index_list_[idx]._3 = idx + (width + 1) + 1;
            index_list_[idx]._4 = idx + 1;
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
}