#include "ecs_manager.hpp"

// Create an entity and return its id
[[nodiscard]] unsigned int ECSManager::create_entity()
{
    unsigned int entity_id = entity_count;
    entity_masks[entity_id] = 0;
    entity_count++;
    return entity_id;
}

/*
Add a PhysicsComponent to an entity
@param entity: Entity's id
@param component: Physics component
*/
void ECSManager::add_component(const unsigned entity, const PhysicsComponent &component)
{
    physics_components[entity] = component;
    entity_masks[entity] |= static_cast<unsigned>(ComponentType::PHYSICS);
}

/*
Add a TransformComponent to an entity
@param entity: Entity's id
@param component: Transform component
*/
void ECSManager::add_component(const unsigned entity, const TransformComponent &component)
{
    transform_components[entity] = component;
    entity_masks[entity] |= static_cast<unsigned>(ComponentType::TRANSFORM);
}

/*
Add a RenderComponent to an entity
@param entity: Entity's id
@param component: Render component
*/
void ECSManager::add_component(const unsigned entity, const RenderComponent &component)
{
    render_components[entity] = component;
    entity_masks[entity] |= static_cast<unsigned>(ComponentType::RENDER);
}

/*
Remove a component from an entity
@param entity: Entity's id
@param component_type: Type of the component
*/
void ECSManager::remove_component(const unsigned entity, const ComponentType &component)
{
    switch (component)
    {
    case ComponentType::TRANSFORM:
    {
        auto it = transform_components.find(entity);
        if (it != transform_components.end())
            transform_components.erase(it);
        break;
    }
    case ComponentType::PHYSICS:
    {
        auto it = physics_components.find(entity);
        if (it != physics_components.end())
            physics_components.erase(it);
        break;
    }
    case ComponentType::RENDER:
    {
        auto it = render_components.find(entity);
        if (it != render_components.end())
            render_components.erase(it);
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
[[nodiscard]] unsigned ECSManager::get_entity_mask(const unsigned entity) const
{
    auto it = entity_masks.find(entity);
    if (it != entity_masks.end())
        return entity_masks.at(entity);

    std::cerr << "[ECS MANAGER WARNING]\n"
              << "Could not find mask for entity " << entity << std::endl;
    return 0;
}

// Get all entities masks
[[nodiscard]] std::unordered_map<unsigned, unsigned> ECSManager::get_masks() const
{
    return entity_masks;
}

// Get all physics components
[[nodiscard]] std::unordered_map<unsigned, PhysicsComponent> &ECSManager::get_physics()
{
    return physics_components;
}

// Get all transform components
[[nodiscard]] std::unordered_map<unsigned, TransformComponent> &ECSManager::get_transforms()
{
    return transform_components;
}

// Get all render components
[[nodiscard]] std::unordered_map<unsigned, RenderComponent> &ECSManager::get_renders()
{
    return render_components;
}