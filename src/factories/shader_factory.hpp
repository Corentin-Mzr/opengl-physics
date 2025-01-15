#pragma once

#include <iostream>
#include <utility>
#include <unordered_map>
#include <sstream>
#include <fstream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

/*
Class used to create shaders
Also stores every shader loaded in a map
*/
class ShaderFactory
{

public:
    /*
    Load a shader
    @param vertex_filepath: Path to the vertex shader
    @param fragment_filepath: Path to the fragment shader
    */
    [[nodiscard]] unsigned load_shader(const char *vertex_filepath, const char *fragment_filepath);

private:
    /*
    Make a shader program and stores it in the shader map
    @param vertex_filepath: Path to the vertex shader
    @param fragment_filepath: Path to the fragment shader
    */
    [[nodiscard]] unsigned make_program(const char *vertex_filepath, const char *fragment_filepath);

    /*
    Make a shader module
    @param filepath: Path to the module
    @param module_type: GL_VERTEX_SHADER or GL_FRAGMENT_SHADER
    */
    [[nodiscard]] unsigned make_module(const char *filepath, const unsigned module_type);
};