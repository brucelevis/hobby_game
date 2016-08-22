#include "behavior_script.h"

namespace hg
{
    BehaviorScript::BehaviorScript(BehaviorScene& scene, int id, Level& level, int entity_id)
        : BehaviorComponent(scene, id, level, entity_id)
        , m_script_id()
    {

    }

    void BehaviorScript::set_script_id(int id)
    {
        if (m_script_id != id)
        {
            m_script_id = id;
        }
    }

    int BehaviorScript::get_script_id() const
    {
        return m_script_id;
    }
}