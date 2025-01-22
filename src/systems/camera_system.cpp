#include "camera_system.hpp"

#include <iostream>

CameraSystem::CameraSystem(const unsigned shader, const std::shared_ptr<GLFWwindow> window) : shader_(shader), window_(window)
{
    // To compute aspect ratio
    int width, height;
    glfwGetWindowSize(window.get(), &width, &height);

    // Initial position - orientation - direction - world up
    position_ = glm::vec3{0.0f, 0.0f, 0.0f};
    eulers_ = glm::vec3{0.0f, 0.0f, 0.0f};
    forwards_ = glm::vec3{1.0f, 0.0f, 0.0f};
    world_up_ = glm::vec3{0.0f, 1.0f, 0.0f};

    // Will be computed later
    right_ = glm::vec3{0.0f, 0.0f, 0.0f};
    up_ = glm::vec3{0.0f, 0.0f, 0.0f};

    // Compute projection matrix
    constexpr float fovy = glm::radians(90.0f);
    const float aspect_ratio = static_cast<float>(width) / static_cast<float>(height);
    constexpr float near = 0.1f;
    constexpr float far = 100.0f;
    projection_ = glm::perspective(fovy, aspect_ratio, near, far);

    // Get uniform location in shader, make sure we use the shader
    glUseProgram(shader_);
    view_proj_loc_ = glGetUniformLocation(shader_, "view_projection");

    if (view_proj_loc_ == -1)
        std::cerr << "[CAMERA SYSTEM ERROR] Uniform \"view_projection\" not found\n";
}

// Update the camera
void CameraSystem::update()
{
    const float theta = glm::radians(eulers_.y);
    const float phi = glm::radians(eulers_.z);

    forwards_ = {
        glm::cos(theta) * glm::cos(phi),
        glm::sin(phi),
        glm::sin(theta) * glm::cos(phi),
    };
    forwards_ = glm::normalize(forwards_);
    right_ = glm::normalize(glm::cross(forwards_, world_up_));
    up_ = glm::normalize(glm::cross(right_, forwards_));

    // ViewProjection matrix
    view_proj_ = projection_ * glm::lookAt(position_, position_ + forwards_, up_);

    // Send to the shader
    glUniformMatrix4fv(view_proj_loc_, 1, GL_FALSE, glm::value_ptr(view_proj_));
}

/*
Move the camera in space
@param dpos: Linear displacement (from key inputs)
@param is_vertical: True if space key or crouch key are pressed
*/
void CameraSystem::move(const glm::vec3 &dpos, const bool is_vertical, const bool is_horizontal)
{
    glm::vec3 cam_up{0.0f, 0.0f, 0.0f};
    if (is_vertical && !is_horizontal)
        cam_up = world_up_;
    else if (is_vertical && is_horizontal)
        cam_up = glm::normalize(up_ + world_up_);
    else if (is_horizontal)
        cam_up = up_;

    position_ += forwards_ * dpos.x;
    position_ += cam_up * dpos.y;
    position_ += right_ * dpos.z;
}

/*
Orientate the camera
@param deulers: Angular displacement (from mouse motion)
*/
void CameraSystem::spin(const glm::vec3 &deulers)
{
    eulers_.y += deulers.y;

    if (eulers_.y > 360.0f)
        eulers_.y -= 360.0f;
    if (eulers_.y < 0.0f)
        eulers_.y += 360.0f;
    
    eulers_.z = std::min(89.0f, std::max(-89.0f, eulers_.z + deulers.z));
}