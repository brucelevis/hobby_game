#include "physics_scene.h"

#include "physics_component.h"

namespace hg
{
    PhysicsScene::PhysicsScene()
    {

    }

    int PhysicsScene::create_component(int entity_id)
    {
        auto c = new PhysicsComponent(*this, new_object_id(), *get_level(), entity_id);
        return create_object(c);
    }

    void PhysicsScene::tick(float dt)
    {

    }
}