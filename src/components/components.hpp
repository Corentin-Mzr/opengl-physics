#pragma once

#include <glm/glm.hpp>

#include "entity_config.hpp"

struct TransformComponent {
    glm::vec3 position, eulers, scale;

    friend std::ostream &operator<<(std::ostream& os, const TransformComponent &t)
    {
        os << "Transform(" 
           << "pos=(x=" << t.position.x << ", y=" << t.position.y << ", z=" << t.position.z << "), "
           << "euler=(x=" << t.eulers.x << ", y=" << t.eulers.y << ", z=" << t.eulers.z << "), "
           << "scale=(x=" << t.scale.x << ", y=" << t.scale.y << ", z=" << t.scale.z << ")"
           << ")";
        return os;
    }
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