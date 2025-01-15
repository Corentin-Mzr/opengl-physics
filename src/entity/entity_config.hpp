#pragma once

#include <array>

constexpr unsigned OBJECT_TYPE_COUNT = 2;

enum class ObjectType
{
    CUBE,
    SPHERE,
};

static const std::array<const char *, 2> model_names{
    "../models/cube.obj",
    "../models/sphere.obj"};

struct Mesh
{
    unsigned vao, vbo, ebo, vertex_count;

    Mesh(const unsigned vao = 0, const unsigned vbo = 0, const unsigned ebo = 0, const unsigned vcount = 0) : vao(vao), vbo(vbo), ebo(ebo), vertex_count(vcount)
    {
    }
};