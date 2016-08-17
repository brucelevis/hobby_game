#include "physics_component.h"
#include "physics_scene.h"

namespace hg
{
    PhysicsComponent::PhysicsComponent(PhysicsScene& scene, int id, Level& level, int entity_id)
        : Component(scene, id, level, entity_id)

        , m_mass(1.0f)
    {

    }

    PhysicsComponent::~PhysicsComponent()
    {

    }
}