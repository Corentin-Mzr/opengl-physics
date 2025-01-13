#include "render_system.hpp"

/*
Class that will render the rendering of a scene
@param window: Window on which render the scene, as a std::shared_ptr<GLFWwindow>
*/
RenderSystem::RenderSystem(const std::shared_ptr<GLFWwindow> &window) : window(window)
{
}

// Render the scene
void RenderSystem::render()
{
}