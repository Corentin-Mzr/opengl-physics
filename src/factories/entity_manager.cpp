#include "entity_manager.hpp"

// Create an entity and return its id
[[nodiscard]] unsigned EntityManager::create_entity() noexcept
{
    unsigned entity_id = entity_count_;
    entity_masks_[entity_id] = 0;
    entity_count_++;
    return entity_id;
}

/*
Add a PhysicsComponent to an entity
@param entity: Entity's id
@param component: Physics component
*/
void EntityManager::add_component(const unsigned entity, const PhysicsComponent &component) noexcept
{
    if (!key_exist(entity, entity_masks_))
        return;

    physics_components_[entity] = component;
    entity_masks_[entity] |= static_cast<unsigned>(ComponentType::PHYSICS);
}

/*
Add a TransformComponent to an entity
@param entity: Entity's id
@param component: Transform component
*/
void EntityManager::add_component(const unsigned entity, const TransformComponent &component) noexcept
{
    if (!key_exist(entity, entity_masks_))
        return;

    transform_components_[entity] = component;
    entity_masks_[entity] |= static_cast<unsigned>(ComponentType::TRANSFORM);
}

/*
Add a RenderComponent to an entity
@param entity: Entity's id
@param component: Render component
*/
void EntityManager::add_component(const unsigned entity, const RenderComponent &component) noexcept
{
    if (!key_exist(entity, entity_masks_))
        return;

    render_components_[entity] = component;
    entity_masks_[entity] |= static_cast<unsigned>(ComponentType::RENDER);
}

/*
Add a ColliderComponent to an entity
@param entity: Entity's id
@param component: Collider component
*/
void EntityManager::add_component(const unsigned entity, const ColliderComponent &component) noexcept
{
    if (!key_exist(entity, entity_masks_))
        return;

    collider_components_[entity] = component;
    entity_masks_[entity] |= static_cast<unsigned>(ComponentType::COLLIDER);
}

/*
Remove a component from an entity
@param entity: Entity's id
@param component_type: Type of the component
*/
void EntityManager::remove_component(const unsigned entity, const ComponentType &component) noexcept
{
    switch (component)
    {
    case ComponentType::TRANSFORM:
    {
        if (key_exist(entity, transform_components_))
            transform_components_.erase(entity);
        break;
    }
    case ComponentType::PHYSICS:
    {
        if (key_exist(entity, physics_components_))
            physics_components_.erase(entity);
        break;
    }
    case ComponentType::RENDER:
    {
        if (key_exist(entity, render_components_))
            render_components_.erase(entity);
        break;
    }
    case ComponentType::COLLIDER:
    {
        if (key_exist(entity, collider_components_))
            collider_components_.erase(entity);
        break;
    }
    default:
        std::cerr << "[ECS MANAGER WARNING]\n"
                  << "Unknown component type for removal\n";
        break;
    }
}

/*
Get the entity mask of the given entity
@param entity: Entity's id
*/
[[nodiscard]] unsigned EntityManager::get_entity_mask(const unsigned entity) const noexcept
{
    if (key_exist(entity, entity_masks_))
        return entity_masks_.at(entity);

    std::cerr << "[ECS MANAGER WARNING]\n"
              << "Could not find mask for entity " << entity << std::endl;
    return 0;
}

// Get all entities masks
[[nodiscard]] std::unordered_map<unsigned, unsigned> EntityManager::get_masks() const noexcept
{
    return entity_masks_;
}

// Get all physics components
[[nodiscard]] std::unordered_map<unsigned, PhysicsComponent> &EntityManager::get_physics() noexcept
{
    return physics_components_;
}

// Get all transform components
[[nodiscard]] std::unordered_map<unsigned, TransformComponent> &EntityManager::get_transforms() noexcept
{
    return transform_components_;
}

// Get all render components
[[nodiscard]] std::unordered_map<unsigned, RenderComponent> &EntityManager::get_renders() noexcept
{
    return render_components_;
}

// Get all collider components
[[nodiscard]] std::unordered_map<unsigned, ColliderComponent> &EntityManager::get_colliders() noexcept
{
    return collider_components_;
}

/*
Check if entity id is stored in the given component map
@param id: Entity's id
@param component_map: Map of components
*/
template <class T>
[[nodiscard]] bool EntityManager::key_exist(const unsigned id, const std::unordered_map<unsigned, T> &component_map) const noexcept
{
    return component_map.find(id) != component_map.end();
}