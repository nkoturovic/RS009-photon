#ifndef RS_TRANSFORM_H
#define RS_TRANSFORM_H

#include "image.hpp"
#include <functional>
#include <vector>

namespace rs {

class Transform {
public:
    Image& operator()(Image &img) const {
        return this->apply(img);
    }

    friend Image& operator<<=(Image &img, const Transform& tform) { 
        return tform.apply(img); 
    }

    friend Image operator<<(const Image &img, const Transform& tform) { 
        Image copy(img);
        return tform.apply(copy);
    }

private:
    virtual Image& apply(Image &) const = 0;
};


class Composition : public Transform {
public:
    friend Composition operator*(Transform && tr1, Transform &&tr2) 
        { return Composition(std::move(tr1), std::move(tr2)); }

private:
    const Transform &m_tform1;
    const Transform &m_tform2;
    std::function<Image&(Image&)> func;

    Composition(Transform &&tform1, Transform &&tform2)
        : m_tform1(std::move(tform1)), m_tform2(std::move(tform2)) {}

    virtual Image& apply(Image &x) const override { return m_tform1(m_tform2(x)); }
};

class Rotate : public Transform {
public:
    enum class Direction { LEFT, RIGHT };
    Rotate(Direction);
private:
    Direction m_direction;
    virtual Image& apply(Image &) const override;
};

class Flip : public Transform {
public:
    enum class Axis { X=0, Y=1 };
    Flip(Axis);
private:
    Axis m_axis;
    virtual Image& apply(Image &) const override;
};

class BlackNWhite : public Transform {
public:
    BlackNWhite();
private:
    virtual Image& apply(Image &) const override;
};

class Brightness : public Transform {
public:
    Brightness(double percents);

private:
    double m_percents = 0;
    virtual Image& apply(Image &) const override;
};

class Contrast : public Transform {
public:
    Contrast(double percents);

private:
    double m_percents = 0;
    virtual Image& apply(Image &) const override;
};

class Crop : public Transform{
    public:
        Crop(int x, int y, int width, int height);
    private:
        int m_x;
        int m_y;
        int m_width;
        int m_height;
        virtual Image& apply(Image &) const override;
};

Image& operator<<=(Image &img, const Transform& tr);
Image operator<<(const Image &img, const Transform& tr);
Composition operator*(Transform &&tr1, Transform &&tr2);

} // namespace rs

#endif
