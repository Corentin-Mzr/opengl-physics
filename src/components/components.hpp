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
    float mass;
    glm::vec3 linear_velocity;
    glm::vec3 linear_acceleration;
    glm::vec3 forces;
    glm::vec3 angular_acceleration;
    glm::vec3 angular_velocity;
    glm::vec3 torque;
    glm::mat3 inv_inertia_tensor;
    bool is_static;

    PhysicsComponent(const float mass = 1.0f,
                     const glm::vec3 &linear_velocity = {0.0f, 0.0f, 0.0f},
                     const glm::vec3 &angular_velocity = {0.0f, 0.0f, 0.0f},
                     const bool is_static = false)
    {
        this->mass = mass;
        this->linear_velocity = linear_velocity;
        this->angular_velocity = angular_velocity;
        this->is_static = is_static;

        // Default values
        linear_acceleration = {0.0f, 0.0f, 0.0f};
        forces = {0.0f, 0.0f, 0.0f};
        angular_acceleration = {0.0f, 0.0f, 0.0f};
        torque = {0.0f, 0.0f, 0.0f};
        inv_inertia_tensor = glm::mat3(1.0f);
    }
};

struct ColliderComponent
{
    glm::vec3 half_size, offset;

    ColliderComponent(const glm::vec3 &half_size = {0.5f, 0.5f, 0.5f}, const glm::vec3 offset = {0.0f, 0.0f, 0.0f}) : half_size(half_size), offset(offset)
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
    COLLIDER = 1 << 2,
    RENDER = 1 << 3,
};