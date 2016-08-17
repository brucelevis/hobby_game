#pragma once

#include "types.h"

namespace hg
{
    class SoundClipAsset;

    class SoundBuffer
    {
    public:
        SoundBuffer();

        void create(const SoundClipAsset& sound_clip);
        void destroy();

        uint get_handle() const { return m_buffer; }

    private:
        uint m_buffer;
    };
}