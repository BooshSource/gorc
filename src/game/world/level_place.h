#pragma once

#include "content/assets/level.h"
#include "framework/content/manager.h"
#include <memory>

namespace gorc {
namespace game {
namespace world {

class level_place {
public:
	std::shared_ptr<content::manager> contentmanager;
	const content::assets::level& level;

	level_place(std::shared_ptr<content::manager> contentmanager, const content::assets::level& level);
};

}
}
}