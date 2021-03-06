#pragma once

#include "types.h"
#include "sound_buffer.h"

#include <string>
#include <vector>

namespace hg
{
    class SoundClip
    {
    public:
        SoundClip();

        void load(const std::string& file_name);

        void create_buffer();
        void destroy_buffer();

        int get_num_channels() const { return m_num_channels; }
        int get_sample_rate() const { return m_sample_rate; }
        int get_bits_per_sample() const { return m_bits_per_sample; }
        
        const byte* get_data() const { return m_data.data(); }
        uint get_data_size() const { return (uint)m_data.size(); }

        const SoundBuffer& get_buffer() const { return m_buffer; }

    private:
        int m_num_channels;
        int m_sample_rate;
        int m_bits_per_sample;
        std::vector<byte> m_data;

        SoundBuffer m_buffer;
    };
}