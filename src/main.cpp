#include <iostream>

#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <glm/glm.hpp>

int main()
{
    // Initialize GLFW
    if (!glfwInit())
    {
        std::cerr << "Could not initialize GLFW\n";
        return 1;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Create a window
    GLFWwindow *window = glfwCreateWindow(800, 600, "OpenGL Physics", nullptr, nullptr);
    if (window == nullptr)
    {
        glfwTerminate();
        std::cerr << "Could not create window\n";
        return 1;
    }
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    // Load GLAD
    if (!gladLoadGLLoader((GLADloadproc)(glfwGetProcAddress)))
    {
        glfwTerminate();
        std::cerr << "Could not load GLAD\n";
        return 1;
    }

    // Set viewport
    glViewport(0, 0, 800, 600);

    // Define background color
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

    // Main loop
    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glfwSwapBuffers(window);
    }

    return 0;
}