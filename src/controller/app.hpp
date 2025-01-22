#pragma once

#include <stdexcept>
#include <string>
#include <memory>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "physics_system.hpp"
#include "render_system.hpp"
#include "camera_system.hpp"

#include "shader_factory.hpp"
#include "mesh_factory.hpp"

#include "entity_manager.hpp"

/* 
App class that will create a resizable window
@param width: Width of the window
@param height: Height of the window
@param title: Title of the window
*/
class App
{
public:
    App(const unsigned width, const unsigned height, const char* title);
    App(const App&) = delete;
    App& operator=(const App&) = delete;
    App& operator=(App&& other) = delete;
    ~App();

    // Run the app
    void run();

private:
    std::shared_ptr<GLFWwindow> window_ = nullptr;
    unsigned width_ = 0, height_ = 0;
    const char* title_ = nullptr;
    unsigned shader_ = 0;
    bool keys_[1024] = {false};
    double xpos_ = 0.0, ypos_ = 0.0, xoffset_ = 0.0, yoffset_ = 0.0;
    bool first_motion_ = true;
    bool glfw_initialized_ = false;
    bool glad_initialized_ = false;
    RenderSystem render_system_;
    PhysicsSystem physics_system_;
    CameraSystem camera_system_;
    ShaderFactory shader_factory_;
    std::shared_ptr<EntityManager> entity_manager_ = nullptr;

    glm::vec3 dpos{0.0f, 0.0f, 0.0f};
    glm::vec3 deulers{0.0f, 0.0f, 0.0f};
    float speed_factor = 1.0f;
    float mouse_sensivity = 20.0f;
    bool is_vertical = false;
    bool is_horizontal = false;

    // Initialize GLFW, if fail throw a std::runtime_error exception
    void setup_glfw();

    // Create the window, if fail throw a std::runtime_error exception
    void setup_window();

    // Load GLAD, if fail throw a std::runtime_error exception
    void setup_glad();

    // Define some OpenGL parameters (viewport, background color, ...)
    void setup_opengl();

    // Define callback functions
    void setup_callbacks();

    // Set up some systems
    void setup_systems();

    // Define everything in the scene
    void setup_scene();

    /*
    Process input each frame
    @param dt: Delta time
    */ 
    void process_input(const double dt);

    /*
    Handle window resizing
    @param window: Pointer to the window
    @param width: Width of the window
    @param height: Height of the window
    */
    static void framebuffer_size_callback(GLFWwindow *window, int width, int height);

    /*
    Handle key inputs
    @param window: Pointer to the window
    @param key: Key code representing the key (ex: GLFW_KEY_...)
    @param scancode: Hardware code that identifies the physical key.
    @param action: GLFW_PRESS or GLFW_RELEASE
    @param mods: Modifiers active (ex: GLFW_MOD_SHIFT)
    */
    static void key_callback(GLFWwindow *window, int key, [[maybe_unused]] int scancode, int action, [[maybe_unused]] int mods);

    /*
    Handle mouse motion
    @param window: Pointer to the window
    @param xposin: Mouse X position
    @param yposin: Mouse Y position
    */
    static void mouse_callback([[maybe_unused]] GLFWwindow *window, double xposin, double yposin);
};