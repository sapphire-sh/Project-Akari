// Ŭnicode please
#include "stdafx.h"
#include "camera.h"

using akari::Camera;

Camera::Camera() : 
    eye_(10, 10, 10),
    lookat_(0, 0, 0),
    up_(0, 1, 0) {
    calculateUp();
}

Camera::~Camera() {

}

void Camera::SetEye(const glm::vec3 &eye) {
    eye_ = eye;
    calculateUp();
}

void Camera::SetEye(float x, float y, float z) {
    eye_.x = x;
    eye_.y = y;
    eye_.z = z;
    calculateUp();
}

const glm::vec3 &Camera::GetEye() const {
    return eye_;
}

void Camera::SetLookAt(const glm::vec3 &lookat) {

    const static glm::vec3 y_vec(0, 1, 0);
    glm::vec3 forward = lookat;
    forward -= eye_;
    if(glm::acos(glm::dot(forward, y_vec) / glm::length(forward)) < glm::radians(5.0f)) {
        return;
    }

    lookat_ = lookat;
    calculateUp();
}

void Camera::SetLookAt(float x, float y, float z) {
    glm::vec3 lookat(x, y, z);
    SetLookAt(lookat);
}

const glm::vec3 &Camera::GetLookAt() const {
    return lookat_;
}

const glm::vec3 &Camera::GetUp() {
    return up_;
}

void Camera::calculateUp() {
    const static glm::vec3 y_vec(0, 1, 0);
    glm::vec3 forward = lookat_;
    forward -= eye_;
    
    up_ = glm::cross(glm::cross(forward, y_vec), forward);
    if(glm::length(up_) < 0.001f) {
        up_.x = 1;
        up_.y = 0;
        up_.z = 0;
    }
    else {
        up_ = glm::normalize(up_);
    }

}

void Camera::Move(Direction dir) {

    const static float speed = 0.05f;

    glm::vec3 dir_vec = lookat_;
    dir_vec -= eye_;

    switch (dir) {
    case kDirLeft:
        dir_vec = glm::cross(up_, dir_vec);
        break;
    case kDirRight:
        dir_vec = glm::cross(dir_vec, up_);
        break;
    case kDirBackward:
        dir_vec *= -1;
        break;
    case kDirForward:
        break;
    case kDirUp:
        dir_vec = up_;
        break;
    case kDirDown:
        dir_vec = -up_;
        break;
    default:
        return;
    }
    
    dir_vec = glm::normalize(dir_vec);
    dir_vec *= speed;
    eye_ += dir_vec;
    lookat_ += dir_vec;
}


void Camera::Rotate(float roll_rad, float pitch_rad) {
    glm::vec3 dir_vec = lookat_;
    dir_vec -= eye_;

    glm::mat4 rotate_mat;
    rotate_mat = glm::rotate(rotate_mat, roll_rad, glm::cross(dir_vec, up_));
    rotate_mat = glm::rotate(rotate_mat, -pitch_rad, up_);

    glm::vec4 temp(dir_vec, 0);
    temp = rotate_mat * temp;
    SetLookAt(eye_.x + temp.x, eye_.y + temp.y, eye_.z + temp.z);
}

void Camera::Update() {
    //Camera mouse control
    static int x, y;
    static int w, h;

    glfwGetMousePos(&x, &y);
    glfwGetWindowSize(&w, &h);

    Rotate(-((float)(y - h/2) / h/2) * 100, ((float)(x - w/2) / w/2) * 100);

    //Camera keyboard control
    if(glfwGetKey('A') == GLFW_PRESS) {
        Move(akari::Camera::kDirLeft);
    }
    if(glfwGetKey('S') == GLFW_PRESS) {
        Move(akari::Camera::kDirBackward);
    }
    if(glfwGetKey('D') == GLFW_PRESS) {
        Move(akari::Camera::kDirRight);
    }
    if(glfwGetKey('W') == GLFW_PRESS) {
        Move(akari::Camera::kDirForward);
    }
    if(glfwGetKey('R') == GLFW_PRESS) {
        Move(akari::Camera::kDirUp);
    }
    if(glfwGetKey('F') == GLFW_PRESS) {
        Move(akari::Camera::kDirDown);
    }
    //top view
    if(glfwGetKey('Z') == GLFW_PRESS) {
        SetEye(0, 2, 0);
        SetLookAt(0, 0, 0);
    }

    //camera apply
    gluLookAt(eye_.x, eye_.y, eye_.z, lookat_.x, lookat_.y, lookat_.z, up_.x, up_.y, up_.z);
    glfwSetMousePos(w/2, h/2);
}
