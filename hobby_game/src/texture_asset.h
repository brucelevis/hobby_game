#pragma once

#include "asset.h"
#include "texture_format.h"

namespace hg
{
    class TextureAsset
        : public Asset
    {
    public:
        TextureAsset(AssetBank& bank, int id);

        int get_bitmap_asset() const { return m_bitmap_asset; }
        TextureFormat get_format() const { return m_format; }
        TextureWrap get_wrap_mode() const { return m_wrap_mode; }
        TextureFilter get_filter_mode() const { return m_filter_mode; }

    protected:
        friend class AssetBank;

        void load(const std::string& file_name) override;

    private:
        int m_bitmap_asset;
        TextureFormat m_format;
        TextureWrap m_wrap_mode;
        TextureFilter m_filter_mode;
    };
}