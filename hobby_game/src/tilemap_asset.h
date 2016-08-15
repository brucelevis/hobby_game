#pragma once

#include "asset.h"

#include <vector>

namespace hg
{
    class TilemapAsset
        : public Asset
    {
    public:
        TilemapAsset(AssetBank& bank);

        int get_texture_asset() const { return m_texture_asset; }

        int get_width() const { return m_width; }
        int get_height() const { return m_height; }
        int get_tile_width() const { return m_tile_width; }
        int get_tile_height() const { return m_tile_height; }

        const int* get_tiles() const { return m_tiles.data() + 0; }
        int get_num_tiles() const { return (int)m_tiles.size(); }

    protected:
        friend class AssetBank;

        /*
            Throws.
        */
        void load(const std::string& file_name) override;

    private:
        int m_texture_asset;

        int m_width;
        int m_height;
        int m_tile_width;
        int m_tile_height;
        std::vector<int> m_tiles;
    };
}