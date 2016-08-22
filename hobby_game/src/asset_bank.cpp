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
#include "behavior_asset.h"

namespace hg
{
    AssetBank::AssetBank()
    {

    }

    void AssetBank::init(Lua& lua)
    {
        m_lua = &lua;
    }

    void AssetBank::destroy()
    {
        clear();
    }

    int AssetBank::load_asset(AssetType type, const std::string& file_name)
    {
        Asset* asset = nullptr;
        
        int id = new_object_id();

        switch (type)
        {
        case AssetType::bitmap:
            asset = new BitmapAsset(*this, id);
            break;
        case AssetType::sound_clip:
            asset = new SoundClipAsset(*this, id);
            break;
        case AssetType::texture:
            asset = new TextureAsset(*this, id);
            break;
        case AssetType::tilemap:
            asset = new TilemapAsset(*this, id);
            break;
        case AssetType::behavior:
            asset = new BehaviorAsset(*this, id);
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

        return create_object(asset);
    }

    int AssetBank::get_asset_id(AssetType type, const std::string& name) const
    {
        auto os = get_objects();
        for (int i = 0; i < get_num_objects(); ++i)
        {
            auto a = (Asset*)(os[i]);
            if (a->get_type() == type && a->get_name() == name)
                return a->get_id();
        }

        return 0;
    }

    Asset* AssetBank::get_asset(AssetType type, const std::string& name) const
    {
        return (Asset*)get_object(get_asset_id(type, name));
    }

    Asset* AssetBank::get_asset(int id) const
    {
        return (Asset*)get_object(id);
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

    BehaviorAsset* AssetBank::get_behavior(int id) const
    {
        auto a = get_asset(id);
        if (a && a->get_type() == AssetType::behavior)
            return (BehaviorAsset*)a;

        return nullptr;
    }
}