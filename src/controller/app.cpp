#include "app.hpp"

/*
App class that will create a resizable window
@param width: Width of the window
@param height: Height of the window
@param title: Title of the window
*/
App::App(const unsigned width, const unsigned height, const char *title) : width(width), height(height), title(title)
{
    setup_glfw();
    setup_window();
    setup_glad();
    setup_opengl();
    setup_callbacks();
    setup_systems();
    setup_scene();
}

App::~App()
{
    glDeleteProgram(shader);
    glfwTerminate();
}

// Run the app
void App::run()
{
    // Main loop
    while (!glfwWindowShouldClose(window.get()))
    {
        glfwPollEvents();
        process_input();

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        physics_system.update(dt);
        render_system.render();

        glfwSwapBuffers(window.get());
    }
}

// Initialize GLFW
void App::setup_glfw()
{
    // Initialize GLFW
    if (!glfwInit())
    {
        throw std::runtime_error("Could not initialize GLFW");
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

// Create the window
void App::setup_window()
{
    // Create a window
    GLFWwindow *raw_window = glfwCreateWindow(width, height, title, NULL, NULL);
    if (raw_window == nullptr)
    {
        glfwTerminate();
        throw std::runtime_error("Failed to create GLFW window");
    }

    // Need to use a custom deleter
    window = std::shared_ptr<GLFWwindow>(raw_window, [](GLFWwindow *ptr)
                                         { glfwDestroyWindow(ptr); });

    glfwMakeContextCurrent(window.get());
    glfwSwapInterval(1);
    glfwSetWindowUserPointer(window.get(), this);
}

// Load GLAD
void App::setup_glad()
{
    // Load GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        glfwTerminate();
        throw std::runtime_error("Failed to initialize GLAD");
    }
}

// Define some OpenGL parameters (viewport, background color, ...)
void App::setup_opengl()
{
    // Set viewport
    glViewport(0, 0, width, height);

    // Define background color
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

    // Blending
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

// Define callback functions
void App::setup_callbacks()
{
    // Define viewport callback
    glfwSetFramebufferSizeCallback(window.get(), framebuffer_size_callback);

    // Define input callback
    glfwSetKeyCallback(window.get(), key_callback);
}

// Set up some systems
void App::setup_systems()
{
    render_system = RenderSystem(window);
}

// Define everything in the scene
void App::setup_scene()
{
    shader = shader_factory.load_shader("../shaders/vertex.glsl", "../shaders/fragment.glsl");
    Mesh mesh = mesh_factory.load_mesh(static_cast<int>(ObjectType::Cube));
    std::cout << mesh.vao << " " << mesh.vbo << " " << mesh.ebo << std::endl;
}

// Process input each frame
void App::process_input()
{
}

// Handle window resizing
void App::framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
}

// Handle key inputs
void App::key_callback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    auto app = static_cast<App *>(glfwGetWindowUserPointer(window));

    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    if (key >= 0 && key < 1024)
    {
        if (action == GLFW_PRESS)
            app->keys[key] = true;
        else if (action == GLFW_RELEASE)
            app->keys[key] = false;
    }
}