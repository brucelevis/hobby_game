#include "behavior_component.h"

#include "behavior_scene.h"

namespace hg
{
    BehaviorComponent::BehaviorComponent(BehaviorScene& scene, int id, Level& level, int entity_id)
        : Component(scene, id, level, entity_id)
    {

    }

    BehaviorComponent::~BehaviorComponent()
    {

    }
}