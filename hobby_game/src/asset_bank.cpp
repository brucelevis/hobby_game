#include "asset_bank.h"
#include "lua.h"
#include "lua_script.h"
#include "lua_table.h"
#include "lua_value.h"
#include "exception.h"

#include "bitmap_asset.h"
#include "sound_clip_asset.h"
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

        LuaValue bitmaps_table, sound_clips_table, textures_table, tilemaps_table;
        if (!assets_table.get_value(LuaType::table, "bitmaps", bitmaps_table))
            throw bad_assets_file;
        if (!assets_table.get_value(LuaType::table, "sound_clips", sound_clips_table))
            throw bad_assets_file;
        if (!assets_table.get_value(LuaType::table, "textures", textures_table))
            throw bad_assets_file;
        if (!assets_table.get_value(LuaType::table, "tilemaps", tilemaps_table))
            throw bad_assets_file;

        std::vector<LuaValue> bitmaps_list, sound_clips_list, textures_list, tilemaps_list;
        try
        {
            bitmaps_table.get_table().to_array(bitmaps_list);
            sound_clips_table.get_table().to_array(sound_clips_list);
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
            load_asset(AssetType::bitmap, fn);
        }

        //sound clip files
        if (!file_names.empty())
            file_names.clear();

        for (const auto& v : sound_clips_list)
        {
            if (v.get_type() == LuaType::string)
            {
                file_names.push_back(v.get_string());
            }
        }

        for (const auto& fn : file_names)
        {
            load_asset(AssetType::sound_clip, fn);
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
            load_asset(AssetType::texture, fn);
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
            load_asset(AssetType::tilemap, fn);
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

    int AssetBank::load_asset(AssetType type, const std::string& file_name)
    {
        Asset* asset = nullptr;
        
        switch (type)
        {
        case AssetType::bitmap:
            asset = new BitmapAsset(*this);
            break;
        case AssetType::sound_clip:
            asset = new SoundClipAsset(*this);
            break;
        case AssetType::texture:
            asset = new TextureAsset(*this);
            break;
        case AssetType::tilemap:
            asset = new TilemapAsset(*this);
            break;
        default:
            throw Exception("Bad AssetType in load_asset()");
            break;
        }

        try
        {
            asset->load(get_asset_type_dir(asset->get_type()) + file_name);
        }
        catch (const Exception& e)
        {
            delete asset;

            throw e;
        }

        asset->m_name = file_name;
        asset->m_id = m_next_asset_id++;

        m_assets.push_back(asset);

        return asset->m_id;
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

    SoundClipAsset* AssetBank::get_sound_clip(int id) const
    {
        auto a = get_asset(id);
        if (a && a->get_type() == AssetType::sound_clip)
            return (SoundClipAsset*)a;

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