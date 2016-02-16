#pragma once

#include "vector.hpp"

namespace gorc {

    struct color_vector_tag { };

    using color = abstract_vector<4, float, color_vector_tag>;
    using color_rgb = abstract_vector<3, float, color_vector_tag>;
    using color_rgba8 = abstract_vector<4, uint8_t, color_vector_tag>;
    using color_rgb8 = abstract_vector<3, uint8_t, color_vector_tag>;

    constexpr color make_color(float r, float g, float b, float a)
    {
        return color(r, g, b, a);
    }

    constexpr color_rgb make_color(float r, float g, float b)
    {
        return color_rgb(r, g, b);
    }

    constexpr color_rgba8 make_color_rgba8(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
    {
        return color_rgba8(r, g, b, a);
    }

    constexpr color_rgb8 make_color_rgb8(uint8_t r, uint8_t g, uint8_t b)
    {
        return color_rgb8(r, g, b);
    }

}
