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
        using iterator_category = std::random_access_iterator_tag;
        using value_type = std::pair<Key, Value>;
        using difference_type = std::ptrdiff_t;
        using pointer = value_type*;
        using reference = value_type&;

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
            ArrayIterator temp = *this;
            ++(*this);
            return temp;
        }

        ArrayIterator operator--(int) {
            ArrayIterator temp = *this;
            --(*this);
            return temp;
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
            return it += d;
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

        std::pair<Key, Value>& operator*() const {
            return *ptr;
        }

        std::pair<Key, Value>* operator->() const {
            return ptr;
        }

        std::pair<Key, Value>& operator[](difference_type d) const {
            return *(ptr + d);
        }

    private:
        std::pair<Key, Value>* ptr;
    };

    using iterator = ArrayIterator;
    using value_type = std::pair<Key, Value>;

    ArrayIterator begin() {
    return data.empty() ? ArrayIterator() : ArrayIterator(&data[0]);
	}


    ArrayIterator end() {
        return iterator(data.data() + data.size());
    }

    Value& operator[](const Key& key) {
    auto comparator = [](const value_type& a, const value_type& b) { return a.first < b.first; };
    auto it = std::lower_bound(data.begin(), data.end(), std::make_pair(key, Value{}), comparator);
    if (it == data.end() || it->first != key) {
        it = data.insert(it, std::make_pair(key, Value{}));
    }
    return it->second;
	}




private:
    std::vector<value_type> data;
};

#endif

