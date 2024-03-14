#ifndef MAP_ARRAY_HPP
#define MAP_ARRAY_HPP

#include <algorithm>
#include <iterator>
#include <ranges>
#include <utility>
#include <vector>

template <typename Key, typename Value>
class MapArray {
public:
    class ArrayIterator {
    public:
        // Iterator traits
        using iterator_category = std::random_access_iterator_tag;
        using value_type = std::pair<Key, Value>;
        using difference_type = std::ptrdiff_t;
        using pointer = std::pair<Key, Value>*;
        using reference = std::pair<Key, Value>&;

        explicit ArrayIterator(pointer ptr = nullptr) : ptr(ptr) {}

        ArrayIterator& operator++() {
            ++ptr;
            return *this;
        }

        ArrayIterator& operator--() {
            --ptr;
            return *this;
        }

        ArrayIterator operator++(int) {
            ArrayIterator tmp = *this;
            ++(*this);
            return tmp;
        }

        ArrayIterator operator--(int) {
            ArrayIterator tmp = *this;
            --(*this);
            return tmp;
        }

        ArrayIterator& operator+=(difference_type d) {
            ptr += d;
            return *this;
        }

        ArrayIterator& operator-=(difference_type d) {
            ptr -= d;
            return *this;
        }

        friend ArrayIterator operator+(ArrayIterator it, difference_type d) {
            return ArrayIterator(it.ptr + d);
        }

        friend ArrayIterator operator+(difference_type d, ArrayIterator it) {
            return ArrayIterator(it.ptr + d);
        }

        friend ArrayIterator operator-(ArrayIterator it, difference_type d) {
            return ArrayIterator(it.ptr - d);
        }

        friend difference_type operator-(ArrayIterator lhs, ArrayIterator rhs) {
            return lhs.ptr - rhs.ptr;
        }

        auto operator<=>(const ArrayIterator& other) const = default;

        reference operator*() const {
            return &(ptr -> data);
        }

        pointer operator->() const {
            return ptr -> data;
        }

        reference operator[](difference_type d) const {
            return *(ptr + d);
        }

    private:
        pointer ptr;
    };

    using iterator = ArrayIterator;

    iterator begin() {
        return iterator(data.data());
    }

    iterator end() {
        return iterator(data.data() + data.size());
    }

    Value& operator[](const Key& key) {
    auto pairKey = std::make_pair(key, Value());
    auto comp = [](const value_type& a, const value_type& b) { return a.first < b.first; };
    auto it = std::lower_bound(begin(), end(), pairKey, comp);

    if (it == end() || it->first != key) {
        it = data.insert(it.base(), std::make_pair(key, Value()));
    }

    return it->second;
}

private:
   std::vector<typename MapArray<Key, Value>::value_type> data;
};

#endif // MAP_ARRAY_HPP

