#include "picture.hpp"
#include <iostream>
#include <utility>

Picture::Picture() : head(nullptr), tail(nullptr) {}

Picture::Picture(const Picture& other) {
    head = tail = nullptr;
    if (other.head != nullptr) {
        ListNode* current = other.head;
        while (current != nullptr) {
			ListNode* newNode = new ListNode;
            newNode->shape = current->shape->clone();
            if (tail == nullptr) {
                head = tail = newNode;
            } else {
                tail->next = newNode;
                newNode->prev = tail;
                tail = newNode;
            }
            current = current->next;
        }
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
    Picture curr(other);
    swap(curr);
    return *this;
}

Picture& Picture::operator=(Picture&& other) {
	swap(other);
    return *this;
}

void Picture::add(const Shape& shape) {
    ListNode *newEntry = new ListNode;
    newEntry->shape = shape.clone();
    newEntry->next = head;
    if (head == nullptr) {
        tail = newEntry;
    } else {
        head->prev = newEntry;
    }
    head = newEntry;
    newEntry->prev = nullptr;
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
    ListNode* current = head;
    while (current != nullptr) {
        current->shape->draw(out);
        current = current->next;
    }
}


double Picture::total_area() const {
    double total = 0.0;
    ListNode* current = head;
    while (current != nullptr) {
        total += current->shape->area();
        current = current->next;
    }
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
