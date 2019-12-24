#ifndef UNDO_H
#define UNDO_H

#include <future>
#include <numeric>
#include <variant>
#include <iostream>
#include <vector>

namespace rs {

template <class X, class Action = std::function<void(X&)>>
class Undo {
public:
    Undo(X &&x) : m_origin(x), m_current(std::move(x)), m_originEqCurrent(true) {}

    const X& origin() const { return m_origin; }
    const X& current() const { return m_current; }

    std::vector<std::shared_ptr<const Action>> previousActions() const {
        return std::vector<std::shared_ptr<const Action>>(
                m_previousActions.cbegin(), 
                m_previousActions.cend()
        );
    }

    std::vector<std::shared_ptr<const Action>> nextActions() const {
        return std::vector<std::shared_ptr<const Action>>(
                m_nextActions.cbegin(), 
                m_nextActions.cend()
        );
    }

    template <class T = Action>
    void action(T && action);

    // retval = [ currSucc, willNextSucceed ]
    std::pair <bool, bool> undo();
    std::pair <bool, bool> redo();

private:
    X m_origin;
    X m_current;
    bool m_originEqCurrent;

    std::variant<X, std::future<X>> m_previous;
    std::variant<X, std::future<X>> m_next;

    /* Actions that transform origin to current */
    std::vector<std::shared_ptr<Action>> m_previousActions;

    /* Transformations that were previously done 
     than undone - in reverse order (be cautious) */
    std::vector<std::shared_ptr<Action>> m_nextActions;
};

template <class X, class Action>
template <class T>
void Undo<X,Action>::action(T && action) {
    m_originEqCurrent = false;
    m_previous = m_current;
    action(m_current);

    if constexpr (std::is_base_of<Action, T>::value) {
        m_previousActions.push_back(std::make_shared<T>(std::forward<T>(action)));
    } else {
        m_previousActions.push_back(std::make_shared<Action>(std::forward<T>(action)));
    }

    m_next = {};
    m_nextActions = {};
}


template <class X, class Action>
std::pair<bool, bool> Undo<X, Action>::undo() {

    if (m_originEqCurrent)
        return {false, false};

    /* Postoji bar jedna undo akcija */
    if (m_nextActions.empty()) {
        m_nextActions.push_back(m_previousActions.back());
        m_previousActions.pop_back();
    }

    if (m_previousActions.empty()) {
        m_originEqCurrent = true;
        m_next = m_current;
        m_current = m_origin;
        m_previous = {};
        return {true,false};
    } else { // there is at least one el in previous
        m_next = m_current;

        try {
            m_current = std::move(std::get<X>(m_previous));
        } catch (const std::bad_variant_access&) {
            m_current = std::move(std::get<std::future<X>>(m_previous).get());
        } catch (std::exception &e) {
            std::cerr << e.what();
            exit(EXIT_FAILURE);
        }

        m_nextActions.push_back(m_previousActions.back());
        m_previousActions.pop_back();

        bool hasPrev = not m_previousActions.empty() || not m_originEqCurrent;
        if (hasPrev) {
            m_previous = std::async(std::launch::async, 
                                [ origin  = m_origin,
                                  actions = this->previousActions() ] () mutable { 
                                    for (const auto &a : actions) { (*a)(origin); } 
                                    return origin;
                                });
        } else {
           m_previous = {};
        }

        return { true, hasPrev };
    }
}

template <class X, class Action>
std::pair<bool, bool> Undo<X, Action>::redo() {
    if (m_nextActions.empty())
        return { false, false };

    m_previous = std::move(m_current);
    m_originEqCurrent = false;

    try {
        m_current = std::move(std::get<X>(m_next));
    } catch (const std::bad_variant_access&) {
        m_current = std::move(std::get<std::future<X>>(m_next).get());
    } catch (std::exception &e) {
        std::cerr << e.what();
        exit(EXIT_FAILURE);
    }

    m_previousActions.push_back(m_nextActions.back());
    m_nextActions.pop_back();

    bool hasNext = not m_nextActions.empty();

    if (hasNext) {
        m_next = std::async(std::launch::async, 
                            [action = m_nextActions.back(), curr=m_current] () mutable { 
                                (*action)(curr); 
                                return curr;
                            });
    } else {
        m_next = {};
    }

    return { true, hasNext };
}

} // ns rs

#endif
