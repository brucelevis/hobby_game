#include "bitmap_asset.h"

#include "lua_value.h"

#include "exception.h"

namespace hg
{
    BitmapAsset::BitmapAsset(AssetBank& bank, int id)
        : Asset(bank, id)
    {

    }

    void BitmapAsset::load(const std::string& file_name)
    {
        Asset::load(file_name);

        LuaValue bmp_file_name;
        if (!m_table.get_value(LuaType::string, "file_name", bmp_file_name))
            throw Exception("Bad bitmap asset file \"" + file_name + "\".");

        m_bitmap.load(get_asset_type_dir(AssetType::bitmap) + bmp_file_name.get_string());
    }
}