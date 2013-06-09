// Ŭnicode please
#include "stdafx.h"
#include "info_ui.h"
#include "camera.h"
#include "terrain.h"

using akari::InfoUI;
using akari::Terrain;

InfoUI::InfoUI() {
    font_.reset(new FTGLPixmapFont("../res/font/NanumGothic.ttf"));
    if(font_->Error()) {
        assert(0 && "font init error");
    }
    font_->FaceSize(24);
}

InfoUI::~InfoUI() {

}

void InfoUI::DrawCameraInfo(const akari::Camera &camera) {
    glPushAttrib(GL_CURRENT_BIT);
    glPixelTransferf(GL_GREEN_BIAS, -1.0f);
    glPixelTransferf(GL_RED_BIAS, -1.0f);
    glPixelTransferf(GL_BLUE_BIAS, -1.0f);
    font_->FaceSize(24);
    FTPoint end_pos = font_->Render("Camera Pos : ", -1, FTPoint(8, WINDOW_HEIGHT - 24));

    //camera position
    camera_pos_.str("");
    camera_pos_ << "(" << camera.GetEye().x << ", " << camera.GetEye().y << ", " << camera.GetEye().z << ")";

    font_->Render(camera_pos_.str().c_str(), -1, end_pos);
    glPopAttrib();

}

void InfoUI::DrawAxis() {
    const static float length = 1000;

    glPushMatrix();
    glPushAttrib(GL_CURRENT_BIT);

    glLineWidth(2.0f);

    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glBegin(GL_LINES);
    //x
    glColor4f(1, 0, 0, 1);
    glVertex3f(-length/2, 0, 0);
    glVertex3f(length/2, 0, 0);

    //y
    glColor4f(0, 1, 0, 1);
    glVertex3f(0, -length/2, 0);
    glVertex3f(0, length/2, 0);

    //z
    glColor4f(0, 0, 1, 1);
    glVertex3f(0, 0, -length/2);
    glVertex3f(0, 0, length/2);

    glEnd();

    glPopAttrib();
    glPopMatrix();
}

void akari::InfoUI::DrawIsRotating(bool is_rotating) {
    FTPoint end_pos = font_->Render("Rotate : ", -1, FTPoint(8, WINDOW_HEIGHT - 48));
    if(is_rotating) {
        font_->Render("Y", -1, end_pos);
    }
    else {
        font_->Render("N", -1, end_pos);
    }
}

void akari::InfoUI::DrawHelp() {
    font_->FaceSize(15);
    font_->Render("Z : Top View", -1, FTPoint(8, 60));
    font_->Render("X : Front View", -1, FTPoint(8, 45));
    font_->Render("C : Quarter View", -1, FTPoint(8, 30));
    font_->Render("M : Rotate", -1, FTPoint(8, 15));
}

void akari::InfoUI::DrawTerrainInfo(const akari::Terrain &terrain) {
    font_->FaceSize(24);
    FTPoint end_pos = font_->Render("Terrain Size : ", -1, FTPoint(8, WINDOW_HEIGHT - 72));
    terrain_size_.str("");
    terrain_size_ << terrain.GetWidth() << " x " << terrain.GetHeight();
    font_->Render(terrain_size_.str().c_str(), -1, end_pos);
}