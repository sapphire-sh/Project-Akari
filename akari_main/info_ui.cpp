// Ŭnicode please
#include "stdafx.h"
#include "info_ui.h"

using akari::InfoUI;

InfoUI::InfoUI() {
    font_.reset(new FTGLPixmapFont("../res/font/NanumGothic.ttf"));
    if(font_->Error()) {
        throw(new std::exception);
    }
    font_->FaceSize(24);
}

InfoUI::~InfoUI() {

}

void InfoUI::DrawCameraInfo(const Camera &camera) {
    glPushAttrib(GL_CURRENT_BIT);
    //Draw blue text
    glPixelTransferf(GL_GREEN_BIAS, -1.0f);
    glPixelTransferf(GL_RED_BIAS, -1.0f);
    glPixelTransferf(GL_BLUE_BIAS, -1.0f);
    font_->Render("Hello World!Hello!", -1, FTPoint(0, WINDOW_HEIGHT - 30));
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