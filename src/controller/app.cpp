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
    // Delete shader
    glDeleteProgram(shader);
    std::cout << "[APP DESTRUCTION INFO] Deleted shader\n";

    // Delete meshes
    for (const auto &[i, mesh]: render_system.get_meshes())
    {
        glDeleteVertexArrays(1, &mesh.vao);
        glDeleteBuffers(1, &mesh.vbo);
    }
    std::cout << "[APP DESTRUCTION INFO] Deleted meshes\n";

    GLenum error = glGetError();
    if (error != GL_NO_ERROR)
    {
        std::cout << "[APP DESTRUCTION ERROR] An error occured during App destructor call: " << error << std::endl;
    }

    glfwTerminate();
}

// Run the app
void App::run()
{
    // Measure time
    double dt = 0.0f;
    double previous_time = glfwGetTime();
    double current_time = 0.0f;
    double accumulator_dt = 0.0f;
    double physics_dt = 1.0f / 240.0f;

    // Data for FPS
    std::string title_with_fps = std::string(title) + " | FPS: 0";
    size_t replace_index = title_with_fps.size() - 1;
    double fps_previous = previous_time;
    double fps_current = 0.0f;
    double fps_elapsed = 0.0f;
    float frame_count = 0;

    // Main loop
    while (!glfwWindowShouldClose(window.get()))
    {
        current_time = glfwGetTime();
        fps_elapsed = current_time - fps_previous;

        // FPS
        if (fps_elapsed < 1.0f)
            frame_count++;
        else
        {
            title_with_fps.replace(replace_index, title_with_fps.size(), std::to_string(frame_count / fps_elapsed));
            glfwSetWindowTitle(window.get(), title_with_fps.c_str());
            fps_elapsed = 0.0f;
            fps_previous = current_time;
            frame_count = 0;
        }

        // 
        dt = current_time - previous_time;
        previous_time = current_time;

        // Accumulate passed time
        accumulator_dt += dt;

        glfwPollEvents();

        while (accumulator_dt >= physics_dt)
        {
            physics_system.update(physics_dt);
            accumulator_dt -= physics_dt;
            process_input(physics_dt);
        }
        
        camera_system.update();
        render_system.render();
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
    glfwSetInputMode(window.get(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
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

    // Wireframe mode
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    // Blending
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // Depth test
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
}

// Define callback functions
void App::setup_callbacks()
{
    // Define viewport callback
    glfwSetFramebufferSizeCallback(window.get(), framebuffer_size_callback);

    // Define input callback
    glfwSetKeyCallback(window.get(), key_callback);

    // Define mouse callback
    glfwSetCursorPosCallback(window.get(), mouse_callback);
}

// Set up some systems
void App::setup_systems()
{
    // Shader must be initialized before everything
    shader = shader_factory.load_shader("../shaders/vertex.glsl", "../shaders/fragment.glsl");
    glUseProgram(shader);

    // ECS must be initialized before render system
    if (entity_manager == nullptr)
        entity_manager = std::make_shared<EntityManager>();
    
    // TODO: INITIALIZE RENDER SYSTEM
    physics_system = PhysicsSystem(entity_manager);
    render_system = RenderSystem(shader, window, entity_manager);
    camera_system = CameraSystem(shader, window);
}

// Define everything in the scene
void App::setup_scene()
{
    /* ENTITY 1 : CUBE */
    unsigned entity = entity_manager->create_entity();
    TransformComponent transform;
    RenderComponent render;
    PhysicsComponent physics;
    ColliderComponent collider;

    transform.position = {0.0f, 0.0f, 0.0f};
    transform.eulers = {0.0f, 0.0f, 0.0f};
    transform.scale = {1.0f, 1.0f, 1.0f};
    entity_manager->add_component(entity, transform);

    render.object_type = ObjectType::CUBE;
    entity_manager->add_component(entity, render);

    physics.is_static = false;
    physics.forces = {0.0f, 0.0f, 0.0f};
    physics.torque = {-5.0f, 3.0f, 10.0f};
    entity_manager->add_component(entity, physics);

    entity_manager->add_component(entity, collider);

    /* ENTITY 2 : SPHERE */
    entity = entity_manager->create_entity();

    transform.position = {2.0f, 0.0f, 2.0f};
    transform.eulers = {0.0f, 0.0f, 0.0f};
    transform.scale = {0.5f, 0.5f, 0.5f};
    entity_manager->add_component(entity, transform);

    render.object_type = ObjectType::SPHERE;
    entity_manager->add_component(entity, render);

    physics.is_static = false;
    physics.forces = {0.0f, 0.0f, 0.0f};
    physics.torque = {0.0f, 10.0f, 0.0f};
    entity_manager->add_component(entity, physics);

    entity_manager->add_component(entity, collider);
}

// Process input each frame
void App::process_input(const double dt)
{
    glm::vec3 dpos{0.0f, 0.0f, 0.0f};
    glm::vec3 deulers{0.0f, 0.0f, 0.0f};
    float speed_factor = 1.0f;
    float mouse_sensivity = 20.0f;
    bool is_vertical = false;
    bool is_horizontal = false;

    /* ------ KEYBOARD CONTROLS ------ */

    // Front
    if (keys[GLFW_KEY_O])
    {
        dpos.x += 1.0f;
        is_horizontal = true;
    }

    // Back
    if (keys[GLFW_KEY_L])
    {
        dpos.x -= 1.0f;
        is_horizontal = true;
    }

    // Right
    if (keys[GLFW_KEY_SEMICOLON])
    {
        dpos.z += 1.0f;
        is_horizontal = true;
    }

    // Left
    if (keys[GLFW_KEY_K])
    {
        dpos.z -= 1.0f;
        is_horizontal = true;
    }

    // Up
    if (keys[GLFW_KEY_SPACE])
    {
        dpos.y += 1.0f;
        is_vertical = true;
    }

    // Down
    if (keys[GLFW_KEY_M])
    {
        dpos.y -= 1.0f;
        is_vertical = true;
    }

    // Sprint
    if (keys[GLFW_KEY_J])
        speed_factor = 3.0f;

    if (glm::length(dpos) > 1.0f)
        dpos = glm::normalize(dpos);
    dpos *= speed_factor;
    dpos *= dt;

    camera_system.move(dpos, is_vertical, is_horizontal);

    /* ------ MOUSE CONTROLS ------ */

    deulers.y = xoffset * mouse_sensivity * dt;
    deulers.z = yoffset * mouse_sensivity * dt;

    camera_system.spin(deulers);
    xoffset = 0.0, yoffset = 0.0;
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

// Handle mouse motion
void App::mouse_callback(GLFWwindow *window, double xposin, double yposin)
{
    auto app = static_cast<App *>(glfwGetWindowUserPointer(window));

    if (app->first_motion)
    {
        app->xpos = xposin;
        app->ypos = yposin;
        app->first_motion = false;
    }

    app->xoffset += xposin - app->xpos;
    app->yoffset += app->ypos - yposin;

    app->xpos = xposin;
    app->ypos = yposin;
}