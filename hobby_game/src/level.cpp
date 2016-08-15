#include "level.h"

#include "game.h"
#include "asset_bank.h"

namespace hg
{
    Level::Level()
        : m_game()
    {

    }

    static bool check_rects(const vcm::vec4& a, const vcm::vec4& b)
    {
        if (a.x + a.z < b.x)
            return false;
        if (a.y + a.w < b.y)
            return false;
        if (a.x > b.x + b.z)
            return false;
        if (a.y > b.y + b.w)
            return false;

        return true;
    }

    void Level::init(Game& game)
    {
        m_game = &game;

        m_player.init(*this);
        
        int tilemap_asset_id = game.get_assets().get_asset_id(AssetType::tilemap, "test.lua");
        auto tilemap_asset = game.get_assets().get_tilemap(tilemap_asset_id);
        m_tilemap.create(*tilemap_asset);
    }

    void Level::tick(float dt)
    {
        m_player.tick(dt);
    }
}