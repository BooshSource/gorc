#pragma once

#include <array>
#include <vector>
#include <cstdint>
#include <memory>

#include "content/asset.hpp"
#include "math/color.hpp"
#include "io/binary_input_stream.hpp"
#include "text/json_output_stream.hpp"

namespace gorc {

    class colormap_palette {
    public:
        std::array<color_rgb8, 256> data;

        colormap_palette(deserialization_constructor_tag, binary_input_stream &);

        void json_serialize_object(json_output_stream &) const;
    };

    class colormap_light_level {
    public:
        std::array<uint8_t, 256> data;

        colormap_light_level(deserialization_constructor_tag, binary_input_stream &);

        void json_serialize_object(json_output_stream &) const;
    };

    class colormap_transparency_table {
    public:
        std::array<uint8_t, 256> data;

        colormap_transparency_table(deserialization_constructor_tag, binary_input_stream &);

        void json_serialize_object(json_output_stream &) const;
    };

    class colormap : public asset {
    public:
        static fourcc const type;

        std::array<char, 4> magic;
        uint32_t version;
        uint32_t transparency;

        color_rgb tint;

        std::array<uint32_t, 10> unknown;

        std::unique_ptr<colormap_palette> palette;
        std::vector<colormap_light_level> light_levels;
        std::vector<colormap_transparency_table> transparency_tables;

        colormap(deserialization_constructor_tag, binary_input_stream &);

        void json_serialize_object(json_output_stream &) const;
    };

}
