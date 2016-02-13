#pragma once

#include <type_traits>
#include <iterator>
#include <utility>

template <bool Condition, class T>
struct add_const_if
{
    typedef T type;
};
template <class T>
struct add_const_if<true, T>
{
    typedef typename std::add_const<T>::type type;
};

template <class Iter>
class key_iterator : public Iter
{
public:
    typedef typename add_const_if<
            std::is_const<typename std::remove_reference<typename std::iterator_traits<Iter>::reference>::type>::value,
            typename std::iterator_traits<Iter>::value_type::first_type
        >::type value_type;

    key_iterator() : Iter()
    {}
    key_iterator(Iter iter) : Iter(iter)
    {}

    value_type& operator*() const
    {
        const Iter& iter = *this;
        return iter->first;
    }
    value_type* operator->() const
    {
        const Iter& iter = *this;
        return &iter->first;
    }
};

template <class Iter>
class value_iterator : public Iter
{
public:
    typedef typename add_const_if<
            std::is_const<typename std::remove_reference<typename std::iterator_traits<Iter>::reference>::type>::value,
            typename std::iterator_traits<Iter>::value_type::second_type
        >::type value_type;

    value_iterator() : Iter()
    {}
    value_iterator(Iter iter) : Iter(iter)
    {}

    value_type& operator*() const
    {
        const Iter& iter = *this;
        return iter->second;
    }
    value_type* operator->() const
    {
        const Iter& iter = *this;
        return &iter->second;
    }
};


template <class Iter>
class KeyRange
{
public:
    typedef key_iterator<Iter> iterator;

private:
    iterator m_begin;
    iterator m_end;

public:
    KeyRange(iterator begin_, iterator end_)
        : m_begin(begin_), m_end(end_)
    {}

    iterator begin() const
    {
        return m_begin;
    }
    iterator end() const
    {
        return m_end;
    }
};


template <class Iter>
class ValueRange
{
public:
    typedef value_iterator<Iter> iterator;

private:
    iterator m_begin;
    iterator m_end;

public:
    ValueRange(iterator begin_, iterator end_)
        : m_begin(begin_), m_end(end_)
    {}

    iterator begin() const
    {
        return m_begin;
    }
    iterator end() const
    {
        return m_end;
    }
};


template <class Map>
KeyRange<typename std::decay<Map>::type::iterator> key_range(Map&& map)
{
    return KeyRange<typename std::decay<Map>::type::iterator>(map.begin(), map.end());
}
template <class Map>
KeyRange<typename std::decay<Map>::type::const_iterator> key_range_const(Map&& map)
{
    return KeyRange<typename std::decay<Map>::type::const_iterator>(map.begin(), map.end());
}

template <class Map>
ValueRange<typename std::decay<Map>::type::iterator> value_range(Map&& map)
{
    return ValueRange<typename std::decay<Map>::type::iterator>(map.begin(), map.end());
}
template <class Map>
ValueRange<typename std::decay<Map>::type::const_iterator> value_range_const(Map&& map)
{
    return ValueRange<typename std::decay<Map>::type::const_iterator>(map.begin(), map.end());
}
