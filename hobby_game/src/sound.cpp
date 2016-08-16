#include "sound.h"

#include "exception.h"

#include <AL/al.h>
#include <AL/alc.h>

#include "wav_file.h"

namespace hg
{
    class SoundImpl
    {
    public:
        SoundImpl();

        void init();
        void destroy();

    private:
        ALCdevice* m_device;
        ALCcontext* m_context;
    };

    SoundImpl::SoundImpl()
        : m_device()
        , m_context()
    {

    }

    void SoundImpl::init()
    {
        m_device = alcOpenDevice(nullptr);
        if (m_device)
        {
            m_context = alcCreateContext(m_device, nullptr);
            if (m_context)
            {
                alcMakeContextCurrent(m_context);
            }
            else
            {
                throw Exception("Could not create OpenAL context.");
            }
        }
        else
        {
            throw Exception("Could not create OpenAL device.");
        }

        WavFile file;
        file.load("assets/music/Walkin Contradiction.wav");

        ALuint buffer;
        alGenBuffers(1, &buffer);

        alBufferData(buffer, AL_FORMAT_STEREO16, file.get_data(), file.get_data_size(), file.get_sample_rate());

        ALuint source;
        alGenSources(1, &source);
        alSourceQueueBuffers(source, 1, &buffer);
        alSourcePlay(source);
    }

    void SoundImpl::destroy()
    {
        alcDestroyContext(m_context);
        m_context = nullptr;

        alcCloseDevice(m_device);
        m_device = nullptr;
    }

    Sound::Sound()
        : m_impl()
    {
        m_impl = new SoundImpl();
    }

    Sound::~Sound()
    {
        delete m_impl;
    }

    void Sound::init()
    {
        m_impl->init();
    }

    void Sound::destroy()
    {
        m_impl->destroy();
    }
}