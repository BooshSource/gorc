#pragma once

#include "animation.h"
#include "framework/pool.h"
#include "content/flags/anim_flag.h"
#include "framework/flag_set.h"

namespace gorc {
namespace game {
namespace world {
namespace level {

class level_model;

namespace animations {

class surface_material_animation : public animation {
private:
	level_model& model;
	unsigned int surface;
	double framerate;
	flag_set<flags::AnimFlag> flag;
	double framerate_accumulator = 0.0;
	int num_cels;

public:
	surface_material_animation(level_model& model, unsigned int surface, double framerate, flag_set<flags::AnimFlag> flag, int anim_num);

	void update(double dt);
	void stop();
};

}
}
}
}
}
