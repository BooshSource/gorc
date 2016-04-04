#pragma once

#include "libold/base/utility/entity_id.hpp"

namespace gorc {
namespace game {
namespace world {
namespace sounds {
namespace components {

class foley {
public:
    #include "foley.uid"

    int sound;

    foley(int sound);
};

}
}
}
}
}
