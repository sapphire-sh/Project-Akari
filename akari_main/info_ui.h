// Ŭnicode please
#ifndef __INFO_UI_H__
#define __INFO_UI_H__

class FTGLPixmapFont;
typedef std::unique_ptr<FTGLPixmapFont> FontPtr;

namespace akari {;

class Camera;
class Terrain;

class InfoUI {
public:
    InfoUI();
    ~InfoUI();

public:
    void DrawHelp();
    void DrawCameraInfo(const akari::Camera &camera);
    void DrawAxis();
    void DrawIsRotating(bool is_rotating);
    void DrawTerrainInfo(const akari::Terrain &terrain);

private:
    FontPtr font_;

private:
    //info string
    std::stringstream camera_pos_;
    std::stringstream terrain_size_;
};

};

#endif