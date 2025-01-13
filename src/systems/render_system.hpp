#pragma once

#include <memory>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

/*
Class that will handle the rendering of a scene
@param window: Window on which render the scene, as a std::shared_ptr<GLFWwindow>
*/
class RenderSystem
{
public:
    RenderSystem() = default;
    RenderSystem(const std::shared_ptr<GLFWwindow> &window_ptr);
    RenderSystem(const RenderSystem &) = delete;

    // Render the scene
    void render();

private:
    std::weak_ptr<GLFWwindow> window;
};