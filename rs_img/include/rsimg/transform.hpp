#ifndef RS_TRANSFORM_H
#define RS_TRANSFORM_H

#include "image.hpp"
#include <functional>
#include <vector>

#include "3rd_party/visitor_pattern.hpp"

namespace rs {

/* Deklaracije klasa */
class Transform; class Composition; class Rotate; class Flip; 
class BlackNWhite; class Brightness; class Contrast; class Crop;
class Invert; class Overlay; class Blur; class Cartoon; class Neon;
class Winter; class Sepia; class Silver; class Rainbow; class Summer;

#define TypeHierarchy Transform, Composition, Rotate, Flip, \
                      BlackNWhite, Brightness, Contrast, Crop, \
                      Invert, Overlay, Blur, Cartoon, Neon, \
                      Winter, Sepia, Silver, Rainbow, Summer

#define ConstTypeHierarchy const Transform, const Composition,\
                           const Rotate, const Flip,\
                           const BlackNWhite, const Brightness,\
                           const Contrast, const Crop, const Invert,\
                           const Overlay, const Blur, const Cartoon,\
                           const Neon, const Winter, const Sepia,\
                           const Silver, const Rainbow, const Summer

/* 1) Vizitor bez rezultata (Ref verzija) */
using TransformVisitor = impl::Visitor<TypeHierarchy>;

/* 2) Vizitor bez rezultata (ConstRef verzija) */
using ConstTransformVisitor = impl::Visitor<ConstTypeHierarchy>;

/* 3) Vizitor sa rezultatom(retval) (Ref verzija) */
template <class ResultType>
using TransformVisitorWithResult = impl::VisitorWithResult<TransformVisitor, ResultType>;

/* 4) Vizitor sa rezultatom(retval) (ConstRef verzija) */
template <class ResultType>
using ConstTransformVisitorWithResult = impl::VisitorWithResult<ConstTransformVisitor, ResultType>;

class Transform : public impl::Visitable<TypeHierarchy> {
public:
    Image& operator()(Image &img) const {
        return this->applyImpl(img);
    }

    friend Image& operator<<=(Image &img, const Transform& tform) {
        return tform.applyImpl(img);
    }

    friend Image operator<<(const Image &img, const Transform& tform) {
        Image copy(img);
        return tform.applyImpl(copy);
    }

    virtual std::unique_ptr<Transform> clone() const {
        return std::unique_ptr<Transform>(this->cloneImpl());
    }

    virtual ~Transform() = default;
protected:
    using base_type = Transform;

private:
    virtual Transform* cloneImpl() const = 0;
    virtual Image& applyImpl(Image &) const = 0;
};

class Composition : public impl::InheritVisitable<Composition,Transform,TypeHierarchy> {
public:
    Composition(const Transform &tform1, const Transform &tform2)
        : m_tform1(tform1.clone()), m_tform2(tform2.clone()) {}

    friend Composition operator*(const Transform &tr1, const Transform &tr2)
        { return Composition(tr1, tr2); }

    friend Composition operator|(const Transform &tr1, const Transform &tr2)
        { return Composition(tr2, tr1); }

    const Transform& firstTransform() const { return *m_tform1; }
    const Transform& secondTransform() const { return *m_tform2; }

private:
    std::unique_ptr<Transform> m_tform1, m_tform2;

    Transform* cloneImpl() const override {
        return new Composition(*m_tform1, *m_tform2);
    }

    virtual Image& applyImpl(Image &x) const override { return (*m_tform1)((*m_tform2)(x)); }
};

class Rotate : public impl::InheritVisitable<Rotate,Transform,TypeHierarchy> {
public:
    enum class Direction { LEFT, RIGHT };
    Rotate(Direction);
    Direction direction() const { return m_direction; }
private:
     Direction m_direction;

     virtual Transform* cloneImpl() const override {
        return new Rotate(*this);
    }

    virtual Image& applyImpl(Image &) const override;
};

class Flip : public impl::InheritVisitable<Flip,Transform,TypeHierarchy> {
public:
    enum class Axis { X=0, Y=1 };
    Flip(Axis);
    Axis axis() const { return m_axis; }
private:

    virtual Transform* cloneImpl() const override {
        return new Flip(*this);
    }
    Axis m_axis;
    virtual Image& applyImpl(Image &) const override;
};

class BlackNWhite : public impl::InheritVisitable<BlackNWhite,Transform,TypeHierarchy> {
public:
    BlackNWhite();
private:

