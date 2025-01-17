#pragma once

#include <glm/glm.hpp>

#include "entity_config.hpp"

struct TransformComponent
{
    glm::vec3 position, eulers, scale;

    TransformComponent(const glm::vec3 &pos = {0.0f, 0.0f, 0.0f},
                       const glm::vec3 &eulers = {0.0f, 0.0f, 0.0f},
                       const glm::vec3 &scale = {1.0f, 1.0f, 1.0f}) : position(pos), eulers(eulers), scale(scale)
    {
    }
};

struct PhysicsComponent
{
    glm::vec3 linear_velocity, angular_velocity;
    bool is_gravity_applied;

    PhysicsComponent(const glm::vec3 &linear = {0.0f, 0.0f, 0.0f},
                     const glm::vec3 &angular = {0.0f, 0.0f, 0.0f},
                     const bool gravity = false) : linear_velocity(linear), angular_velocity(angular), is_gravity_applied(gravity)
    {
    }
};

struct RenderComponent
{
    ObjectType object_type;

    RenderComponent(const ObjectType &object_type = ObjectType::CUBE) : object_type(object_type)
    {
    }
};

enum class ComponentType
{
    TRANSFORM = 1 << 0,
    PHYSICS = 1 << 1,
    RENDER = 1 << 2,
};