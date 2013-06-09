// Ŭnicode please
#include "stdafx.h"
#include "info_ui.h"
#include "camera.h"

using akari::InfoUI;

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
    FTPoint end_pos = font_->Render("Camera Pos : ", -1, FTPoint(0, WINDOW_HEIGHT - 24));

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