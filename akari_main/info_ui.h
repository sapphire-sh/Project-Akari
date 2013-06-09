// Ŭnicode please
#ifndef __INFO_UI_H__
#define __INFO_UI_H__

class FTGLPixmapFont;
typedef std::unique_ptr<FTGLPixmapFont> FontPtr;

namespace akari {;

class Camera;

class InfoUI {
public:
    InfoUI();
    ~InfoUI();

public:
    void DrawCameraInfo(const akari::Camera &camera);
    void DrawAxis();

private:
    FontPtr font_;

private:
    //info string
    std::stringstream camera_pos_;
};

};

#endif