#pragma once

#include "libold/base/utility/entity_id.hpp"

namespace gorc {
namespace game {
namespace world {
namespace events {

class landed {
public:
    #include "landed.uid"

    int thing;

    landed(int thing);
};

}
}
}
}
