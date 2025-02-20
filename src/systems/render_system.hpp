#pragma once

#include <memory>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "entity_manager.hpp"
#include "mesh_factory.hpp"

/*
Class that will handle the rendering of a scene
@param shader: Shader to use
@param window: Window on which render the scene, as a std::shared_ptr<GLFWwindow>
@param entity_manager: Handles entity creation
*/
class RenderSystem
{
public:
    RenderSystem() = default;
    RenderSystem(const unsigned shader, const std::shared_ptr<GLFWwindow> window_ptr, const std::shared_ptr<EntityManager> entity_manager);

    // Render the scene
    void render();

    // Debug purpose only
    void simple_render();

    // For cleanup
    const std::unordered_map<unsigned, Mesh>& get_meshes() const noexcept;

private:
    unsigned int shader_ = 0;
    std::shared_ptr<GLFWwindow> window_ = nullptr;
    std::shared_ptr<EntityManager> entity_manager_ = nullptr;

    int pos_loc_ = 0;
    int euler_loc_ = 0;
    int scale_loc_ = 0;

    MeshFactory mesh_factory_;

    // Build every mesh from the MeshFactory
    void build_meshes();

    std::unordered_map<unsigned, Mesh> meshes_;
};