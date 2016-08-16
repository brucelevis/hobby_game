#include "asset_bank.h"
#include "lua.h"
#include "lua_script.h"
#include "lua_table.h"
#include "lua_value.h"
#include "exception.h"

#include "bitmap_asset.h"
#include "texture_asset.h"
#include "tilemap_asset.h"

namespace hg
{
    AssetBank::AssetBank()
        : m_lua()
        , m_script_id()

        , m_next_asset_id(1)
    {

    }

    void AssetBank::init(Lua& lua)
    {
        m_lua = &lua;

        //load assets script
        m_script_id = m_lua->load_script("assets/assets.lua");
        auto script = m_lua->get_script(m_script_id);

        script->run();

        Exception bad_assets_file("Bad assets file.");

        int assets_table_ref;
        try
        {
            assets_table_ref = m_lua->get_table_ref("assets");
        }
        catch (const Exception&)
        {
            throw bad_assets_file;
        }

        LuaTable assets_table(*m_lua, assets_table_ref);

        LuaValue bitmaps_table, textures_table, tilemaps_table;
        if (!assets_table.get_value(LuaType::table, "bitmaps", bitmaps_table))
            throw bad_assets_file;
        if (!assets_table.get_value(LuaType::table, "textures", textures_table))
            throw bad_assets_file;
        if (!assets_table.get_value(LuaType::table, "tilemaps", tilemaps_table))
            throw bad_assets_file;

        std::vector<LuaValue> bitmaps_list, textures_list, tilemaps_list;
        try
        {
            bitmaps_table.get_table().to_array(bitmaps_list);
            textures_table.get_table().to_array(textures_list);
            tilemaps_table.get_table().to_array(tilemaps_list);
        }
        catch (const Exception&)
        {
            throw bad_assets_file;
        }

        std::vector<std::string> file_names;

        //bitmap files
        for (const auto& v : bitmaps_list)
        {
            if (v.get_type() == LuaType::string)
            {
                file_names.push_back(v.get_string());
            }
        }

        for (const auto& fn : file_names)
        {
            load_bitmap(fn);
        }

        //texture files
        if (!file_names.empty())
            file_names.clear();

        for (const auto& v : textures_list)
        {
            if (v.get_type() == LuaType::string)
            {
                file_names.push_back(v.get_string());
            }
        }

        for (const auto& fn : file_names)
        {
            load_texture(fn);
        }

        //tilemap files
        if(!file_names.empty())
            file_names.clear();

        for (const auto& v : tilemaps_list)
        {
            if (v.get_type() == LuaType::string)
            {
                file_names.push_back(v.get_string());
            }
        }

        for (const auto& fn : file_names)
        {
            load_tilemap(fn);
        }
    }

    void AssetBank::destroy()
    {
        if (!m_assets.empty())
        {
            for (auto a : m_assets)
                delete a;

            m_assets.clear();
        }
    }

    int AssetBank::load_bitmap(const std::string& file_name)
    {
        BitmapAsset* ba = new BitmapAsset(*this);

        try
        {
            ba->load(get_asset_type_dir(ba->get_type()) + file_name);
        }
        catch (const Exception& e)
        {
            delete ba;

            throw e;
        }

        ba->m_name = file_name;
        ba->m_id = m_next_asset_id++;

        m_assets.push_back(ba);

        return ba->m_id;
    }

    int AssetBank::load_texture(const std::string& file_name)
    {
        TextureAsset* ta = new TextureAsset(*this);

        try
        {
            ta->load(get_asset_type_dir(ta->get_type()) + file_name);
        }
        catch (const Exception& e)
        {
            delete ta;

            throw e;
        }

        ta->m_name = file_name;
        ta->m_id = m_next_asset_id++;

        m_assets.push_back(ta);

        return ta->m_id;
    }

    int AssetBank::load_tilemap(const std::string& file_name)
    {
        TilemapAsset* ta = new TilemapAsset(*this);

        try
        {
            ta->load(get_asset_type_dir(ta->get_type()) + file_name);
        }
        catch (const Exception& e)
        {
            delete ta;

            throw e;
        }

        ta->m_name = file_name;
        ta->m_id = m_next_asset_id++;

        m_assets.push_back(ta);

        return ta->m_id;
    }

    int AssetBank::get_asset_id(AssetType type, const std::string& name) const
    {
        for (auto a : m_assets)
        {
            if (a->get_type() == type && a->get_name() == name)
                return a->get_id();
        }

        return 0;
    }

    Asset* AssetBank::get_asset(AssetType type, const std::string& name) const
    {
        for (auto a : m_assets)
        {
            if (a->get_type() == type && a->get_name() == name)
                return a;
        }

        return nullptr;
    }

    Asset* AssetBank::get_asset(int id) const
    {
        for (auto a : m_assets)
        {
            if (a->get_id() == id)
                return a;
        }

        return nullptr;
    }

    BitmapAsset* AssetBank::get_bitmap(int id) const
    {
        auto a = get_asset(id);
        if (a && a->get_type() == AssetType::bitmap)
            return (BitmapAsset*)a;

        return nullptr;
    }

    TextureAsset* AssetBank::get_texture(int id) const
    {
        auto a = get_asset(id);
        if (a && a->get_type() == AssetType::texture)
            return (TextureAsset*)a;

        return nullptr;
    }

    TilemapAsset* AssetBank::get_tilemap(int id) const
    {
        auto a = get_asset(id);
        if (a && a->get_type() == AssetType::tilemap)
            return (TilemapAsset*)a;

        return nullptr;
    }
}