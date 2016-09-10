#pragma once

#include "component.h"
#include "behavior_component_type.h"

namespace hg
{
    class BehaviorScene;

    class BehaviorComponent
        : public Component
    {
    public:
        BehaviorComponent(BehaviorScene& scene, int id, Level& level, int entity_id);
        virtual ~BehaviorComponent();

        virtual BehaviorComponentType get_behavior_type() const = 0;

        ComponentType get_component_type() const override { return ComponentType::behavior; }

    protected:
        friend class BehaviorScene;

        virtual void init();
        virtual void tick(float dt);

    private:

    };
}