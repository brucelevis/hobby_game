#include "asset.h"

#include "asset_bank.h"
#include "lua.h"
#include "exception.h"
#include "lua_script.h"

namespace hg
{
    Asset::Asset(AssetBank& bank, AssetType type)
        : m_bank(bank)
        , m_type(type)

        , m_id()
    {

    }

    Asset::~Asset()
    {

    }

    void Asset::load(const std::string& file_name)
    {
        auto lua = m_bank.get_lua();

        int script_id = lua->load_script(file_name);
        auto script = lua->get_script(script_id);

        std::vector<LuaValue> results;
        script->run(results);

        if (results.empty() || results.size() > 1 || results[0].get_type() != LuaType::table)
            throw Exception("Bad asset file \"" + file_name + "\".");

        auto& result = results[0];
        
        m_table = result.get_table();
    }
}