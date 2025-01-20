#include "camera_system.hpp"

#include <iostream>

CameraSystem::CameraSystem(const unsigned shader, const std::shared_ptr<GLFWwindow> window) : shader(shader), window(window)
{
    // To compute aspect ratio
    int width, height;
    glfwGetWindowSize(window.get(), &width, &height);

    // Initial position - orientation - direction - world up
    position = glm::vec3{0.0f, 0.0f, 0.0f};
    eulers = glm::vec3{0.0f, 0.0f, 0.0f};
    forwards = glm::vec3{1.0f, 0.0f, 0.0f};
    world_up = glm::vec3{0.0f, 1.0f, 0.0f};

    // Will be computed later
    right = glm::vec3{0.0f, 0.0f, 0.0f};
    up = glm::vec3{0.0f, 0.0f, 0.0f};

    // Compute projection matrix
    constexpr float fovy = glm::radians(90.0f);
    const float aspect_ratio = static_cast<float>(width) / static_cast<float>(height);
    constexpr float near = 0.1f;
    constexpr float far = 100.0f;
    projection = glm::perspective(fovy, aspect_ratio, near, far);

    // Get uniform location in shader, make sure we use the shader
    glUseProgram(shader);
    view_proj_loc = glGetUniformLocation(shader, "view_projection");

    if (view_proj_loc == -1)
        std::cerr << "[CAMERA SYSTEM ERROR] Uniform \"view_projection\" not found\n";
}

// Update the camera
void CameraSystem::update()
{
    const float theta = glm::radians(eulers.y);
    const float phi = glm::radians(eulers.z);

    forwards = {
        glm::cos(theta) * glm::cos(phi),
        glm::sin(phi),
        glm::sin(theta) * glm::cos(phi),
    };
    forwards = glm::normalize(forwards);
    right = glm::normalize(glm::cross(forwards, world_up));
    up = glm::normalize(glm::cross(right, forwards));

    // ViewProjection matrix
    view_proj = projection * glm::lookAt(position, position + forwards, up);

    // Send to the shader
    glUniformMatrix4fv(view_proj_loc, 1, GL_FALSE, glm::value_ptr(view_proj));
}

/*
Move the camera in space
@param dpos: Linear displacement (from key inputs)
@param is_vertical: True if space key or crouch key are pressed
*/
void CameraSystem::move(const glm::vec3 &dpos, const bool is_vertical, const bool is_horizontal)
{
    glm::vec3 up{0.0f, 0.0f, 0.0f};
    if (is_vertical && !is_horizontal)
        up = world_up;
    else if (is_vertical && is_horizontal)
        up = glm::normalize(this->up + world_up);
    else if (is_horizontal)
        up = this->up;

    position += forwards * dpos.x;
    position += up * dpos.y;
    position += right * dpos.z;
}

/*
Orientate the camera
@param deulers: Angular displacement (from mouse motion)
*/
void CameraSystem::spin(const glm::vec3 &deulers)
{
    eulers.y += deulers.y;

    if (eulers.y > 360.0f)
        eulers.y -= 360.0f;
    if (eulers.y < 0.0f)
        eulers.y += 360.0f;
    
    eulers.z = std::min(89.0f, std::max(-89.0f, eulers.z + deulers.z));
}