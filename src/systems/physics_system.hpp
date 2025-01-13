#pragma once

/*
Class that will handle the physics of objects in a scene
*/
class PhysicsSystem
{
public:
    PhysicsSystem() = default;
    PhysicsSystem(const PhysicsSystem &) = delete;
    PhysicsSystem &operator=(const PhysicsSystem &) = delete;

    // Update physics
    void update(const float dt);
};