#ifndef RS_TRANSFORM_H
#define RS_TRANSFORM_H

#include "image.hpp"
#include <functional>
#include <vector>

namespace rs {

class Transform {
public:
    friend Image& operator<<=(Image &img, const Transform& tr) { 
        return tr.applyToImpl(img); 
    }

    friend Image operator<<(const Image &img, const Transform& tr) { 
        Image copy(img);
        return copy <<= tr;
    }

private:
    virtual Image& applyToImpl(Image &) const = 0;
};

class Composition : public Transform {
public:
    friend Composition operator*(const Transform& tr1, const Transform& tr2) 
    { return Composition(tr1, tr2); }

private:
    Composition(const Transform& tr1, const Transform& tr2);

    virtual Image& applyToImpl(Image &) const override;
    std::function<Image&(Image&)> m_composition;
};

class Rotate : public Transform {
public:
    enum class Direction { LEFT, RIGHT };
    Rotate(Direction);
private:
    Direction m_direction;
    virtual Image& applyToImpl(Image &) const override;
};

class Flip : public Transform {
public:
    enum class Axis { X=0, Y=1 };
    Flip(Axis);
private:
    Axis m_axis;
    virtual Image& applyToImpl(Image &) const override;
};

class BlackNWhite : public Transform {
public:
    BlackNWhite();
private:
    virtual Image& applyToImpl(Image &) const override;
};

class Brightness : public Transform {
public:
    Brightness(double percents);

private:
    double m_percents = 0;
    virtual Image& applyToImpl(Image &) const override;
};

class Contrast : public Transform {
public:
    Contrast(double percents);

private:
    double m_percents = 0;
    virtual Image& applyToImpl(Image &) const override;
};

class Crop : public Transform{
    public:
        Crop(int x, int y, int width, int height);
    private:
        int m_x;
        int m_y;
        int m_width;
        int m_height;
        virtual Image& applyToImpl(Image &) const override;
};

Image& operator<<=(Image &img, const Transform& tr);
Image operator<<(const Image &img, const Transform& tr);
Composition operator*(const Transform& tr1, const Transform& tr2);

} // namespace rs

#endif
