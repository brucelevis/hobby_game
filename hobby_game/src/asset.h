#pragma once

#include "asset_type.h"
#include "lua_table.h"

#include <string>

namespace hg
{
    class AssetBank;

    class Asset
    {
    public:
        explicit Asset(AssetBank& bank, AssetType type);
        virtual ~Asset();

        AssetBank& get_bank() const { return m_bank; }
        AssetType get_type() const { return m_type; }

        int get_id() const { return m_id; }
        const std::string& get_name() const { return m_name; }

    protected:
        friend class AssetBank;

        /*
            Throws.
        */
        virtual void load(const std::string& file_name) = 0;

        AssetBank& m_bank;
        int m_id;
        std::string m_name;
        LuaTable m_table;

    private:
        AssetType m_type;
    };
}