#include "sound_source.h"

#include "sound_buffer.h"

#include <AL/al.h>

namespace hg
{
    SoundSource::SoundSource()
        : m_source()
    {

    }

    void SoundSource::create()
    {
        destroy();

        alGenSources(1, &m_source);
    }

    void SoundSource::destroy()
    {
        if (m_source)
        {
            alDeleteSources(1, &m_source);
            m_source = 0;
        }
    }

    void SoundSource::set_buffer(const SoundBuffer& buffer)
    {
        ALuint b = buffer.get_handle();
        alSourceQueueBuffers(m_source, 1, &b);
    }

    void SoundSource::play()
    {
        alSourcePlay(m_source);
    }
}