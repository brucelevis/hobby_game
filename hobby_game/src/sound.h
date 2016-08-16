#pragma once

namespace hg
{
    class Game;
    class SoundImpl;

    class Sound
    {
    public:
        Sound();
        ~Sound();

    protected:
        friend class Game;

        void init();

        void destroy();

    private:
        SoundImpl* m_impl;
    };
}