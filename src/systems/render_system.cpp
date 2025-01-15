#include "render_system.hpp"

/*
Class that will render the rendering of a scene
@param window: Window on which render the scene, as a std::shared_ptr<GLFWwindow>
@param ecs: ECS Manager
*/
RenderSystem::RenderSystem(const unsigned shader,
                           const std::shared_ptr<GLFWwindow> &window,
                           const std::shared_ptr<ECSManager> &ecs) : shader(shader), window(window), ecs(ecs)
{
    // glUseProgram(shader);
    pos_loc = glGetUniformLocation(shader, "position");
    euler_loc = glGetUniformLocation(shader, "euler");
    scale_loc = glGetUniformLocation(shader, "scale");

    // std::cout << pos_loc << " " << euler_loc << " " << scale_loc << std::endl;

    // TODO: ADD THIS
    // build_meshes();
}

// Render the scene
void RenderSystem::render()
{
    // glUseProgram(shader);

    auto &transform_components = ecs->get_transforms();
    auto &render_components = ecs->get_renders();
    const auto &meshes = mesh_factory.get_meshes();

    // Clear screen
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Draw entities
    for (const auto &[entity, mask] : ecs->get_masks())
    {
        // Check for RenderComponent and TransformComponent
        if ((mask & static_cast<unsigned>(ComponentType::TRANSFORM)) &&
            mask & static_cast<unsigned>(ComponentType::RENDER))
        {
            const TransformComponent &transform = transform_components[entity];
            const RenderComponent &render = render_components[entity];
            const Mesh mesh = meshes.at(static_cast<unsigned>(render.object_type));

            // Data to send to create the model matrix
            glUniform3fv(pos_loc, 1, glm::value_ptr(transform.position));
            glUniform3fv(euler_loc, 1, glm::value_ptr(glm::radians(transform.eulers)));
            glUniform3fv(scale_loc, 1, glm::value_ptr(transform.scale));

            // // Bind mesh and texture
            // glBindTexture(GL_TEXTURE_2D, render.material);

            glBindVertexArray(mesh.vao);
            glDrawArrays(GL_TRIANGLES, 0, mesh.vertex_count);
            // glDrawElements(GL_TRIANGLES, render.vertex_count, GL_UNSIGNED_INT, 0);
        }
    }

    // Display
    glfwSwapBuffers(window.get());
}

// Build every mesh from the MeshFactory
void RenderSystem::build_meshes()
{
    for (size_t i = 0; i < OBJECT_TYPE_COUNT; ++i)
    {
        Mesh mesh = mesh_factory.load_mesh(i);
    }
}