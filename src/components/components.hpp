#pragma once

#include <glm/glm.hpp>

#include "entity_config.hpp"

struct TransformComponent {
    glm::vec3 position, eulers, scale;
};

struct PhysicsComponent {
    glm::vec3 linear_velocity, angular_velocity;
};

struct RenderComponent {
    ObjectType object_type;
};

enum class ComponentType {
    TRANSFORM = 1 << 0,
    PHYSICS = 1 << 1,
    RENDER = 1 << 2,
};