#include "tilemap.h"
#include "exception.h"
#include "util.h"

#include "tilemap_asset.h"
#include "asset_bank.h"

namespace hg
{
    Tilemap::Tilemap()
        : m_width()
        , m_height()
        , m_tile_width()
        , m_tile_height()
    {

    }

    void Tilemap::create(const TilemapAsset& asset)
    {
        m_width = asset.get_width();
        m_height = asset.get_height();
        m_tile_width = asset.get_tile_width();
        m_tile_height = asset.get_tile_height();

        m_tiles.resize(m_width * m_height);
        for (int i = 0; i < asset.get_num_tiles(); ++i)
        {
            m_tiles[i] = asset.get_tiles()[i];
        }

        //temporary until we have a runtime asset system
        int texture_asset_id = asset.get_texture_asset();
        m_texture.create(*asset.get_bank().get_texture(texture_asset_id));
    }

    bool Tilemap::check_xy(int x, int y) const
    {
        return x >= 0 && y >= 0 && x < m_width && y < m_height;
    }

    void Tilemap::set_tile(int x, int y, int id)
    {
        if (check_xy(x, y))
            m_tiles[y * m_height + x] = id;
    }

    int Tilemap::get_tile(int x, int y) const
    {
        if (check_xy(x, y))
            return m_tiles[y * m_height + x];
        return -1;
    }

    int Tilemap::get_tile_index(int x, int y) const
    {
        if (check_xy(x, y))
            return y * m_height + x;
        return -1;
    }

    bool Tilemap::get_tile_info(int index, TileInfo& out) const
    {
        if (index < 0 || index >= (int)m_tiles.size())
            return false;

        if (!m_texture.exists())
            throw Exception("Tried to get_tile_info() on tilemap with invalid texture.");

        int x = index % m_width;
        int y = index / m_width;

        out.id = m_tiles[index];

        out.x = x * m_tile_width;
        out.y = y * m_tile_height;
        out.w = m_tile_width;
        out.h = m_tile_height;

        int tex_width = m_texture.get_width() / m_tile_width;

        out.clip_x = (out.id % tex_width) * m_tile_width;
        out.clip_y = (out.id / tex_width) * m_tile_height;
        out.clip_w = m_tile_width;
        out.clip_h = m_tile_height;

        return true;
    }
}