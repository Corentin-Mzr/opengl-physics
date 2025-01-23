#include "render_system.hpp"

/*
Class that will handle the rendering of a scene
@param shader: Shader to use
@param window: Window on which render the scene, as a std::shared_ptr<GLFWwindow>
@param entity_manager: Handles entity creation
*/
RenderSystem::RenderSystem(const unsigned shader,
                           const std::shared_ptr<GLFWwindow> window,
                           const std::shared_ptr<EntityManager> entity_manager) : shader_(shader),
                                                                                  window_(window),
                                                                                  entity_manager_(entity_manager)
{
    // Make sure we use the shader to find uniforms
    glUseProgram(shader_);
    pos_loc_ = glGetUniformLocation(shader_, "position");
    euler_loc_ = glGetUniformLocation(shader_, "euler");
    scale_loc_ = glGetUniformLocation(shader_, "scale");

    // Check if uniforms are found
    if (pos_loc_ == -1)
        std::cerr << "[RENDER SYSTEM ERROR] Uniform \"position\" not found\n";
    if (euler_loc_ == -1)
        std::cerr << "[RENDER SYSTEM ERROR] Uniform \"euler\" not found\n";
    if (scale_loc_ == -1)
        std::cerr << "[RENDER SYSTEM ERROR] Uniform \"scale\" not found\n";

    // Build meshes for use
    build_meshes();
}

// For cleanup
const std::unordered_map<unsigned, Mesh> &RenderSystem::get_meshes() const noexcept
{
    return meshes_;
}

// Render the scene
void RenderSystem::render()
{
    const auto &transform_components = entity_manager_->get_transforms();
    const auto &render_components = entity_manager_->get_renders();

    // Clear screen
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Draw entities
    for (const auto &[entity, mask] : entity_manager_->get_masks())
    {
        // If RenderComponent or TransformComponent does not exist, skip
        if (!(mask & static_cast<unsigned>(ComponentType::TRANSFORM)) || !(mask & static_cast<unsigned>(ComponentType::RENDER)))
            continue;

        // Else retrieve the components
        const TransformComponent &transform = transform_components.at(entity);
        const RenderComponent &render = render_components.at(entity);

        // If Mesh is not created, skip
        if (meshes_.find(static_cast<unsigned>(render.object_type)) == meshes_.end())
            continue;

        // Else retrieve the mesh
        const Mesh &mesh = meshes_.at(static_cast<unsigned>(render.object_type));

        // Data to send to create the model matrix
        glUniform3fv(pos_loc_, 1, glm::value_ptr(transform.position));
        glUniform3fv(euler_loc_, 1, glm::value_ptr(glm::radians(transform.eulers)));
        glUniform3fv(scale_loc_, 1, glm::value_ptr(transform.scale));

        // // Bind mesh and texture
        // glBindTexture(GL_TEXTURE_2D, render.material);

        // Draw
        glBindVertexArray(mesh.vao);
        glDrawArrays(GL_TRIANGLES, 0, mesh.vertex_count);
        // glDrawElements(GL_TRIANGLES, render.vertex_count, GL_UNSIGNED_INT, 0);
    }

    // Display
    glfwSwapBuffers(window_.get());
}

// Debug purpose only
void RenderSystem::simple_render()
{
    const Mesh &mesh = meshes_[0];

    // Clear screen
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Set uniforms
    glUniform3fv(pos_loc_, 1, glm::value_ptr(glm::vec3{0.0f, 0.0f, 0.0f}));
    glUniform3fv(euler_loc_, 1, glm::value_ptr(glm::radians(glm::vec3{0.0f, 0.0f, 0.0f})));
    glUniform3fv(scale_loc_, 1, glm::value_ptr(glm::vec3{1.0f, 1.0f, 1.0f}));

    // Draw
    glBindVertexArray(mesh.vao);
    glDrawArrays(GL_TRIANGLES, 0, mesh.vertex_count);

    // Display
    glfwSwapBuffers(window_.get());
}

// Build every mesh from the MeshFactory
void RenderSystem::build_meshes()
{
    std::cout << "[RENDER SYSTEM INFO] Building meshes\n";

    for (unsigned i = 0; i < OBJECT_TYPE_COUNT; ++i)
    {
        meshes_[i] = mesh_factory_.load_mesh(i);
        if (meshes_[i].vao == 0 || meshes_[i].vertex_count == 0)
        {
            std::cerr << "[RENDER SYSTEM ERROR] Failed to load mesh for ObjectType " << i << std::endl;
            meshes_.erase(i);
        }
        else
            std::cout << "[RENDER SYSTEM INFO] Mesh loaded for ObjectType " << i << std::endl;
    }
}