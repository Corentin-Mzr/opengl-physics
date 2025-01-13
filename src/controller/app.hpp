#pragma once

#include <stdexcept>
#include <string>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

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
    GLFWwindow *window = nullptr;
    std::string title = "";
    unsigned width = 0, height = 0;
    unsigned shader = 0;
    bool keys[1024] = {false};

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

    // Define everything in the scene
    void setup_scene();

    // Process input each frame
    void process_input();

    // Handle window resizing
    static void framebuffer_size_callback(GLFWwindow *window, int width, int height);

    // Handle key inputs
    static void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods);
};