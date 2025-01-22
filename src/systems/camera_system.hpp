#pragma once

#include <memory>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

/*
Handle the view of the player
@param window: The window, as a shared_ptr
@param shader: Shader used
*/
class CameraSystem
{

public:
    CameraSystem() = default;
    CameraSystem(const unsigned shader, const std::shared_ptr<GLFWwindow> window);

    // Update the camera
    void update();

    /*
    Move the camera in space
    @param dpos: Linear displacement (from key inputs)
    @param is_vertical: True if space key or crouch key are pressed
    */
    void move(const glm::vec3 &dpos, const bool is_vertical, const bool is_horizontal);

    /*
    Orientate the camera
    @param deulers: Angular displacement (from mouse motion)
    */
    void spin(const glm::vec3 &deulers);

private:
    unsigned shader_ = 0;
    std::shared_ptr<GLFWwindow> window_ = nullptr;
    glm::vec3 position_{0.0f};
    glm::vec3 eulers_{0.0f};
    glm::vec3 forwards_{0.0f};
    glm::vec3 right_{0.0f}; 
    glm::vec3 up_{0.0f};
    glm::vec3 world_up_{0.0f};
    glm::mat4 projection_{1.0f};
    glm::mat4 view_proj_{1.0f};
    int view_proj_loc_ = 0;
};