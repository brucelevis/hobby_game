#include "behavior_script.h"
#include "behavior_asset.h"

namespace hg
{
    BehaviorScript::BehaviorScript(BehaviorScene& scene, int id, Level& level, int entity_id, BehaviorAsset& script_asset)
        : BehaviorComponent(scene, id, level, entity_id)
        , m_script_asset(&script_asset)
    {

    }

    void BehaviorScript::init_self(const LuaTable& self)
    {
        m_self = self;
    }

    void BehaviorScript::init()
    {
        BehaviorComponent::init();

        m_script_asset->init(m_self);
    }

    void BehaviorScript::tick(float dt)
    {
        BehaviorComponent::tick(dt);

        m_script_asset->tick(m_self, dt);
    }
}