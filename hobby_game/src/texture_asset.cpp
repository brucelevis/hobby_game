#include "texture_asset.h"
#include "asset_bank.h"

#include "lua_value.h"

#include "exception.h"

namespace hg
{
    TextureAsset::TextureAsset(AssetBank& bank, int id)
        : Asset(bank, id, AssetType::texture)

        , m_bitmap_asset()
        , m_format(TextureFormat::undefined)
        , m_wrap_mode(TextureWrap::undefined)
        , m_filter_mode(TextureFilter::undefined)
    {

    }

    void TextureAsset::load(const std::string& file_name)
    {
        Asset::load(file_name);

        Exception bad_file("Bad texture asset file \"" + file_name + "\".");

        LuaValue bitmap, format, wrap_mode, filter_mode;

        int b = 0;
        b += !m_table.get_value(LuaType::string, "bitmap", bitmap);
        b += !m_table.get_value(LuaType::string, "format", format);
        b += !m_table.get_value(LuaType::string, "wrap_mode", wrap_mode);
        b += !m_table.get_value(LuaType::string, "filter_mode", filter_mode);

        if (b)
            throw bad_file;

        m_bitmap_asset = m_bank.get_asset_id(AssetType::bitmap, bitmap.get_string());
        if (!m_bitmap_asset)
            throw bad_file;

        if (format.get_string() == "R")
            m_format = TextureFormat::r;
        else if (format.get_string() == "RGB")
            m_format = TextureFormat::rgb;
        else if (format.get_string() == "RGBA")
            m_format = TextureFormat::rgba;
        else
            throw bad_file;

        if (wrap_mode.get_string() == "clamp")
            m_wrap_mode = TextureWrap::clamp;
        else if (wrap_mode.get_string() == "repeat")
            m_wrap_mode = TextureWrap::repeat;
        else
            throw bad_file;

        if (filter_mode.get_string() == "linear")
            m_filter_mode = TextureFilter::linear;
        else if (filter_mode.get_string() == "nearest")
            m_filter_mode = TextureFilter::nearest;
        else
            throw bad_file;
    }
}