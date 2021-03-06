#include "loader_registry.hpp"
#include "log/log.hpp"

gorc::loader const& gorc::loader_registry::get_loader(fourcc f) const
{
    auto it = loaders.find(f);
    if(it == loaders.end()) {
        LOG_FATAL(format("no loader for content type %s") % to_string(f));
    }

    return *it->second;
}
