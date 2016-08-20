#include "physics_scene.h"

#include "physics_component.h"
#include "physics_empty.h"

namespace hg
{
    PhysicsScene::PhysicsScene()
    {

    }

    int PhysicsScene::create_empty(int entity_id)
    {
        auto empty = new PhysicsEmpty(*this, new_object_id(), *get_level(), entity_id);
        return create_object(empty);
    }

    PhysicsEmpty* PhysicsScene::get_empty(int id) const
    {
        auto o = (PhysicsComponent*)get_object(id);
        if (o->get_physics_type() == PhysicsComponentType::empty)
            return (PhysicsEmpty*)o;

        return nullptr;
    }

    void PhysicsScene::tick(float dt)
    {

    }
}