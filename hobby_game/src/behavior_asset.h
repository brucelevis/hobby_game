#pragma once

#include "asset.h"

#include "lua_table.h"
#include "lua_function.h"

namespace hg
{
    class BehaviorAsset
        : public Asset
    {
    public:
        BehaviorAsset(AssetBank& bank, int id);

        void init(const LuaTable& self);
        void tick(const LuaTable& self, float dt);

        AssetType get_type() const override { return AssetType::behavior; }
        
    protected:
        friend class AssetBank;

        void load(const std::string& file_name) override;

    private:
        LuaFunction m_init_func;
        LuaFunction m_tick_func;
    };
}