    virtual Transform* cloneImpl() const override {
        return new BlackNWhite(*this);
    }
    virtual Image& applyImpl(Image &) const override;
};

class Brightness : public impl::InheritVisitable<Brightness,Transform,TypeHierarchy> {
public:
    Brightness(double percents);
    double percents() const { return m_percents; }
private:

    virtual Transform* cloneImpl() const override {
        return new Brightness(*this);
    }

    double m_percents = 0;
    virtual Image& applyImpl(Image &) const override;
};

class Contrast : public impl::InheritVisitable<Contrast,Transform,TypeHierarchy> {
public:
    Contrast(double percents);
    double percents() const { return m_percents; }
private:

    virtual Transform* cloneImpl() const override {
        return new Contrast(*this);
    }

    double m_percents = 0;
    virtual Image& applyImpl(Image &) const override;
};

class Crop : public impl::InheritVisitable<Crop,Transform,TypeHierarchy> {
public:
    Crop(int x, int y, int width, int height);
    double x() const { return m_x; }
    double y() const { return m_y; }
    double width() const { return m_width; }
    double height() const { return m_height; }
private:

    virtual Transform* cloneImpl() const override {
        return new Crop(*this);
    }

    int m_x, m_y, m_width, m_height;
    virtual Image& applyImpl(Image &) const override;
};

class Invert : public impl::InheritVisitable<Invert,Transform,TypeHierarchy> {
public:
    Invert();
private:

    virtual Transform* cloneImpl() const override {
        return new Invert(*this);
    }
    virtual Image& applyImpl(Image &) const override;
};

class Overlay : public impl::InheritVisitable<Overlay,Transform,TypeHierarchy> {
public:
    enum class Color { RED,GREEN,BLUE };

    Overlay(Color color);
    Color color() const;
private:

    Color m_color;

    virtual Transform* cloneImpl() const override {
        return new Overlay(*this);
    }
    virtual Image& applyImpl(Image &) const override;
};

class Blur : public impl::InheritVisitable<Blur,Transform,TypeHierarchy> {
public:
    Blur(int percent);
    int percent() const;
private:
    int m_percent = 0;

    virtual Transform* cloneImpl() const override {
        return new Blur(*this);
    }
    virtual Image& applyImpl(Image &) const override;
};

class Cartoon : public impl::InheritVisitable<Cartoon,Transform,TypeHierarchy> {
private:
    virtual Transform* cloneImpl() const override {
        return new Cartoon(*this);
    }
    virtual Image& applyImpl(Image &) const override;
};

class Neon : public impl::InheritVisitable<Neon,Transform,TypeHierarchy> {
private:
    virtual Transform* cloneImpl() const override {
        return new Neon(*this);
    }
    virtual Image& applyImpl(Image &) const override;
};

class Winter : public impl::InheritVisitable<Winter,Transform,TypeHierarchy> {
private:
    virtual Transform* cloneImpl() const override {
        return new Winter(*this);
    }
    virtual Image& applyImpl(Image &) const override;
};

class Sepia : public impl::InheritVisitable<Sepia,Transform,TypeHierarchy> {
private:
    virtual Transform* cloneImpl() const override {
        return new Sepia(*this);
    }
    virtual Image& applyImpl(Image &) const override;
};

class Silver : public impl::InheritVisitable<Silver,Transform,TypeHierarchy> {
private:
    virtual Transform* cloneImpl() const override {
        return new Silver(*this);
    }
    virtual Image& applyImpl(Image &) const override;
};

class Rainbow : public impl::InheritVisitable<Rainbow,Transform,TypeHierarchy> {
private:
    virtual Transform* cloneImpl() const override {
        return new Rainbow(*this);
    }
    virtual Image& applyImpl(Image &) const override;
};

class Summer : public impl::InheritVisitable<Summer,Transform,TypeHierarchy> {
private:
    virtual Transform* cloneImpl() const override {
        return new Summer(*this);
    }
    virtual Image& applyImpl(Image &) const override;
};

Image& operator<<=(Image &img, const Transform& tr);
Image operator<<(const Image &img, const Transform& tr);
Composition operator*(const Transform &tr1, const Transform &tr2);
Composition operator|(const Transform &tr1, const Transform &tr2);

} // namespace rs

#undef TypeHierarchy
#undef ConstTypeHierarchy

#endif
