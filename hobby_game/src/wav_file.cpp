#include "wav_file.h"

#include "exception.h"

#include "types.h"

#include <fstream>
#include <vector>

namespace hg
{
    WavFile::WavFile()
    {

    }

    void WavFile::load(const std::string& file_name)
    {
        std::ifstream file(file_name, std::ios::in | std::ios::binary | std::ios::ate);
        if (!file)
        {
            throw Exception("Could not open wav file \"" + file_name + "\".");
        }

        ulong size = (ulong)file.tellg();
        file.seekg(0, file.beg);

        std::vector<char> buff(size);
        if (!file.read(buff.data(), size))
            throw Exception("Error reading wav file \"" + file_name + "\".");

        file.close();

        Exception bad_file("Bad wav file \"" + file_name + "\".");

        char* b = buff.data();
        char c[4];
        memcpy(c, b, 4);

        if (strncmp(c, "RIFF", 4) != 0)
        {
            throw bad_file;
        }

        b += 4;
        uint chunk_size;
        memcpy(&chunk_size, b, 4);

        b += 4;

        memcpy(c, b, 4);
        if (strncmp(c, "WAVE", 4) != 0)
            throw bad_file;

        b += 4;
        memcpy(c, b, 4);

        if (strncmp(c, "fmt ", 4) != 0)
        {
            throw bad_file;
        }

        b += 4;

        b += 6;

        ushort channels;
        uint samples_per_sec;

        memcpy(&channels, b, 2);
        b += 2;
        memcpy(&samples_per_sec, b, 4);
        b += 4;

        b += 6;

        ushort bits_per_sample;
        memcpy(&bits_per_sample, b, 2);

        b += 2;

        //b += 24;

        memcpy(c, b, 4);
        if (strncmp(c, "data", 4) != 0)
        {
            throw bad_file;
        }

        b += 4;

        uint data_size;
        memcpy(&data_size, b, 4);

        b += 4;

        std::vector<byte> data;
        data.resize(data_size);
        memcpy(data.data(), b, data_size);

        m_num_channels = channels;
        m_sample_rate = samples_per_sec;
        m_bits_per_sample = bits_per_sample;
        m_data.swap(data);
    }
}