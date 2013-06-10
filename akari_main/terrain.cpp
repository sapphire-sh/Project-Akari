// Ŭnicode please
#include "stdafx.h"
#include "terrain.h"

using akari::Terrain;

Terrain::Terrain(int _width, int _height, int _depth) {
    Init(_width, _height, _depth);
}

Terrain::~Terrain() {

}

void akari::Terrain::Init(int _width, int _height, int _depth) {
     //vertex, index init
	width = _width;
	height = _height;
	depth = _depth;
    vertex_list_.resize((_width) * (_height));
    plane_index_list_.resize((_width - 1) * (_height - 1) * 2);
	outline_index_list_.resize((_width - 1) * (_height - 1) * 2);
	diagonal_index_list_.resize((_width - 1) * (_height - 1));
	diagonal_color_list_.resize(_width * _height);
	selected_index_list_.resize(4);
	plane_color_list_.resize(_width * _height);

    int idx = 0;
    for(int h=0; h<_height; ++h) {
        for(int w=0; w<_width ; ++w) {
            /*
                (0, 0)      (w, 0)


                (0, h)      (w, h)
            */
            vertex_list_[idx].x = (-(_width/2) + w) * 0.1f;
            vertex_list_[idx].y = (float) _depth;
            vertex_list_[idx].z = (-(_height/2) + h) * 0.1f;
			
			plane_color_list_[idx]._red = 0.0f;
			plane_color_list_[idx]._green = 0.5f*0.5f*((w%2)+(h%2));
			plane_color_list_[idx]._blue = 0.0f;
			plane_color_list_[idx]._alpha = 1.0f;

			diagonal_color_list_[idx]._red = 0.0f;
			diagonal_color_list_[idx]._green = 0.5f*0.5f*((w%2)+(h%2));
			diagonal_color_list_[idx]._blue = 0.0f;
			diagonal_color_list_[idx]._alpha = 1.0f;

			diagonal_color_list_[idx]._red = 0.5f;
			diagonal_color_list_[idx]._green = 0.5f;
			diagonal_color_list_[idx]._blue = 0.5f;
			diagonal_color_list_[idx]._alpha = 1.0f;
			idx++;
        }
    }

	idx=0;
    for(int h=0; h<_height-1; ++h) {
        for(int w=0; w<_width-1; ++w) {
            //plane index
            plane_index_list_[idx]._1 = h * _width + w;
            plane_index_list_[idx]._2 = (h + 1) * width + w;
            plane_index_list_[idx]._3 = h * width + (w + 1);

			//outline index
			outline_index_list_[idx]._1 = h * _width + w;
            outline_index_list_[idx]._2 = (h + 1) * _width + w;


			idx++;

			//plane_index
			plane_index_list_[idx]._1 = h * _width + (w + 1);
            plane_index_list_[idx]._2 = (h + 1) * _width + w;
            plane_index_list_[idx]._3 = (h + 1) * _width + (w + 1);

			//outline index
			outline_index_list_[idx]._1 = h * _width + w;
            outline_index_list_[idx]._2 = h * _width + (w + 1);

			idx++;
        }
    }
	idx = 0;
	for(int h=0; h<_height-1; ++h) {
        for(int w=0; w<_width-1; ++w) {
            //diagonal index
            diagonal_index_list_[idx]._1 = h * _width + w;
            diagonal_index_list_[idx]._2 = (h + 1) * _width + (w + 1);
			idx++;
        }
    }


	selected_index_list_[0]._1 = (width/2) * height + height/2;
	selected_index_list_[0]._2 = (width/2) * height + height/2 + 1;
	selected_index_list_[1]._1 = (width/2) * height + height/2 + 1;
	selected_index_list_[1]._2 = (width/2 + 1) * height + height/2 + 1;
	selected_index_list_[2]._1 = (width/2 + 1) * height + height/2 + 1;
	selected_index_list_[2]._2 = (width/2 + 1) * height + height/2;
	selected_index_list_[3]._1 = (width/2 + 1) * height + height/2;
	selected_index_list_[3]._2 = (width/2) * height + height/2;
}

void Terrain::Reset(int _width, int _height, int _depth) {
    VertexList().swap(vertex_list_);
    PlaneIndexList().swap(plane_index_list_);
    ColorList().swap(diagonal_color_list_);
    ColorList().swap(plane_color_list_);
    LineIndexList().swap(outline_index_list_);
    LineIndexList().swap(diagonal_index_list_);
    LineIndexList().swap(selected_index_list_);

    Init(_width, _height, _depth);
}

void Terrain::Draw(float elapsed, bool is_rotating = false) {
    glPushMatrix();
    glPushAttrib(GL_CURRENT_BIT);

	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, &vertex_list_[0]);
	
	glEnableClientState(GL_COLOR_ARRAY);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glShadeModel(GL_SMOOTH);
	glColorPointer(4, GL_FLOAT, 0, &plane_color_list_[0]);
    glLineWidth(0);
