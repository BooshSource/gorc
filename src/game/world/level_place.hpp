#pragma once

#include "libold/content/assets/level.hpp"
#include "content/content_manager.hpp"
#include <memory>

namespace gorc {
namespace game {
namespace world {

class level_place {
public:
    std::shared_ptr<content_manager> contentmanager;
    asset_ref<content::assets::level> level;

    level_place(std::shared_ptr<content_manager> contentmanager,
                asset_ref<content::assets::level> level);
};

}
}
}
