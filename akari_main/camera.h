// Ŭnicode please
#ifndef __CAMERA_H__
#define __CAMERA_H__

namespace akari {;

class Camera {
public:
    enum Direction {
        kDirLeft,
        kDirRight,
        kDirForward,
        kDirBackward,
        kDirUp,
        kDirDown
    };

public:
    Camera();
    ~Camera();

public:
    void SetEye(const glm::vec3 &eye);
    void SetEye(float x, float y, float z);
    const glm::vec3 &GetEye() const;
    void SetLookAt(const glm::vec3 &lookat);
    void SetLookAt(float x, float y, float z);
    const glm::vec3 &GetLookAt() const;
    const glm::vec3 &GetUp();

    void Move(Direction dir);
    void Rotate(float roll_rad, float pitch_rad);

    void Update();

private:
    void calculateUp();

private:
    glm::vec3 eye_;
    glm::vec3 lookat_;
    glm::vec3 up_;
};

};

#endif