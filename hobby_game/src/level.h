#pragma once

#include "player.h"
#include "tilemap.h"

namespace hg
{
    class Game;

    class Level
    {
    public:
        Level();

        Game* get_game() const { return m_game; }

        const Player& get_player() const { return m_player; }
        const Tilemap& get_tilemap() const { return m_tilemap; }

    protected:
        friend class Game;

        void init(Game& game);

        void tick(float dt);

    private:
        Game* m_game;
        Player m_player;
        Tilemap m_tilemap;
    };
}