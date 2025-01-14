#pragma once

#include <array>

enum class ObjectType
{
    CUBE,
    SPHERE,
    COUNT, // NOT AN OBJECT TYPE
};

static const std::array<const char *, 2> model_names
{
    "../models/cube.obj",
    "../models/sphere.obj"
};

struct Mesh
{
    unsigned vao, vbo, ebo, vertex_count;
};