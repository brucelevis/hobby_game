#pragma once

#include "asset_type.h"
#include "object.h"
#include "lua_table.h"

#include <string>

namespace hg
{
    class AssetBank;

    class Asset
        : public Object
    {
    public:
        explicit Asset(AssetBank& bank, int id, AssetType type);
        virtual ~Asset();

        AssetBank& get_bank() const { return m_bank; }
        AssetType get_type() const { return m_type; }

        const std::string& get_name() const { return m_name; }

    protected:
        friend class AssetBank;

        /*
            Throws.
        */
        virtual void load(const std::string& file_name) = 0;

        AssetBank& m_bank;

        std::string m_name;
        LuaTable m_table;

    private:
        AssetType m_type;
    };
}