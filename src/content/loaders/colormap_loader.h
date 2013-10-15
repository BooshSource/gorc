#pragma once

#include "content/loader.h"

namespace gorc {
namespace content {
namespace loaders {

class colormap_loader : public loader {
public:
	static const std::vector<boost::filesystem::path> asset_root_path;

	virtual std::unique_ptr<asset> deserialize(io::read_only_file& file, manager& manager, diagnostics::report& report) override;
};

}
}
}
