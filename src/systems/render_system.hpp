#pragma once

#include <memory>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "ecs_manager.hpp"
#include "mesh_factory.hpp"

/*
Class that will handle the rendering of a scene
@param window: Window on which render the scene, as a std::shared_ptr<GLFWwindow>
@param ecs: ECS Manager
*/
class RenderSystem
{
public:
    RenderSystem() = default;
    RenderSystem(const unsigned shader, const std::shared_ptr<GLFWwindow> &window_ptr, const std::shared_ptr<ECSManager> &ecs);
    RenderSystem(const RenderSystem &) = delete;

    // Render the scene
    void render();

private:
    unsigned int shader = 0;
    std::shared_ptr<GLFWwindow> window = nullptr;
    std::shared_ptr<ECSManager> ecs = nullptr;

    int pos_loc = 0;
    int euler_loc = 0;
    int scale_loc = 0;

    MeshFactory mesh_factory;

    // Build every mesh from the MeshFactory
    void build_meshes();
};