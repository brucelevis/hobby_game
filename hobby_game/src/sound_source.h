#pragma once

#include "types.h"

namespace hg
{
    class SoundBuffer;

    class SoundSource
    {
    public:
        SoundSource();

        void create();
        void destroy();

        void set_buffer(const SoundBuffer& buffer);

        void play();

        uint get_handle() const { return m_source; }

    private:
        uint m_source;
    };
}