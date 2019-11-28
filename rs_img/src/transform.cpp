#include "../include/rsimg/transform.hpp"
#include "../include/rsimg/implementation/image_impl.hpp"

namespace rs {

Rotate::Rotate(Rotate::Direction direction) : m_direction(direction) {}

Image& Rotate::applyToImpl(Image &img) const {
    cv::Mat &image = get_impl(img).m_image;
    /* TODO: @Andrijana (Napisati implementaciju) */
    return img;
}

Flip::Flip(Axis axis) : m_axis(axis) {}

Image& Flip::applyToImpl(Image &img) const {
    cv::Mat &image = get_impl(img).m_image;
    /* TODO: @Andrijana (Napisati implementaciju) */
    return img;
}

Composition::Composition(const Transform& tr1, const Transform& tr2) : 
    m_composition( [&tr1, &tr2](Image &img) -> Image& { return (img <<= tr2) <<= tr1; } ) {}

Image& Composition::applyToImpl(Image &img) const {
    return m_composition(img);
}

BlackNWhite::BlackNWhite() { }

Image& BlackNWhite::applyToImpl(Image &img) const { 
    cv::Mat &image = get_impl(img).m_image;
    /* TODO: @Andrijana (Napisati implementaciju) */
    return img;
}

} // namespace rs
