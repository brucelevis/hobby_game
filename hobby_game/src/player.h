#pragma once

#include <vecmath/vector.hpp>

namespace hg
{
    class Level;

    class Player
    {
    public:
        Player();

        const vcm::vec2& get_position() const { return m_position; }

    protected:
        friend class Level;

        void init(Level& level);
        void tick(float dt);

    private:
        Level* m_level;
        vcm::vec2 m_position;
    };
}