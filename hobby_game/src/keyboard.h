#pragma once

#include "keycode.h"

namespace hg
{
    class Game;

    class Keyboard
    {
    public:
        Keyboard();

        /*
            Returns true if the key with this code is being held down.
        */
        bool is_key_down(Keycode code) const;

        /*
            Returns true if the key with this code was immidiately pressed this frame.
        */
        bool was_key_pressed(Keycode code) const;

        /*
            Returns true if the key with this code was immidiately released (unpressed) this frame.
        */
        bool was_key_released(Keycode code) const;

    protected:
        friend class Game;

        /*
            Called by the Game class when a key is pressed/released (changes state; true = pressed, false = released).
        */
        void on_key_change(Keycode code, bool state);

        void clear_key_diffs();

    private:
        bool m_keys[(int)Keycode::num_codes];
        bool m_prev_keys[(int)Keycode::num_codes];

        static const int MAX_KEYS_DIFF = 512;
        Keycode m_keys_diff[MAX_KEYS_DIFF];
        int m_num_keys_diff;
    };
}