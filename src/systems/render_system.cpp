#include "render_system.hpp"

/*
Class that will handle the rendering of a scene
@param shader: Shader to use
@param window: Window on which render the scene, as a std::shared_ptr<GLFWwindow>
@param entity_manager: Handles entity creation
*/
RenderSystem::RenderSystem(const unsigned shader,
                           const std::shared_ptr<GLFWwindow> &window,
                           const std::shared_ptr<EntityManager> &entity_manager) : shader(shader),
                                                                                   window(window),
                                                                                   entity_manager(entity_manager)
{
    // Make sure we use the shader to find uniforms
    glUseProgram(shader);
    pos_loc = glGetUniformLocation(shader, "position");
    euler_loc = glGetUniformLocation(shader, "euler");
    scale_loc = glGetUniformLocation(shader, "scale");

    // Check if uniforms are found
    if (pos_loc == -1)
        std::cerr << "[RENDER SYSTEM ERROR] Uniform \"position\" not found\n";
    if (euler_loc == -1)
        std::cerr << "[RENDER SYSTEM ERROR] Uniform \"euler\" not found\n";
    if (scale_loc == -1)
        std::cerr << "[RENDER SYSTEM ERROR] Uniform \"scale\" not found\n";

    // Build meshes for use
    build_meshes();
}

RenderSystem::~RenderSystem()
{
    // for (auto [i, mesh]: meshes)
    // {
    //     glDeleteVertexArrays(1, &mesh.vao);
    //     glDeleteBuffers(1, &mesh.vbo);
    // }
}

// For cleanup
const std::unordered_map<unsigned, Mesh> &RenderSystem::get_meshes() const
{
    return meshes;
}

// Render the scene
void RenderSystem::render()
{
    auto &transform_components = entity_manager->get_transforms();
    auto &render_components = entity_manager->get_renders();

    // Clear screen
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Draw entities
    for (const auto &[entity, mask] : entity_manager->get_masks())
    {
        // Check for RenderComponent and TransformComponent
        if ((mask & static_cast<unsigned>(ComponentType::TRANSFORM)) &&
            mask & static_cast<unsigned>(ComponentType::RENDER))
        {
            const TransformComponent &transform = transform_components[entity];
            const RenderComponent &render = render_components[entity];
            const Mesh &mesh = meshes.at(static_cast<unsigned>(render.object_type));

            // Data to send to create the model matrix
            glUniform3fv(pos_loc, 1, glm::value_ptr(transform.position));
            glUniform3fv(euler_loc, 1, glm::value_ptr(glm::radians(transform.eulers)));
            glUniform3fv(scale_loc, 1, glm::value_ptr(transform.scale));

            // // Bind mesh and texture
            // glBindTexture(GL_TEXTURE_2D, render.material);

            // Draw
            glBindVertexArray(mesh.vao);
            glDrawArrays(GL_TRIANGLES, 0, mesh.vertex_count);
            // glDrawElements(GL_TRIANGLES, render.vertex_count, GL_UNSIGNED_INT, 0);
        }
    }

    // Display
    glfwSwapBuffers(window.get());
}

// Debug purpose only
void RenderSystem::simple_render()
{
    const Mesh &mesh = meshes[0];

    // Clear screen
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Set uniforms
    glUniform3fv(pos_loc, 1, glm::value_ptr(glm::vec3{0.0f, 0.0f, 0.0f}));
    glUniform3fv(euler_loc, 1, glm::value_ptr(glm::radians(glm::vec3{0.0f, 0.0f, 0.0f})));
    glUniform3fv(scale_loc, 1, glm::value_ptr(glm::vec3{1.0f, 1.0f, 1.0f}));

    // Draw
    glBindVertexArray(mesh.vao);
    glDrawArrays(GL_TRIANGLES, 0, mesh.vertex_count);

    // Display
    glfwSwapBuffers(window.get());
}

// Build every mesh from the MeshFactory
void RenderSystem::build_meshes()
{
    std::cout << "[RENDER SYSTEM INFO] Building meshes\n";

    for (size_t i = 0; i < OBJECT_TYPE_COUNT; ++i)
    {
        meshes[i] = mesh_factory.load_mesh(i);
        if (meshes[i].vao == 0 || meshes[i].vertex_count == 0)
        {
            std::cerr << "[RENDER SYSTEM ERROR] Failed to load mesh for ObjectType " << i << std::endl;
            meshes.erase(i);
        }
        else
            std::cout << "[RENDER SYSTEM INFO] Mesh loaded for ObjectType " << i << std::endl;
    }
}