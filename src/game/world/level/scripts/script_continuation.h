#pragma once

#include "cog/vm/value.h"
#include "game/flags/message_type.h"
#include "script_instance.h"
#include <array>

namespace gorc {
namespace game {
namespace world {
namespace level {
namespace scripts {

class script_continuation {
public:
	int instance_id;

	int sender_id;
	int sender_ref;
	flags::message_type sender_type;
	int source_ref;
	flags::message_type source_type;
	std::array<cog::vm::value, 4> params;
	cog::vm::value returnex_value;

	unsigned int program_counter;

	script_continuation() = default;
	script_continuation(int InstanceId,
			int SenderId, int SenderRef, flags::message_type SenderType,
			int SourceRef, flags::message_type SourceType,
			cog::vm::value Param0, cog::vm::value Param1, cog::vm::value Param2, cog::vm::value Param3,
			unsigned int ProgramCounter = 0);
};

}
}
}
}
}
