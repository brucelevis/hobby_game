#include "behavior_asset.h"

#include "lua_value.h"
#include "exception.h"

namespace hg
{
    BehaviorAsset::BehaviorAsset(AssetBank& bank, int id)
        : Asset(bank, id)
    {

    }

    void BehaviorAsset::load(const std::string& file_name)
    {
        Asset::load(file_name);

        Exception bad_file("Bad behavior asset file \"" + file_name + "\".");

        LuaValue init_func, tick_func;

        int b = 0;
        b += !m_table.get_value(LuaType::function, "init", init_func);
        b += !m_table.get_value(LuaType::function, "tick", tick_func);
        
        if (b)
            throw bad_file;

        m_init_func = init_func.get_function();
        m_tick_func = tick_func.get_function();
    }

    void BehaviorAsset::init(const LuaTable& self)
    {
        auto params = { LuaValue(self) };
        std::vector<LuaValue> results;
        m_init_func.call(params.begin(), 1, results);
    }

    void BehaviorAsset::tick(const LuaTable& self, float dt)
    {
        auto params = { LuaValue(self), LuaValue(dt) };
        std::vector<LuaValue> results;
        m_tick_func.call(params.begin(), 2, results);
    }
}