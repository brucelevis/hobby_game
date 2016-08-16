#pragma once

#include "asset.h"
#include "wav_file.h"

namespace hg
{
    class SoundClipAsset
        : public Asset
    {
    public:
        SoundClipAsset(AssetBank& bank);

        const WavFile& get_wav_file() const { return m_wav_file; }

    protected:
        friend class AssetBank;

        void load(const std::string& file_name) override;

    private:
        WavFile m_wav_file;
    };
}