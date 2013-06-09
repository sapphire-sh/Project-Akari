// Ŭnicode please
#ifndef __INFO_UI_H__
#define __INFO_UI_H__

class Camera;
class FTGLPixmapFont;
typedef std::unique_ptr<FTGLPixmapFont> FontPtr;

namespace akari {;

class InfoUI {
public:
    InfoUI();
    ~InfoUI();

public:
    void DrawCameraInfo(const Camera &camera);
    void DrawAxis();

private:
    FontPtr font_;
};

};

#endif