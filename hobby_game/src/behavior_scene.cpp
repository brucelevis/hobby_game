#include "behavior_scene.h"

#include "behavior_script.h"
#include "level.h"
#include "game.h"
#include "lua_value.h"

#include <lua.hpp>

namespace hg
{
    BehaviorScene::BehaviorScene()
    {

    }

    void BehaviorScene::tick(float dt)
    {
        auto objects = get_objects();
        int s = get_num_objects();
        for (int i = 0; i < s; ++i)
        {
            auto o = objects[i];
            auto comp = (BehaviorComponent*)o;
            comp->tick(dt);
        }
    }

    int BehaviorScene::create_script(int entity_id, int script_asset_id)
    {
        auto script_asset = get_level()->get_game()->get_assets().get_behavior(script_asset_id);
        auto script = new BehaviorScript(*this, new_object_id(), *get_level(), entity_id, *script_asset);

        LuaTable table;
        table.create(get_level()->get_game()->get_lua());
        table.set_value("entity_id", entity_id);

        script->init_self(table);

        auto o = create_object(script);

        script->init();

        return o;
    }

    BehaviorScript* BehaviorScene::get_script(int id) const
    {
        auto o = (BehaviorScript*)get_object(id);
        if (o->get_behavior_type() == BehaviorComponentType::script)
            return (BehaviorScript*)o;

        return nullptr;
    }
}