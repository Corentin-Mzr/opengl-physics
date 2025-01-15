#version 330 core

// ------------- FUNCTIONS ------------- //

// Compute Translation Matrix
mat4 translation_matrix(in vec3 pos)
{
    return mat4(
        1.0, 0.0, 0.0, 0.0,
        0.0, 1.0, 0.0, 0.0,
        0.0, 0.0, 1.0, 0.0,
        pos.x, pos.y, pos.z, 1.0
    );
}

// Compute Scale Matrix
mat4 scale_matrix(in vec3 scale)
{
    return mat4(
        scale.x, 0.0, 0.0, 0.0,
        0.0, scale.y, 0.0, 0.0,
        0.0, 0.0, scale.z, 0.0,
        0.0, 0.0, 0.0, 1.0
    );
}

// Compute Rotation Matrix around X axis
// Theta (t) in radians
mat4 rotx_matrix(in float t)
{
    float c = cos(t);
    float s = sin(t);

    return mat4(
        1.0, 0.0, 0.0, 0.0,
        0.0, c, -s, 0.0,
        0.0, s, c, 0.0,
        0.0, 0.0, 0.0, 1.0
    );
}

// Compute Rotation Matrix around Y axis
// Theta (t) in radians
mat4 roty_matrix(in float t)
{
    float c = cos(t);
    float s = sin(t);
    return mat4(
        c, 0.0, s, 0.0,
        0.0, 1.0, 0.0, 0.0,
        -s, 0.0, c, 0.0,
        0.0, 0.0, 0.0, 1.0
    );
}


// Compute Rotation Matrix around Z axis
// Theta (t) in radians
mat4 rotz_matrix(in float t)
{
    float c = cos(t);
    float s = sin(t);

    mat4 rotz = mat4(
        c, -s, 0.0, 0.0,
        s, c, 0.0, 0.0,
        0.0, 0.0, 1.0, 0.0,
        0.0, 0.0, 0.0, 1.0
    );

    return rotz;
}

// Compute Global Rotation Matrix around all axes
// Angles in radians
mat4 rotation_matrix(in vec3 euler)
{
    return rotz_matrix(euler.z) * roty_matrix(euler.y) * rotx_matrix(euler.x);
}

// Compute the model matrix
mat4 model_matrix(in vec3 position, in vec3 euler, in vec3 scale)
{
    mat4 model = translation_matrix(position) * rotation_matrix(euler) * scale_matrix(scale);
    return model;
}

// ------------- MAIN ------------- //

layout (location = 0) in vec3 vertex_pos;

uniform vec3 position;
uniform vec3 euler;
uniform vec3 scale;

uniform mat4 view_projection;

void main()
{
    mat4 model = model_matrix(position, euler, scale);
    gl_Position = view_projection * model * vec4(vertex_pos, 1.0f);
}