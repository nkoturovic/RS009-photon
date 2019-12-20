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

    friend X& operator<<=(X &x, const Transform& tr) { 
        return tr.apply(x); 
    }

    friend X operator<<(const X &x, const Transform& tr) { 
        X copy(x);
        return copy <<= tr;
    }

    X& operator()(X &x) {
        this->apply(x);
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
    Composition(const Transform<X> &tr1, const Transform<X> &tr2)
        :m_composition( [&tr1, &tr2](X &x) -> X& { return (x <<= tr2) <<= tr1; } ) {}

    virtual X& apply(X &x) const override { return m_composition(x); }
    std::function<X&(X&)> m_composition;
};


template <class X>
class TransformManager {
private:
    X m_origin;
    X m_current;

    std::optional<std::future<Transform<X>>> m_previous {};
    std::optional<std::future<Transform<X>>> m_next {};

    // Transformations that transform origin to current
    std::deque<Transform<X>> m_previousTransforms;

    // Transformations that were previously done than undone
    std::deque<Transform<X>> m_nextTransforms;


public:
    TransformManager(X &&x) : m_origin(x), m_current(std::move(x)) {}

    const X& origin() const { return m_origin; }
    const X& current() const { return m_current; }

    std::pair <bool, bool> redo() {

        if (m_nextTransforms.empty())
            return { false, false };

        m_previous = std::move(m_current);
        m_current = std::move(m_next);

        m_previousTransforms.push_back(std::move(m_nextTransforms.front()));
        m_previousTransforms.pop_front();

        bool hasNext = not m_nextTransforms.empty();

        if (hasNext)
            m_next = std::async(std::launch::async, [&] { return m_previousTransforms.front()(m_current); });
        else
            m_next = {};

        return { true, hasNext };
    }

    std::pair<bool, bool> undo() {

        if (m_previousTransforms.empty())
            return { false, false };

        m_next = std::move(m_current);
        m_current = std::move(m_previous);
        m_nextTransforms.push_front(std::move(m_previousTransforms.back()));
        m_previousTransforms.pop_back();

        /* Make composition from previous transformations */
        auto tform = std::accumulate(std::next(m_previousTransforms.crbegin()), 
                                     m_previousTransforms.crend(), 
                                     m_previousTransforms.crbegin(), 
                                     std::multiplies<>()
        );

        bool hasPrev = not m_previousTransforms.empty();

        if (hasPrev)
            m_previous = std::async(std::launch::async, [&] { return tform(m_origin); });
        else
            m_previous = {};

        return { true, hasPrev };
    }

    void transform(Transform<X> && tform) {
        m_previous = m_current;
        tform(m_current);
        m_previousTransforms.push_back(std::move(tform));
    }
};

#endif // TRANSFORM_MANAGER_H
