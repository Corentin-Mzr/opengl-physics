#include "app.hpp"

int main()
{
    try
    {
        App app(1280, 720, "OpenGL Physics");
        app.run();
    }
    catch (const std::exception &e)
    {
        std::cerr << "[APP EXECUTION ERROR] " << e.what() << std::endl;
    }

    return 0;
}