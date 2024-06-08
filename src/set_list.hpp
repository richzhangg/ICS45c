#ifndef SET_LIST_HPP
#define SET_LIST_HPP

#include <algorithm>
#include <functional>
#include <iterator>
#include <memory>
#include <ranges>

template <typename T>
class SetList {
    struct ListNode {
        T data;
        std::shared_ptr<ListNode> next;
    };

public:
    class ListIterator {
    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = value_type*;
        using reference = value_type&;

        explicit ListIterator(std::shared_ptr<ListNode> ptr = nullptr) : ptr(ptr) {}

        ListIterator& operator++() {
            ptr = ptr->next;
            return *this;
        }

        ListIterator operator++(int) {
            ListIterator tmp = *this;
            ++(*this);
            return tmp;
        }

        reference operator*() const {
            return ptr->data;
        }

        pointer operator->() const {
            return &(ptr->data);
        }

        bool operator==(const ListIterator& other) const = default;

    private:
        std::shared_ptr<ListNode> ptr;
    };

    using value_type = T;
    using iterator = ListIterator;
    // Normally there would be a const_iterator too

    SetList() = default;

    template <std::ranges::input_range Rng>
    explicit SetList(Rng&& rng) : head(nullptr) {
        std::ranges::for_each(std::forward<Rng>(rng),
            std::bind_front(&SetList::insert, this));
    }

    ListIterator begin() {
        return ListIterator(head);
    }

    ListIterator end() {
        return ListIterator(nullptr);
    }

    bool contains(const T& value) {
    for (auto current = head; current != nullptr; ) {
        if (current->data == value) {
            return true;
        }
        current = current->next;
    }
    return false;
	}

    ListIterator insert(T value) {
    auto containsValue = [this, &value]() -> bool {
        for (auto current = head; current != nullptr; current = current->next) {
            if (current->data == value) {
                return true;
            }
        }
        return false;
    };

    if (!containsValue()) {
        head = std::make_shared<ListNode>(ListNode{std::move(value), head});
    }

    return ListIterator(head);
}


private:
    std::shared_ptr<ListNode> head = nullptr;
};

#endif
