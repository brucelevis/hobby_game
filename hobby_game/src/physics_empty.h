#pragma once

#include "physics_component.h"

namespace hg
{
    class PhysicsEmpty
        : public PhysicsComponent
    {
    public:
        PhysicsEmpty(PhysicsScene& scene, int id, Level& level, int entity_id);

        PhysicsComponentType get_physics_type() const override { return PhysicsComponentType::empty; }
    };
}