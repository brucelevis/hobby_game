#pragma once

#include "asset.h"
#include "bitmap.h"

namespace hg
{
    class BitmapAsset
        : public Asset
    {
    public:
        BitmapAsset(AssetBank& bank, int id);

        const Bitmap& get_bitmap() const { return m_bitmap; }

        AssetType get_type() const override { return AssetType::bitmap; }

    protected:
        friend class AssetBank;

        void load(const std::string& file_name) override;

    private:
        Bitmap m_bitmap;
    };
}