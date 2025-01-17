#pragma once

#include <memory>

#include "entity_manager.hpp"

/*
Class that will handle the physics of objects in a scene
@param entity_manager: Handles entity creation
*/
class PhysicsSystem
{
public:
    PhysicsSystem() = default;
    PhysicsSystem(const std::shared_ptr<EntityManager> &entity_manager);
    PhysicsSystem(const PhysicsSystem &) = delete;

    // Update physics
    void update(const float dt);

private:
    glm::vec3 gravity{0.0f, -9.81f, 0.0f};

    std::shared_ptr<EntityManager> entity_manager = nullptr;
};