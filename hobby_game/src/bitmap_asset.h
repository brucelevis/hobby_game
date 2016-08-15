#pragma once

#include "asset.h"
#include "bitmap.h"

namespace hg
{
    class BitmapAsset
        : public Asset
    {
    public:
        BitmapAsset(AssetBank& bank);

        const Bitmap& get_bitmap() const { return m_bitmap; }

    protected:
        friend class AssetBank;

        void load(const std::string& file_name) override;

    private:
        Bitmap m_bitmap;
    };
}