#include "physics_system.hpp"

/*
Class that will handle the physics of objects in a scene
@param entity_manager: Handles entity creation
*/
PhysicsSystem::PhysicsSystem(const std::shared_ptr<EntityManager> &entity_manager) : entity_manager(entity_manager)
{
}

/*
Update physics
@param dt: Delta time
*/
void PhysicsSystem::update(const float dt)
{
    auto &transform_components = entity_manager->get_transforms();
    auto &physics_components = entity_manager->get_physics();

    for (const auto &[entity, mask] : entity_manager->get_masks())
    {
        // Check for PhysicsComponent and TransformComponent
        if ((mask & static_cast<unsigned>(ComponentType::TRANSFORM)) &&
            mask & static_cast<unsigned>(ComponentType::PHYSICS))
        {
            TransformComponent &transform = transform_components[entity];
            PhysicsComponent &physics = physics_components[entity];

            // Do physics
            transform.position += physics.linear_velocity * dt;
            transform.eulers += physics.angular_velocity * dt;

            // Apply gravity
            if (physics.is_gravity_applied)
            {
                transform.position += gravity * dt;
            }
        }
    }
}