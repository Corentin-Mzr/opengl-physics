#include "shader_factory.hpp"

ShaderFactory::~ShaderFactory()
{
    for (auto [pair, shader]: shader_map)
    {
        glDeleteProgram(shader);
    }
}

/*
Load a shader
@param vertex_filepath: Path to the vertex shader
@param fragment_filepath: Path to the fragment shader
*/
[[nodiscard]] unsigned ShaderFactory::load_shader(const char *vertex_filepath, const char *fragment_filepath)
{
    // Check if shader is already loaded
    if (is_loaded({vertex_filepath, fragment_filepath}))
    {
        std::cout << "[SHADER FACTORY LOADING INFO]\n"
                  << "Shader is already loaded\n";
        return shader_map.at({vertex_filepath, fragment_filepath});
    }

    // Else create it and store it
    // Could add a safety to check if shader program is correct
    const unsigned program = make_program(vertex_filepath, fragment_filepath);
    shader_map[{vertex_filepath, fragment_filepath}] = program;

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
        std::cerr << "[SHADER PROGRAM LINKING ERROR]\n"
                  << error_log << std::endl;
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
        std::cerr << "[SHADER MODULE CREATION ERROR]\n"
                  << e.what() << std::endl;
    }

    // Convert to char*
    std::string shader_source = buffer.str();
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
        std::cerr << "[SHADER MODULE COMPILATION ERROR]\n"
                  << error_log << std::endl;
    }

    return shader_module;
}

/*
Check if a shader is already loaded
@param shader: Pair of vertex_filepath and fragment_filepath
*/
[[nodiscard]] bool ShaderFactory::is_loaded(const std::pair<const char *, const char *> &shader) const
{
    const auto it = shader_map.find(shader);
    return it != shader_map.end();
}