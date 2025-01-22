#pragma once

#include <memory>

#include <glm/gtc/quaternion.hpp>

#include "entity_manager.hpp"

/*
Class that will handle the physics of objects in a scene
@param entity_manager: Handles entity creation
*/
class PhysicsSystem
{
public:
    PhysicsSystem() = default;
    PhysicsSystem(const std::shared_ptr<EntityManager> entity_manager);

    // Update physics
    void update(const float dt);

private:
    glm::vec3 gravity{0.0f, -9.81f, 0.0f};

    std::shared_ptr<EntityManager> entity_manager = nullptr;

    /*
    Returns the dimensions of a cuboid using its collider component, in local space
    @param collider: Cuboid's ColliderComponent
    */
    glm::vec3 get_local_cuboid_dimensions(const ColliderComponent &collider);

    /*
    Retrieve the inverse inertia matrix using a ColliderComponent
    @param collider: Collider component
    @param mass: Cuboid's mass
    */
    glm::mat3 get_inverse_inertia_tensor(const ColliderComponent &collider, const float mass);
};