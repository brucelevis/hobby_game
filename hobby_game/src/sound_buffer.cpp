#include "sound_buffer.h"

#include "sound_clip_asset.h"

#include "exception.h"

#include <AL/al.h>

namespace hg
{
    SoundBuffer::SoundBuffer()
        : m_buffer()
    {

    }

    void SoundBuffer::create(const SoundClipAsset& sound_clip_asset)
    {
        destroy();

        alGenBuffers(1, &m_buffer);

        const SoundClip& sound_clip = sound_clip_asset.get_sound_clip();

        ALenum format;
        bool bad_format = false;
        if (sound_clip.get_num_channels() == 1)
        {
            if (sound_clip.get_bits_per_sample() == 8)
                format = AL_FORMAT_MONO8;
            else if (sound_clip.get_bits_per_sample() == 16)
                format = AL_FORMAT_MONO16;
            else
                bad_format = true;
        }
        else if (sound_clip.get_num_channels() == 2)
        {
            if (sound_clip.get_bits_per_sample() == 8)
                format = AL_FORMAT_STEREO8;
            else if (sound_clip.get_bits_per_sample() == 16)
                format = AL_FORMAT_STEREO16;
            else
                bad_format = true;
        }
        else
        {
            bad_format = true;
        }

        if (bad_format)
        {
            throw Exception("Bad format in sound_clip asset \"" + sound_clip_asset.get_name() + "\" in SoundBuffer::create()");
        }

        alBufferData(m_buffer, format, sound_clip.get_data(), sound_clip.get_data_size(), sound_clip.get_sample_rate());
    }

    void SoundBuffer::destroy()
    {
        if (m_buffer)
        {
            alDeleteBuffers(1, &m_buffer);
            m_buffer = 0;
        }
    }
}