#include "sound_clip_asset.h"

#include "lua_value.h"
#include "lua_table.h"
#include "exception.h"

namespace hg
{
    SoundClipAsset::SoundClipAsset(AssetBank& bank, int id)
        : Asset(bank, id, AssetType::sound_clip)
    {

    }

    void SoundClipAsset::load(const std::string& file_name)
    {
        Asset::load(file_name);

        LuaValue sound_file_name;
        if (!m_table.get_value(LuaType::string, "file_name", sound_file_name))
            throw Exception("Bad bitmap asset file \"" + file_name + "\".");

        m_sound_clip.load(get_asset_type_dir(AssetType::sound_clip) + sound_file_name.get_string());
    }
}