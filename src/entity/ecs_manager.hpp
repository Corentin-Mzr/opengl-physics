#pragma once

#include <iostream>
#include <unordered_map>

#include "components.hpp"

/*
Class that handles entities and their components
*/
class ECSManager
{
public:
    // Create an entity and return its id
    [[nodiscard]] unsigned create_entity();

    /*
    Add a PhysicsComponent to an entity
    @param entity: Entity's id
    @param component: Physics component
    */
    void add_component(const unsigned entity, const PhysicsComponent &component);

    /*
    Add a TransformComponent to an entity
    @param entity: Entity's id
    @param component: Transform component
    */
    void add_component(const unsigned entity, const TransformComponent &component);

    /*
    Add a RenderComponent to an entity
    @param entity: Entity's id
    @param component: Render component
    */
    void add_component(const unsigned entity, const RenderComponent &component);

    /*
    Remove a component from an entity
    @param entity: Entity's id
    @param component_type: Type of the component
    */
    void remove_component(const unsigned entity, const ComponentType &component_type);

    /*
    Get the entity mask of the given entity
    @param entity: Entity's id
    */
    [[nodiscard]] unsigned get_entity_mask(const unsigned entity) const;

    // Get all entities masks
    [[nodiscard]] std::unordered_map<unsigned, unsigned> get_masks() const;

    // Get all physics components
    [[nodiscard]] std::unordered_map<unsigned, PhysicsComponent> &get_physics();

    // Get all transform components
    [[nodiscard]] std::unordered_map<unsigned, TransformComponent> &get_transforms();

    // Get all render components
    [[nodiscard]] std::unordered_map<unsigned, RenderComponent> &get_renders();

private:
    std::unordered_map<unsigned, unsigned> entity_masks;
    std::unordered_map<unsigned, PhysicsComponent> physics_components;
    std::unordered_map<unsigned, TransformComponent> transform_components;
    std::unordered_map<unsigned, RenderComponent> render_components;

    unsigned entity_count = 0;
};