#pragma once

#include "asset.h"
#include "sound_clip.h"

namespace hg
{
    class SoundClipAsset
        : public Asset
    {
    public:
        SoundClipAsset(AssetBank& bank);

        const SoundClip& get_sound_clip() const { return m_sound_clip; }

    protected:
        friend class AssetBank;

        void load(const std::string& file_name) override;

    private:
        SoundClip m_sound_clip;
    };
}