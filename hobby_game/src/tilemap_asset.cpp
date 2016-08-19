#include "tilemap_asset.h"
#include "asset_bank.h"

#include "lua_value.h"

#include "exception.h"

namespace hg
{
    TilemapAsset::TilemapAsset(AssetBank& bank, int id)
        : Asset(bank, id)

        , m_texture_asset()
        , m_width()
        , m_height()
        , m_tile_width()
        , m_tile_height()
    {

    }

    void TilemapAsset::load(const std::string& file_name)
    {
        Asset::load(file_name);

        Exception bad_file("Bad tilemap asset file \"" + file_name + "\".");

        LuaValue texture, width, height, tile_width, tile_height;
        LuaValue tiles;

        int b = 0;
        b += !m_table.get_value(LuaType::string, "texture", texture);
        b += !m_table.get_value(LuaType::_int, "width", width);
        b += !m_table.get_value(LuaType::_int, "height", height);
        b += !m_table.get_value(LuaType::_int, "tile_width", tile_width);
        b += !m_table.get_value(LuaType::_int, "tile_height", tile_height);
        b += !m_table.get_value(LuaType::table, "tiles", tiles);

        if (b)
            throw bad_file;

        m_texture_asset = m_bank.get_asset_id(AssetType::texture, texture.get_string());
        if (!m_texture_asset)
            throw bad_file;

        m_width = width.get_int();
        m_height = height.get_int();
        m_tile_width = tile_width.get_int();
        m_tile_height = tile_height.get_int();

        std::vector<LuaValue> tiles_array;
        tiles.get_table().to_array(tiles_array);

        m_tiles.reserve(tiles_array.size());
        for (const auto& value : tiles_array)
        {
            if (value.get_type() != LuaType::_int)
                throw bad_file;

            m_tiles.push_back(value.get_int());
        }
    }
}