//    glColor4f(0.5, 0.5, 0.5, 1);
    glDrawElements(GL_TRIANGLES, plane_index_list_.size() * 3, GL_UNSIGNED_INT, &plane_index_list_[0]);
	glDisableClientState(GL_COLOR_ARRAY);

    glLineWidth(0.5);
    glColor4f(0, 0.5, 0, 1);
    glDrawElements(GL_LINES, outline_index_list_.size() * 2, GL_UNSIGNED_INT, &outline_index_list_[0]);
	
	glEnableClientState(GL_COLOR_ARRAY);
	glShadeModel(GL_FLAT);
	glColorPointer(4, GL_FLOAT, 0, &diagonal_color_list_[0]);
    glLineWidth(0.5);
    glDrawElements(GL_LINES, diagonal_index_list_.size() * 2, GL_UNSIGNED_INT, &diagonal_index_list_[0]);
	glDisableClientState(GL_COLOR_ARRAY);

    if(!is_rotating) {
	    glLineWidth(10);
        glColor4f(1, 0, 0, 1);
        glDrawElements(GL_LINES, selected_index_list_.size() * 2, GL_UNSIGNED_INT, &selected_index_list_[0]);
    }

	glDisableClientState(GL_VERTEX_ARRAY);
    glPopAttrib();
    glPopMatrix();
}

glm::vec3 findPlane(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3) {
	return glm::vec3((p2.y*p3.z - p2.z*p3.y) + p1.y*(p2.z - p3.z) + p1.z *(p3.y - p2.y),
			p1.x*(p3.z - p2.z) + (p2.z*p3.x - p2.x*p3.z) + p1.z *(p2.x - p3.x),
			p1.x*(p2.y - p3.y) + p1.y*(p3.x - p2.x) + (p2.x*p3.y - p2.y*p3.x));
}

float Terrain::isMet(glm::vec3 eye, glm::vec3 lookat, glm::vec3 plane, float d) {
	return (d - plane.x*eye.x - plane.y*eye.y - plane.z*eye.z) / (plane.x * (lookat.x-eye.x)+plane.y * (lookat.y-eye.y) + plane.z * (lookat.z - eye.z));
}

bool Terrain::isInTriangle(glm::vec3 point, glm::vec3 A, glm::vec3 B, glm::vec3 C) {
	glm::vec3 temp, temp2, line1, line2, line3;
	temp = B - A;
	temp2 = point - A;
	line1 = glm::cross(temp,temp2);
	temp = C - B;
	temp2 = point - B;
	line2 = glm::cross(temp,temp2);
	temp = A - C;
	temp2 = point - C;
	line3 = glm::cross(temp,temp2);

	if(line1.x*line2.x>=0&&line2.x*line3.x>=0&&line3.x*line1.x>=0) {
		if(line1.y*line2.y>=0&&line2.y*line3.y>=0&&line3.y*line1.y>=0) {
			if(line1.z*line2.z>=0&&line2.z*line3.z>=0&&line3.z*line1.z>=0) {
				return true;
			}
			return false;
		}
		return false;
	}
	return false;
}

void Terrain::setStartEnd (int *start, int *end,glm::vec3 eye, glm::vec3 lookat) {
	start[0]=eye.z * 10 + width/2;
	start[1]=eye.x * 10 + height/2;
	end[0]=lookat.z * 10 + width/2;;
	end[1]=lookat.x * 10 + height/2;
}

void Terrain::setQueue(int *start, int *end, int *queue, int *cnt) {
	int delta[2],j;
	float temp;
	*cnt=0;
	if(start[0]>=0&&start[0]<width-1&&start[1]>=0&&start[1]<height-1) {
		queue[0]=start[0];
		queue[1]=start[1];
		*cnt+=1;
	}

	if(start[0]<end[0])
		delta[0]=1;
	else
		delta[0]=-1;
	if(start[1]<end[1])
		delta[1]=1;
	else
		delta[1]=-1;

	j=start[1];
	for(int i=start[0];;) {
		if((i<0&&i+delta[0]<i)||(i>width-2&&i+delta[0]>i)||(j<0&&j+delta[1]<j)||(j>height-2&&j+delta[1]>j))
			break;
		i+=delta[0];
		if(i>=0&&i<width-1&&j>=0&&j<height-1) {
			queue[*cnt*2]=i;
			queue[*cnt*2+1]=j;
			*cnt+=1;
		}
		temp = (1.0f * (end[1]-start[1]))/(end[0]-start[0]) * (i-start[0]) + start[1];
		while((temp-j)*delta[1]>0) {
			j+=delta[1];
			if(i>=0&&i<width-1&&j>=0&&j<height-1) {
				queue[*cnt*2]=i;
				queue[*cnt*2+1]=j;
				*cnt+=1;
			}
		}
	}
	if(end[0]<0||end[0]>=width-1||end[1]<0||end[1]>=height-1)
		return;
	queue[*cnt*2]=end[0];
	queue[*cnt*2+1]=end[1];
	*cnt+=1;
}

