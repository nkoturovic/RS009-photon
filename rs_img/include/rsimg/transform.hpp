#ifndef RS_TRANSFORM_H
#define RS_TRANSFORM_H

#include "image.hpp"
#include <functional>
#include <vector>

#define RS_TRANSFORMS(PREF,SUFF) \
PREF Composition SUFF \
PREF Rotate      SUFF \
PREF Flip        SUFF \
PREF BlackNWhite SUFF \
PREF Brightness  SUFF \
PREF Contrast    SUFF \
PREF Crop        SUFF

#define RS_VISIT_PREFIX virtual void visit(const
#define RS_VISIT_PURE_SUFFIX &)=0;
#define RS_VISIT_SUFFIX &)override;
#define RS_PURE_DECLARE_VISITORS RS_TRANSFORMS(RS_VISIT_PREFIX, RS_VISIT_PURE_SUFFIX)
#define RS_DECLARE_VISITORS RS_TRANSFORMS(RS_VISIT_PREFIX, RS_VISIT_SUFFIX) \

namespace rs {

class Transform;

RS_TRANSFORMS(class,;)

namespace interface {
class TransformVisitorI {
private:
    friend class rs::Transform;
    RS_TRANSFORMS(friend class rs::,;)
    RS_PURE_DECLARE_VISITORS
};
} // ns interface

class Transform {
friend class interface::TransformVisitorI;
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

    virtual void accept(interface::TransformVisitorI &visitor) const { this->acceptImpl(visitor); }

    virtual std::unique_ptr<Transform> clone() const { 
        return std::unique_ptr<Transform>(this->cloneImpl()); 
    }

    virtual ~Transform() = default;
protected:
    using base_type = Transform;

private:
    virtual void acceptImpl(interface::TransformVisitorI &visitor) const = 0;
    virtual Transform* cloneImpl() const = 0;
    virtual Image& applyImpl(Image &) const = 0;
};

template <class R>
class TransformVisitor : public interface::TransformVisitorI {
private:
    R m_result;
protected:
    void result(R &&r) { m_result = R(std::forward<R>(r)); }
public:
    R operator()(const rs::Transform &t) { m_result = {}; t.accept(*this); return m_result; }
    R result() const { return m_result; }
};

template <typename ... Base>
struct Visitor : Base ...
{
    using Base::operator()...;
};

template<typename ... T>  Visitor(T...) -> Visitor<T...>;

template <typename ... Base>
constexpr auto makeVisitor(Base... args) 
{
    struct LambdaVisitor : public TransformVisitor 
                       <typename std::result_of<Visitor<Base...>(Transform&)>::type>
    {
        Visitor<Base...> m_v;
        LambdaVisitor(Base... args) : m_v{args...} {}
        #define VISITOR_IMPL_PFIX virtual void visit(const
        #define VISITOR_IMPL_SFX &t) override { this->result(m_v(t)); }
        RS_TRANSFORMS(VISITOR_IMPL_PFIX, VISITOR_IMPL_SFX)
        #undef VISITOR_IMPL_PFIX
        #undef VISITOR_IMPL_SFX
    }r(args...);
    return r;
}

class Composition : public Transform {
public:
    Composition(const Transform &tform1, const Transform &tform2)
        : m_tform1(tform1.clone()), m_tform2(tform2.clone()) {}

    friend Composition operator*(const Transform &tr1, const Transform &tr2) 
        { return Composition(tr1, tr2); }

    const Transform& firstTransform() const { return *m_tform1; }
    const Transform& secondTransform() const { return *m_tform2; }

private:
    std::unique_ptr<Transform> m_tform1, m_tform2;

    virtual void acceptImpl(rs::interface::TransformVisitorI &visitor) const override { 
        visitor.visit(*this); 
    }

    Transform* cloneImpl() const override {
        return new Composition(*m_tform1, *m_tform2);  
    }

    virtual Image& applyImpl(Image &x) const override { return (*m_tform1)((*m_tform2)(x)); }
};

class Rotate : public Transform {
public:
    enum class Direction { LEFT, RIGHT };
    Rotate(Direction);
    Direction direction() const { return m_direction; }
private:
     Direction m_direction;

    virtual void acceptImpl(rs::interface::TransformVisitorI &visitor) const override { 
        visitor.visit(*this); 
    }

     virtual Transform* cloneImpl() const override {
        return new Rotate(*this); 
    }

    virtual Image& applyImpl(Image &) const override;
};

class Flip : public Transform {
public:
    enum class Axis { X=0, Y=1 };
    Flip(Axis);
    Axis axis() const { return m_axis; }
private:
    virtual void acceptImpl(rs::interface::TransformVisitorI &visitor) const override { 
        visitor.visit(*this); 
    }

    virtual Transform* cloneImpl() const override {
        return new Flip(*this); 
    }
    Axis m_axis;
    virtual Image& applyImpl(Image &) const override;
};

class BlackNWhite : public Transform {
public:
    BlackNWhite();
private:
    virtual void acceptImpl(rs::interface::TransformVisitorI &visitor) const override { 
        visitor.visit(*this); 
    }

    virtual Transform* cloneImpl() const override {
        return new BlackNWhite(*this); 
    }
    virtual Image& applyImpl(Image &) const override;
};

class Brightness : public Transform {
public:
    Brightness(double percents);
    double percents() const { return m_percents; }
private:
    virtual void acceptImpl(rs::interface::TransformVisitorI &visitor) const override { 
        visitor.visit(*this); 
    }

    virtual Transform* cloneImpl() const override {
        return new Brightness(*this); 
    }
 
    double m_percents = 0;
    virtual Image& applyImpl(Image &) const override;
};

class Contrast : public Transform {
public:
    Contrast(double percents);
    double percents() const { return m_percents; }
private:
    virtual void acceptImpl(rs::interface::TransformVisitorI &visitor) const override { 
        visitor.visit(*this); 
    }

    virtual Transform* cloneImpl() const override {
        return new Contrast(*this); 
    }

    double m_percents = 0;
    virtual Image& applyImpl(Image &) const override;
};

class Crop : public Transform{
public:
    Crop(int x, int y, int width, int height);
    double x() const { return m_x; }
    double y() const { return m_y; }
    double width() const { return m_width; }
    double height() const { return m_height; }
private:
    virtual void acceptImpl(rs::interface::TransformVisitorI &visitor) const override { 
        visitor.visit(*this); 
    }

    virtual Transform* cloneImpl() const override {
        return new Crop(*this); 
    }

    int m_x, m_y, m_width, m_height;
    virtual Image& applyImpl(Image &) const override;
};

Image& operator<<=(Image &img, const Transform& tr);
Image operator<<(const Image &img, const Transform& tr);
Composition operator*(const Transform &tr1, const Transform &tr2);

} // namespace rs

#undef RS_ACCEPT_TRANSFORM_VISITOR

#endif
