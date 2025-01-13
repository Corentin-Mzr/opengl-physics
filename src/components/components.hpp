#pragma once

#include <glm/glm.hpp>

#include "object_type.hpp"

struct TransformComponent {
    glm::vec3 position, eulers, scale;
};

struct PhysicsComponent {
    glm::vec3 linear_velocity, angular_velocity;
};

struct RenderComponent {
    ObjectType object_type;
};