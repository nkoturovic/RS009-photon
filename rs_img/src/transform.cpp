#include "../include/rsimg/transform.hpp"
#include "../include/rsimg/implementation/image_impl.hpp"
#include "../include/rsimg/exception.hpp"

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

Brightness::Brightness(double percents) : m_percents(percents) {}

Image& Brightness::applyToImpl(Image &img) const {
    cv::Mat &image = get_impl(img).m_image;

    /* TODO: @Andrijana (Napisati implementaciju) 
     *
     * Nivo potrebne promene osvetljenosti je izrazen u procentima i 
     * nalazi se u polju: m_percents. Da bi se pronasla vrednost za koju
     * sliku treba posvetliti, mora se uzeti u obzir trenutna osvetljenost slike
     * jer se osvetljenost piksela izrazava u opsegu 0-255 za svaku od kompon-
     * enti piksela (RGB). Primeniti nesto nalik na sledecu formulu:
     * NEW_R = OLD_R + ((OLD_R * percent)/100);
     * NEW_G = OLD_G + ((OLD_G * percent)/100);
     * NEW_B = OLD_B + ((OLD_B * percent)/100); 
     *
     * Ovo ce raditi i za procente koji su oblika -100, -150, 200 ... Mada moze 
     * se vrlo lako i ograniciti. 
     *
     * Funkcija opencv transform bi trebalo da prima nesto nalik:
     * ((OLD_R * percent)/100) ako se ne varam */
     return img;
}

Contrast::Contrast(double percents) : m_percents(percents) {
}

Image& Contrast::applyToImpl(Image &img) const {
    cv::Mat &image = get_impl(img).m_image;

    /* TODO: @Andrijana (Napisati implementaciju) 
     *
     * Vazi isto sto i za Brightness, samo ovde umesto uvecanje za odredjeni procenat
     * vrednoste (R,G,B) komponenti treba mnoziti sa odgovarajucim koeficijentom:
     *
     * Npr: NEW_R = OLD_R * (100 + percent)/100) 
     * Npr: NEW_G = OLD_G * (100 + percent)/100) 
     * Npr: NEW_B = OLD_B * (100 + percent)/100) 
     *
     * Funkcija opencv transform bi trebalo da prima nesto nalik:
     * (100 + percent)/100) */

    return img;
}

} // namespace rs
