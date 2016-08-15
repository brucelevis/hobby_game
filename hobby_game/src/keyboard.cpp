#include "keyboard.h"

namespace hg
{
    Keyboard::Keyboard()
        : m_num_keys_diff()
    {
        for (auto& k : m_keys)
            k = false;

        for (auto& k : m_prev_keys)
            k = false;

        for (auto& k : m_keys_diff)
            k = Keycode::none;
    }

    bool Keyboard::is_key_down(Keycode code) const
    {
        return m_keys[(int)code];
    }

    bool Keyboard::was_key_pressed(Keycode code) const
    {
        return m_keys[(int)code] && !m_prev_keys[(int)code];
    }

    bool Keyboard::was_key_released(Keycode code) const
    {
        return m_prev_keys[(int)code] && !m_keys[(int)code];
    }

    void Keyboard::on_key_change(Keycode code, bool state)
    {
        m_keys[(int)code] = state;

        m_keys_diff[m_num_keys_diff++] = code;
    }

    void Keyboard::clear_key_diffs()
    {
        for (int i = 0; i < m_num_keys_diff; ++i)
        {
            int k = (int)m_keys_diff[i];
            m_prev_keys[k] = m_keys[k];
        }

        m_num_keys_diff = 0;
    }
}