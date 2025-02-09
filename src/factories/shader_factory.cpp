#include "shader_factory.hpp"

/*
Load a shader
@param vertex_filepath: Path to the vertex shader
@param fragment_filepath: Path to the fragment shader
*/
[[nodiscard]] unsigned ShaderFactory::load_shader(const char *vertex_filepath, const char *fragment_filepath)
{
    std::cout << "[SHADER FACTORY LOADING INFO] Creating a shader with " << vertex_filepath << " and " << fragment_filepath << std::endl;
    const unsigned program = make_program(vertex_filepath, fragment_filepath);
    
    if (program)
        std::cout << "[SHADER FACTORY LOADING SUCCESS] Shader was created\n";
    else
        std::cerr << "[SHADER FACTORY LOADING ERROR] Could not create the shader\n";

    return program;
}

/*
Make a shader program and stores it in the shader map
@param vertex_filepath: Path to the vertex shader
@param fragment_filepath: Path to the fragment shader
*/
[[nodiscard]] unsigned ShaderFactory::make_program(const char *vertex_filepath, const char *fragment_filepath)
{
    // Create modules
    const unsigned vertex_shader = make_module(vertex_filepath, GL_VERTEX_SHADER);
    const unsigned fragment_shader = make_module(fragment_filepath, GL_FRAGMENT_SHADER);

    // Create shader program and link modules
    unsigned shader_program = glCreateProgram();
    glAttachShader(shader_program, vertex_shader);
    glAttachShader(shader_program, fragment_shader);
    glLinkProgram(shader_program);

    // Check compilation is OK
    int success;
    glGetProgramiv(shader_program, GL_LINK_STATUS, &success);
    if (!success)
    {
        char error_log[1024];
        glGetShaderInfoLog(shader_program, 1024, NULL, error_log);
        std::cerr << "[SHADER PROGRAM LINKING ERROR] " << error_log << std::endl;
    }

    // Delete modules
    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);

    return shader_program;
}

/*
Make a shader module
@param filepath: Path to the module
@param module_type: GL_VERTEX_SHADER or GL_FRAGMENT_SHADER
*/
[[nodiscard]] unsigned ShaderFactory::make_module(const char *filepath, const unsigned module_type)
{
    // Get file content
    std::ifstream file;
    std::stringstream buffer;
    std::string line;
    buffer.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try
    {
        file.open(filepath);
        buffer << file.rdbuf();
        file.close();
    }
    catch (std::ifstream::failure &e)
    {
        std::cerr << "[SHADER MODULE CREATION ERROR] " << e.what() << std::endl;
    }

    // Convert to char*
    const std::string shader_source = buffer.str();
    const char *shader_src = shader_source.c_str();

    // Create and compile the shader module
    unsigned shader_module = glCreateShader(module_type);
    glShaderSource(shader_module, 1, &shader_src, NULL);
    glCompileShader(shader_module);

    // Check compilation is OK
    int success;
    glGetShaderiv(shader_module, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        char error_log[1024];
        glGetShaderInfoLog(shader_module, 1024, NULL, error_log);
        std::cerr << "[SHADER MODULE COMPILATION ERROR] " << error_log << std::endl;
    }

    return shader_module;
}