void Terrain::Update(glm::vec3 eye, glm::vec3 lookat) {

	glm::vec3 tri[3];
	glm::vec3 plane, point;
	float temp;
	int start[2],end[2],i, j, *queue, cnt, selectedX, selectedY;
	int m[5][2] ={{0,0},{0,1},{0,-1},{1,0},{-1,0}};

	queue = (int*)malloc(sizeof(int)*(width*height)*2);
	setStartEnd(start,end,eye,lookat);
	setQueue(start,end,queue,&cnt);

	for(int k=0;k<cnt;k++) {
		for(int l=0;l<5;l++) {
			i = queue[k*2] + m[l][0];
			j = queue[k*2+1] + m[l][1];
//			i = queue[k*2];
//			j = queue[k*2+1];
			if(i<0||i>width-2||j<0||j>height-2)
				continue;
			tri[0] = vertex_list_[i * height + j];
			tri[1] = vertex_list_[i * height + j + 1];
			tri[2] = vertex_list_[(i+1) * height + j];
			plane = glm::cross(tri[2]-tri[0],tri[1]-tri[0]);
			if((temp=isMet(eye,lookat,plane,glm::dot(plane,tri[0])))>0) {
				point = eye + (lookat-eye) * temp;

				if(isInTriangle(point, tri[0], tri[1], tri[2])) {
					selectedX = i;
					selectedY = j;
					break;
				}
			}

			tri[0] = vertex_list_[(i + 1) * height + j + 1];
			plane = findPlane(tri[0], tri[1], tri[2]);
			if((temp=isMet(eye,lookat,plane,glm::dot(plane,tri[0])))>0) {
				point = eye + (lookat-eye) * temp;
				if(isInTriangle(point, tri[0], tri[1], tri[2])) {
					selectedX = i;
					selectedY = j;
					break;
				}
			}
		}
	}

	if(selectedX>=0&&selectedX<width-1&&selectedY>=0&&selectedY<height-1) {
		selected_index_list_[0]._1 = selectedX * height + selectedY;
		selected_index_list_[0]._2 = selectedX * height + selectedY + 1;
		selected_index_list_[1]._1 = selectedX * height + selectedY + 1;
		selected_index_list_[1]._2 = (selectedX + 1) * height + selectedY + 1;
		selected_index_list_[2]._1 = (selectedX + 1) * height + selectedY + 1;
		selected_index_list_[2]._2 = (selectedX + 1) * height + selectedY;
		selected_index_list_[3]._1 = (selectedX + 1) * height + selectedY;
		selected_index_list_[3]._2 = selectedX * height + selectedY;
	}

	delete queue;
}

void Terrain::Click() {
	int m[9][2] ={{-1,-1},{-1,0},{-1,1},{0,-1},{0,0},{0,1},{1,-1},{1,0},{1,1}},x,y,idx;
	glm::vec3 tri[3],plane, point;
	float temp;
	vertex_list_[selected_index_list_[0]._1].y-=0.001f;
	vertex_list_[selected_index_list_[1]._1].y-=0.001f;
	vertex_list_[selected_index_list_[2]._1].y-=0.001f;
	vertex_list_[selected_index_list_[3]._1].y-=0.001f;
	for(int i=0;i<9;i++) {
		x=(selected_index_list_[0]._1/height)+m[i][0];
		y=(selected_index_list_[0]._1%height)+m[i][1];
		if(x<0||x>width-2||y<0||y>height-2)
			continue;
		tri[0] = vertex_list_[x * height + y];
		tri[1] = vertex_list_[x * height + y + 1];
		tri[2] = vertex_list_[(x+1) * height + y];
		plane = glm::cross(tri[2]-tri[0],tri[1]-tri[0]);
		temp = glm::dot(plane,tri[0])-glm::dot(vertex_list_[(x+1) * height + y+1],plane);
		
		idx=(y+1)*width+x+1;
		if(temp<0.00000001f&&temp>-0.00000001f) {
			//plane color
			diagonal_color_list_[idx]._red = 0.0f;
			diagonal_color_list_[idx]._green = 0.5f*0.25f*(x%2)*(y%2);
			diagonal_color_list_[idx]._blue = 0.0f;
			diagonal_color_list_[idx]._alpha = 1.0f;

			diagonal_color_list_[idx]._red = 0.5f;
			diagonal_color_list_[idx]._green = 0.5f;
			diagonal_color_list_[idx]._blue = 0.5f;
			diagonal_color_list_[idx]._alpha = 1.0f;
		}
		else {
			//plane color
			diagonal_color_list_[idx]._red = 0.5f;
			diagonal_color_list_[idx]._green = 0.5f;
			diagonal_color_list_[idx]._blue = 0.5f;
			diagonal_color_list_[idx]._alpha = 1.0f;
		}
	}
}


const int akari::Terrain::GetWidth() const {
    return width;
}

const int akari::Terrain::GetHeight() const {
    return height;
}

//0 <= w < width, 0 <= h < height
//격자 수 x 점 수 o
const int akari::Terrain::GetDepth(int w, int h) const {
    return (int)(vertex_list_[width * h + w].y * 0x7F + 0x80);
}

void akari::Terrain::SetDepth(int w, int h, int d) {
	vertex_list_[width * h + w].y = ((d - 0x80) / (float)0x7F);
}