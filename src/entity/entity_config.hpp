#pragma once

#include <array>

enum class ObjectType
{
    Cube,
    Sphere,
};

static const std::array<const char *, 2> model_names
{
    "../models/cube.obj",
    "../models/sphere.obj"
};

struct Mesh
{
    unsigned vao, vbo, ebo;
};