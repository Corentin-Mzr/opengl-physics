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
    CameraSystem(const unsigned shader, const std::shared_ptr<GLFWwindow> &window);
    CameraSystem(CameraSystem &) = delete;

    // Update the camera
    void update();

    /*
    Move the camera in space
    @param dpos: Linear displacement (from key inputs)
    */
    void move(const glm::vec3 &dpos);

    /*
    Orientate the camera
    @param deulers: Angular displacement (from mouse motion)
    */
    void spin(const glm::vec3 &deulers);

private:
    unsigned shader = 0;
    std::shared_ptr<GLFWwindow> window = nullptr;
    glm::vec3 position, eulers, forwards, right, up, world_up;
    glm::mat4 projection;
    glm::mat4 view_proj;
    int view_proj_loc = 0;
};