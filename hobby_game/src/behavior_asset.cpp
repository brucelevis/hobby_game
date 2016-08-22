#include "behavior_asset.h"

namespace hg
{
    BehaviorAsset::BehaviorAsset(AssetBank& bank, int id)
        : Asset(bank, id)
    {

    }

    void BehaviorAsset::load(const std::string& file_name)
    {
        Asset::load(file_name);
    }
}