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
    ~App();

    // Run the app
    void run();

private:
    std::shared_ptr<GLFWwindow> window = nullptr;
    const char* title = nullptr;
    unsigned width = 0, height = 0;
    unsigned shader = 0;
    bool keys[1024] = {false};
    double xpos = 0.0, ypos = 0.0, xoffset = 0.0, yoffset = 0.0;
    bool first_motion = true;
    float dt = 0.01f;
    RenderSystem render_system;
    PhysicsSystem physics_system;
    CameraSystem camera_system;
    ShaderFactory shader_factory;
    std::shared_ptr<EntityManager> entity_manager = nullptr;

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

    // Process input each frame
    void process_input(const double dt);

    // Handle window resizing
    static void framebuffer_size_callback(GLFWwindow *window, int width, int height);

    // Handle key inputs
    static void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods);

    // Handle mouse motion
    static void mouse_callback(GLFWwindow *window, double xposin, double yposin);
};