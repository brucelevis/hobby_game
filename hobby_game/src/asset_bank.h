#pragma once

#include "asset_type.h"

#include <vector>
#include <string>

namespace hg
{
    class Game;
    class Asset;
    class Lua;

    class BitmapAsset;
    class SoundClipAsset;
    class TextureAsset;
    class TilemapAsset;

    class AssetBank
    {
    public:
        AssetBank();

        Lua* get_lua() const { return m_lua; }

    protected:
        friend class Game;

        /*
            Throws.
        */
        void init(Lua& lua);

        void destroy();

    public:
        /*
            Loads an asset with this file_name. (looks in the folder corresponding to the AssetType)
            "assets/{corresponding directory for type}/" not needed before file's actual name because of get_asset_type_dir()
        */
        int load_asset(AssetType type, const std::string& file_name);
        
        int get_asset_id(AssetType type, const std::string& name) const;
        Asset* get_asset(AssetType type, const std::string& name) const;
        Asset* get_asset(int id) const;

        BitmapAsset* get_bitmap(int id) const;
        SoundClipAsset* get_sound_clip(int id) const;
        TextureAsset* get_texture(int id) const;
        TilemapAsset* get_tilemap(int id) const;

    private:
        Lua* m_lua;

        int m_script_id;

        std::vector<Asset*> m_assets;
        int m_next_asset_id;
    };
}