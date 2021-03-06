#pragma once

#include "content/id.hpp"

namespace gorc {
namespace game {
namespace world {
namespace events {

class killed {
public:
    #include "killed.uid"

    thing_id thing;
    thing_id killer;

    killed(thing_id thing, thing_id killer);
};

}
}
}
}
