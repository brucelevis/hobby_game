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
        Asset(AssetBank& bank, int id);
        virtual ~Asset();

        AssetBank& get_bank() const { return m_bank; }
        
        virtual AssetType get_type() const = 0;

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
    };
}