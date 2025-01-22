#include "physics_system.hpp"

/*
Class that will handle the physics of objects in a scene
@param entity_manager: Handles entity creation
*/
PhysicsSystem::PhysicsSystem(const std::shared_ptr<EntityManager> entity_manager) : entity_manager_(entity_manager)
{
}

/*
Update physics
@param dt: Delta time
*/
void PhysicsSystem::update(const float dt)
{
    auto &transform_components = entity_manager_->get_transforms();
    auto &physics_components = entity_manager_->get_physics();
    auto &collider_components = entity_manager_->get_colliders();

    for (const auto &[entity, mask] : entity_manager_->get_masks())
    {
        // Check if entity has TransformComponent
        if (!(mask & static_cast<unsigned>(ComponentType::TRANSFORM)))
            continue;

        // Check if entity has PhysicsComponent
        if (!(mask & static_cast<unsigned>(ComponentType::PHYSICS)))
            continue;

        // Check if entity has ColliderComponent
        if (!(mask & static_cast<unsigned>(ComponentType::COLLIDER)))
            continue;

        // Retrieve associated components
        TransformComponent &transform = transform_components[entity];
        PhysicsComponent &physics = physics_components[entity];
        ColliderComponent &collider = collider_components[entity];

        // Check if object is static
        if (physics.is_static)
            continue;

        // Else do physics

        // Linear motion
        physics.linear_acceleration = physics.forces / physics.mass;
        physics.linear_velocity += physics.linear_acceleration * dt;
        physics.forces = {0.0f, 0.0f, 0.0f};
        transform.position += physics.linear_velocity * dt;

        // Angular motion
        physics.inv_inertia_tensor = get_inverse_inertia_tensor(collider, physics.mass);
        physics.angular_acceleration = physics.inv_inertia_tensor * physics.torque;
        physics.angular_velocity += physics.angular_acceleration * dt;
        physics.torque = {0.0f, 0.0f, 0.0f};

        glm::quat angular_vel_quat(0.0f, physics.angular_velocity.x, physics.angular_velocity.y, physics.angular_velocity.z);
        glm::quat orientation = glm::quat(glm::radians(transform.eulers));
        orientation += 0.5f * angular_vel_quat * orientation * dt;
        orientation = glm::normalize(orientation);
        transform.eulers = glm::degrees(glm::eulerAngles(orientation));
    }
}

/*
Returns the dimensions of a cuboid using its collider component, in local space
@param collider: Cuboid's ColliderComponent
*/
glm::vec3 PhysicsSystem::get_local_cuboid_dimensions(const ColliderComponent &collider) noexcept
{
    return 2.0f * collider.half_size;
}

/*
Retrieve the inertia matrix using a ColliderComponent
@param collider: Collider component
@param mass: Cuboid's mass
*/
glm::mat3 PhysicsSystem::get_inverse_inertia_tensor(const ColliderComponent &collider, const float mass)
{
    const glm::vec3 dims = get_local_cuboid_dimensions(collider);
    glm::mat3 tensor = (mass * 1.0f / 12.0f) * glm::mat3{
        glm::vec3{dims.y * dims.y + dims.z * dims.z, 0.0f, 0.0f}, 
        glm::vec3{0.0f, dims.x * dims.x + dims.z * dims.z, 0.0f}, 
        glm::vec3{0.0f, 0.0f, dims.x * dims.x + dims.y * dims.y}
    };
    return glm::inverse(tensor);
}