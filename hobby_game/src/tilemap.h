#pragma once

#include <vector>
#include <string>

#include "bitmap.h"
#include "texture.h"

namespace hg
{
    class TilemapAsset;

    struct TileInfo
    {
        int id;
        int x, y, w, h;
        int clip_x, clip_y, clip_w, clip_h;
    };

    class Tilemap
    {
    public:
        Tilemap();

        /*
            Creates a tilemap from a TilemapAsset.
        */
        void create(const TilemapAsset& asset);

        /*
            Returns true if the x, y position is within the tilemap's bounds.
        */
        bool check_xy(int x, int y) const;

        void set_tile(int x, int y, int id);
        int get_tile(int x, int y) const;

        /*
            Returns the index of the tile at this x, y position.
            The index corresponds to the internal tilemap array.
        */
        int get_tile_index(int x, int y) const;

        /*
            Returns the tile ID of the tile with this index and stores info about the tile in the out param.
        */
        bool get_tile_info(int index, TileInfo& out) const;

        int get_width() const { return m_width; }
        int get_height() const { return m_height; }
        int get_tile_width() const { return m_tile_width; }
        int get_tile_height() const { return m_tile_height; }

        const int* get_tiles() const { return m_tiles.data(); }
        int get_num_tiles() const { return (int)m_tiles.size(); }

        const Texture& get_texture() const { return m_texture; }

    private:
        int m_width;
        int m_height;
        int m_tile_width;
        int m_tile_height;

        std::vector<int> m_tiles; //list of tile IDs

        Texture m_texture;
    };
}