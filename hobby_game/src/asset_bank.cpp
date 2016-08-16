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
        : m_next_asset_id(1)
    {

    }

    void AssetBank::init(Lua& lua)
    {
        m_lua = &lua;
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