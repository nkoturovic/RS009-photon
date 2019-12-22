#ifndef UNDO_H
#define UNDO_H

#include <future>
#include <numeric>
#include <variant>
#include <iostream>

#include <immer/vector.hpp>

namespace rs {

template <class X, class Action = std::function<void(X&)>>
class Undo {
private:
    X m_origin;
    X m_current;
    bool m_origin_eq_current;

    std::variant<X, std::future<X>> m_previous;
    std::variant<X, std::future<X>> m_next;

    /* Actions that transform origin to current */
    immer::vector<Action> m_previousActions;

    /* Transformations that were previously done 
     than undone - in reverse order (be cautious) */
    immer::vector<Action> m_nextActions;


public:
    Undo(X &&x) : m_origin(x), m_current(std::move(x)), m_origin_eq_current(true) {}

    const X& origin() const { return m_origin; }
    const X& current() const { return m_current; }

    void action(Action && action) {
        m_origin_eq_current = false;
        m_previous = m_current;
        action(m_current);

        m_previousActions = m_previousActions.push_back(std::move(action));

        m_next = {};
        m_nextActions = {};
    }

    /* retval = [ currSucc, willNextUndoSucceed ] */
    std::pair<bool, bool> undo() {

        if (m_origin_eq_current)
            return {false, false};

        /* Postoji bar jedna undo akcija */
        if (m_nextActions.empty()) {
            m_nextActions = m_nextActions.push_back(m_previousActions.back());
            m_previousActions = m_previousActions.take(m_previousActions.size()-1);
        }

        if (m_previousActions.empty()) {
            m_origin_eq_current = true;
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

            m_nextActions = m_nextActions.push_back(m_previousActions.back());
            m_previousActions = m_previousActions.take(m_previousActions.size()-1);

            bool hasPrev = not m_previousActions.empty() || not m_origin_eq_current;
            if (hasPrev) {
                m_previous = std::async(std::launch::async, 
                                    [ origin  = m_origin,
                                      actions = m_previousActions ] () mutable { 
                                        for (const auto &a : actions)
                                            a(origin); 
                                        return origin;
                                    });
            } else {
                m_previous = {};
            }

            return { true, hasPrev };
        }
    }

    /* retval = [ currSucc, willNextRedoSucceed ] */
    std::pair <bool, bool> redo() { 

        if (m_nextActions.empty())
            return { false, false };

        m_previous = std::move(m_current);
        m_origin_eq_current = false;

        try {
            m_current = std::move(std::get<X>(m_next));
        } catch (const std::bad_variant_access&) {
            m_current = std::move(std::get<std::future<X>>(m_next).get());
        } catch (std::exception &e) {
            std::cerr << e.what();
            exit(EXIT_FAILURE);
        }

        m_previousActions = m_previousActions.push_back(m_nextActions.back());
        m_nextActions = m_nextActions.take(m_nextActions.size()-1);


        bool hasNext = not m_nextActions.empty();

        if (hasNext) {
            m_next = std::async(std::launch::async, 
                                [action = m_nextActions.back(), curr=m_current] () mutable { 
                                    action(curr); 
                                    return curr;
                                });
        } else {
            m_next = {};
        }

        return { true, hasNext };
    }
};

} // ns rs

#endif
