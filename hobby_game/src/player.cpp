#include "player.h"

#include "level.h"
#include "game.h"

namespace hg
{
    Player::Player()
        : m_level()
    {

    }

    void Player::init(Level& level)
    {
        m_level = &level;
    }

    void Player::tick(float dt)
    {
        auto& kb = m_level->get_game()->get_keyboard();
        
        vcm::vec2 dir;
        static const float speed = 150;
        if (kb.is_key_down(Keycode::right))
        {
            dir.x = 1.0f;
        }
        else if (kb.is_key_down(Keycode::left))
        {
            dir.x = -1.0f;
        }

        if (kb.is_key_down(Keycode::down))
        {
            dir.y = 1.0f;
        }
        else if (kb.is_key_down(Keycode::up))
        {
            dir.y = -1.0f;
        }

        dir = vcm::normalize(dir);
        m_position += dir * speed * dt;
    }
}