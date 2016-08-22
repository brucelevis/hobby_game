#pragma once

#include "behavior_component.h"

namespace hg
{
    class BehaviorScene;

    class BehaviorScript
        : public BehaviorComponent
    {
    public:
        BehaviorScript(BehaviorScene& scene, int id, Level& level, int entity_id);

        void set_script_id(int id);
        int get_script_id() const;

        BehaviorComponentType get_behavior_type() const override { return BehaviorComponentType::script; }

    protected:
        friend class BehaviorScene;

    private:
        int m_script_id;
    };
}