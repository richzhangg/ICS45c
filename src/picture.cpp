#include "picture.hpp"
#include <iostream>
#include <utility>

Picture::Picture() : head(nullptr), tail(nullptr) {}

Picture::Picture(const Picture& other) : head(nullptr), tail(nullptr) {
    for (ListNode* current = other.head; current != nullptr; current = current->next) {
        add(*(current->shape));
    }
}

Picture::Picture(Picture&& other) : head(other.head), tail(other.tail) {
    other.head = nullptr;
    other.tail = nullptr;
}

void Picture::swap(Picture& other) {
	using std::swap;
    swap(head, other.head);
    swap(tail, other.tail);
}

Picture& Picture::operator=(const Picture& other) {
	if (this != &other) {
        Picture curr(other);
        swap(curr);
    }
    return *this;
}


Picture& Picture::operator=(Picture&& other) {
	swap(other);
    return *this;
}

void Picture::add(const Shape& shape) {
    ListNode* newNode = new ListNode;
    newNode->shape = shape.clone();
    newNode->prev = nullptr;
    newNode->next = head;
    if (head != nullptr) {
        head->prev = newNode;
    } else {
        tail = newNode;
    }
    head = newNode;
}


void Picture::print_all(std::ostream& out) const {
	ListNode* current = head;
    while (current != nullptr) {
        current->shape->print(out);
        current->shape->draw(out);
        current = current->next;
    }
}

void Picture::draw_all(std::ostream& out) const {
	for(ListNode *node = tail; node; node = node->prev) {
        node->shape->draw(out);
    }
}

double Picture::total_area() const {
	double total = 0;
    for (ListNode* ptr = head; ptr; ptr = ptr->next)
        total += ptr->shape->area();
    return total;
}

Picture::~Picture() {
	for (ListNode* current = head; current != nullptr; ) {
        ListNode* next = current->next;
        delete current->shape;
        delete current;
        current = next;
    }
}
