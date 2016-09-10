#pragma once

#include "behavior_component.h"
#include "lua_table.h"

namespace hg
{
    class BehaviorScene;
    class BehaviorAsset;

    class BehaviorScript
        : public BehaviorComponent
    {
    public:
        BehaviorScript(BehaviorScene& scene, int id, Level& level, int entity_id, BehaviorAsset& script_asset);

        BehaviorComponentType get_behavior_type() const override { return BehaviorComponentType::script; }

    protected:
        friend class BehaviorScene;

        void init_self(const LuaTable& self);

        void init() override;
        void tick(float dt) override;

    private:
        BehaviorAsset* m_script_asset;
        LuaTable m_self;
    };
}