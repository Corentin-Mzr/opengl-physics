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
    struct PairHash
    {
        template <typename T1, typename T2>
        std::size_t operator()(const std::pair<T1, T2> &p) const
        {
            auto hash1 = std::hash<T1>{}(p.first);
            auto hash2 = std::hash<T2>{}(p.second);
            return hash1 ^ (hash2 << 1);
        }
    };

public:
    ~ShaderFactory();

    /*
    Load a shader
    @param vertex_filepath: Path to the vertex shader
    @param fragment_filepath: Path to the fragment shader
    */
    [[nodiscard]] unsigned load_shader(const char *vertex_filepath, const char *fragment_filepath);

private:
    std::unordered_map<std::pair<const char*, const char*>, unsigned, PairHash> shader_map;

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

    /*
    Check if a shader is already loaded
    @param shader: Pair of vertex_filepath and fragment_filepath
    */
    [[nodiscard]] bool is_loaded(const std::pair<const char*, const char*> &shader) const;
};