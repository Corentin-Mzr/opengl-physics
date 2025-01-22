#include "app.hpp"

/*
App class that will create a resizable window
@param width: Width of the window
@param height: Height of the window
@param title: Title of the window
*/
App::App(const unsigned width, const unsigned height, const char *title) : width_(width), height_(height), title_(title)
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
    // OpenGL functions wont work if GLAD is not loaded
    if (glad_initialized_)
    {
        // Delete shader
        glDeleteProgram(shader_);
        std::cout << "[APP DESTRUCTION INFO] Deleted shader\n";

        // Delete meshes
        for (const auto &[i, mesh] : render_system_.get_meshes())
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
    }

    if (glfw_initialized_)
        glfwTerminate();
}

// Run the app
void App::run()
{
    // Measure time
    float dt = 0.0f;
    float previous_time = static_cast<float>(glfwGetTime());
    float current_time = 0.0f;
    float accumulator_dt = 0.0f;
    const float physics_dt = 1.0f / 240.0f;

    // Data for FPS
    std::string title_with_fps = std::string(title_) + " | FPS: 0";
    const size_t replace_index = title_with_fps.size() - 1;
    float fps_previous = previous_time;
    float fps_elapsed = 0.0f;
    float frame_count = 0;

    // Main loop
    while (!glfwWindowShouldClose(window_.get()))
    {
        current_time = static_cast<float>(glfwGetTime());
        fps_elapsed = current_time - fps_previous;

        // FPS
        if (fps_elapsed < 1.0f)
            frame_count++;
        else
        {
            title_with_fps.replace(replace_index, title_with_fps.size(), std::to_string(frame_count / fps_elapsed));
            glfwSetWindowTitle(window_.get(), title_with_fps.c_str());
            fps_elapsed = 0.0f;
            fps_previous = current_time;
            frame_count = 0;
        }

        // Compute delta time
        dt = current_time - previous_time;
        previous_time = current_time;

        // Accumulate passed time
        accumulator_dt += dt;

        glfwPollEvents();

        while (accumulator_dt >= physics_dt)
        {
            physics_system_.update(physics_dt);
            accumulator_dt -= physics_dt;
            process_input(physics_dt);
        }

        camera_system_.update();
        render_system_.render();
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

    glfw_initialized_ = true;
}

// Create the window
void App::setup_window()
{
    // Create a window
    GLFWwindow *raw_window = glfwCreateWindow(width_, height_, title_, NULL, NULL);
    if (raw_window == nullptr)
    {
        glfwTerminate();
        throw std::runtime_error("Failed to create GLFW window");
    }

    // Need to use a custom deleter
    window_ = std::shared_ptr<GLFWwindow>(raw_window, [](GLFWwindow *ptr)
                                          { glfwDestroyWindow(ptr); });

    glfwMakeContextCurrent(window_.get());
    glfwSwapInterval(1);
    glfwSetWindowUserPointer(window_.get(), this);
    glfwSetInputMode(window_.get(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
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

    glad_initialized_ = true;
}

// Define some OpenGL parameters (viewport, background color, ...)
void App::setup_opengl()
{
    // Set viewport
    glViewport(0, 0, width_, height_);

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
    glfwSetFramebufferSizeCallback(window_.get(), framebuffer_size_callback);

    // Define input callback
    glfwSetKeyCallback(window_.get(), key_callback);

    // Define mouse callback
    glfwSetCursorPosCallback(window_.get(), mouse_callback);
}

// Set up some systems
void App::setup_systems()
{
    // Shader must be initialized before everything
    shader_ = shader_factory_.load_shader("../shaders/vertex.glsl", "../shaders/fragment.glsl");
    glUseProgram(shader_);

    // ECS must be initialized before render system
    if (entity_manager_ == nullptr)
        entity_manager_ = std::make_shared<EntityManager>();

    physics_system_ = PhysicsSystem(entity_manager_);
    render_system_ = RenderSystem(shader_, window_, entity_manager_);
    camera_system_ = CameraSystem(shader_, window_);
}

// Define everything in the scene
void App::setup_scene()
{
    /* ENTITY 1 : CUBE */
    unsigned entity = entity_manager_->create_entity();
    TransformComponent transform;
    RenderComponent render;
    PhysicsComponent physics;
    ColliderComponent collider;

    transform.position = {0.0f, 0.0f, 0.0f};
    transform.eulers = {0.0f, 0.0f, 0.0f};
    transform.scale = {1.0f, 1.0f, 1.0f};
    entity_manager_->add_component(entity, transform);

    render.object_type = ObjectType::CUBE;
    entity_manager_->add_component(entity, render);

    physics.is_static = false;
    physics.forces = {0.0f, 0.0f, 0.0f};
    physics.torque = {-5.0f, 3.0f, 10.0f};
    entity_manager_->add_component(entity, physics);

    entity_manager_->add_component(entity, collider);

    /* ENTITY 2 : SPHERE */
    entity = entity_manager_->create_entity();

    transform.position = {2.0f, 0.0f, 2.0f};
    transform.eulers = {0.0f, 0.0f, 0.0f};
    transform.scale = {0.5f, 0.5f, 0.5f};
    entity_manager_->add_component(entity, transform);

    render.object_type = ObjectType::SPHERE;
    entity_manager_->add_component(entity, render);

    physics.is_static = false;
    physics.forces = {0.0f, 0.0f, 0.0f};
    physics.torque = {0.0f, 10.0f, 0.0f};
    entity_manager_->add_component(entity, physics);

    entity_manager_->add_component(entity, collider);
}

/*
Process input each frame
@param dt: Delta time
*/
void App::process_input(const float dt)
{
    /* ------ KEYBOARD CONTROLS ------ */
    // Front
    if (keys_[GLFW_KEY_O])
    {
        dpos.x += 1.0f;
        is_horizontal = true;
    }

    // Back
    if (keys_[GLFW_KEY_L])
    {
        dpos.x -= 1.0f;
        is_horizontal = true;
    }

    // Right
    if (keys_[GLFW_KEY_SEMICOLON])
    {
        dpos.z += 1.0f;
        is_horizontal = true;
    }

    // Left
    if (keys_[GLFW_KEY_K])
    {
        dpos.z -= 1.0f;
        is_horizontal = true;
    }

    // Up
    if (keys_[GLFW_KEY_SPACE])
    {
        dpos.y += 1.0f;
        is_vertical = true;
    }

    // Down
    if (keys_[GLFW_KEY_M])
    {
        dpos.y -= 1.0f;
        is_vertical = true;
    }

    // Sprint
    if (keys_[GLFW_KEY_J])
        speed_factor = 3.0f;

    if (glm::length(dpos) > 1.0f)
        dpos = glm::normalize(dpos);
    dpos *= speed_factor;
    dpos *= dt;

    camera_system_.move(dpos, is_vertical, is_horizontal);

    /* ------ MOUSE CONTROLS ------ */

    deulers.y = xoffset_ * mouse_sensivity * dt;
    deulers.z = yoffset_ * mouse_sensivity * dt;
    camera_system_.spin(deulers);

    /* ------ RESET VARIABLES ------ */
    dpos = {0.0f, 0.0f, 0.0f};
    deulers = {0.0f, 0.0f, 0.0f};
    xoffset_ = 0.0, yoffset_ = 0.0;
    speed_factor = 1.0f;
    is_vertical = false;
    is_horizontal = false;
}

/*
Handle window resizing
@param window: Pointer to the window
@param width: Width of the window
@param height: Height of the window
*/
void App::framebuffer_size_callback([[maybe_unused]] GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
}

/*
Handle key inputs
@param window: Pointer to the window
@param key: Key code representing the key (ex: GLFW_KEY_...)
@param scancode: Hardware code that identifies the physical key.
@param action: GLFW_PRESS or GLFW_RELEASE
@param mods: Modifiers active (ex: GLFW_MOD_SHIFT)
*/
void App::key_callback(GLFWwindow *window, int key, [[maybe_unused]] int scancode, int action, [[maybe_unused]] int mods)
{
    auto app = static_cast<App *>(glfwGetWindowUserPointer(window));

    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    if (key >= 0 && key < 1024)
    {
        if (action == GLFW_PRESS)
            app->keys_[key] = true;
        else if (action == GLFW_RELEASE)
            app->keys_[key] = false;
    }
}

/*
Handle mouse motion
@param window: Pointer to the window
@param xposin: Mouse X position
@param yposin: Mouse Y position
*/
void App::mouse_callback(GLFWwindow *window, double xposin, double yposin)
{
    auto app = static_cast<App *>(glfwGetWindowUserPointer(window));
    const float xposin_f = static_cast<float>(xposin);
    const float yposin_f = static_cast<float>(yposin);

    if (app->first_motion_)
    {
        app->xpos_ = xposin_f;
        app->ypos_ = yposin_f;
        app->first_motion_ = false;
    }

    app->xoffset_ += xposin_f - app->xpos_;
    app->yoffset_ += app->ypos_ - yposin_f;

    app->xpos_ = xposin_f;
    app->ypos_ = yposin_f;
}