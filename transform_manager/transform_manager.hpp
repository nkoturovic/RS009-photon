#ifndef TRANSFORM_MANAGER_H
#define TRANSFORM_MANAGER_H

#include <vector>
#include <stack>
#include <future>

#include <algorithm>
#include <numeric>

template <typename X>
class Transform {
public:

    X& operator()(X &x) {
        return this->apply(x);
    }

    friend X& operator<<=(X &x, const Transform& tform) { 
        return tform.apply(x); 
    }

    friend X operator<<(const X &x, const Transform& tform) { 
        X copy(x);
        return tform.apply(copy);
    }

private:
    virtual X& apply(X &) const = 0;
};


template <typename X>
class Composition : public Transform<X> {
public:
    friend Composition operator*(const Transform<X> &tr1, const Transform<X> &tr2) 
    { return Composition(tr1, tr2); }

private:
    std::function<X&(X&)> m_composition;

    Composition(const Transform<X> &tform1, const Transform<X> &tform2)
        : m_composition( [tform1, &tform2](X &x) -> X& { return tform1(tform2(x)); } ) {}

    virtual X& apply(X &x) const override { return m_composition(x); }
};


template <class X>
class TransformManager {
private:
    X m_origin;
    X m_current;

    std::optional<std::future<Transform<X>>> m_previous {};
    std::optional<std::future<Transform<X>>> m_next {};

    // Transformations that transform origin to current
    std::vector<Transform<X>> m_previousTransforms;

    // Transformations that were previously done 
    // than undone - in reverse order (be cautious)
    std::vector<Transform<X>> m_nextTransforms;


public:
    TransformManager(X &&x) : m_origin(x), m_current(std::move(x)) {}

    const X& origin() const { return m_origin; }
    const X& current() const { return m_current; }

    std::pair <bool, bool> redo() {

        if (m_nextTransforms.empty())
            return { false, false };

        m_previous = std::move(m_current);
        m_current = std::move(m_next);

        m_previousTransforms.push_back(std::move(m_nextTransforms.back()));
        m_nextTransforms.pop_back();

        bool hasNext = not m_nextTransforms.empty();

        if (hasNext)
            m_next = std::async(std::launch::async, [&] { return m_nextTransforms.back(m_current); });
        else
            m_next = {};

        return { true, hasNext };
    }

    std::pair<bool, bool> undo() {

        if (m_previousTransforms.empty())
            return { false, false };

        m_next = std::move(m_current);
        m_current = std::move(m_previous);
        m_nextTransforms.push(std::move(m_previousTransforms.back()));
        m_previousTransforms.pop_back();

        /* Make composition from previous transformations */
        auto comp = std::accumulate(std::next(m_previousTransforms.crbegin()), 
                                              m_previousTransforms.crend(), 
                                              m_previousTransforms.crbegin(), 
                                              std::multiplies<>()
        );

        bool hasPrev = not m_previousTransforms.empty();

        if (hasPrev)
            m_previous = std::async(std::launch::async, [&] { return comp(m_origin); });
        else
            m_previous = {};

        return { true, hasPrev };
    }

    void transform(Transform<X> && tform) {
        m_previous = m_current;
        tform(m_current);
        m_previousTransforms.push_back(std::move(tform));
        m_nextTransforms.clear();
    }
};

#endif // TRANSFORM_MANAGER_H
