// picture.cpp
#include "picture.hpp"
#include <iostream>

// Constructor
Picture::Picture() : head(nullptr), tail(nullptr) {}

// Destructor
Picture::~Picture() {
    ListNode* current = head;
    while (current != nullptr) {
        ListNode* next = current->next;
        delete current->shape; // Free the shape
        delete current; // Free the node
        current = next;
    }
}

// Copy constructor
Picture::Picture(const Picture& other) : head(nullptr), tail(nullptr) {
    ListNode* current = other.head;
    while (current != nullptr) {
        add(*(current->shape)); // Clone and add the shape
        current = current->next;
    }
}

// Move constructor
Picture::Picture(Picture&& other) : head(other.head), tail(other.tail) {
    other.head = nullptr;
    other.tail = nullptr;
}

// Swap
void Picture::swap(Picture& other) {
    using std::swap;
    swap(head, other.head);
    swap(tail, other.tail);
}

// Copy assignment
Picture& Picture::operator=(const Picture& other) {
    Picture temp(other);
    swap(temp);
    return *this;
}

// Move assignment
Picture& Picture::operator=(Picture&& other) {
    swap(other);
    return *this;
}

// Add a clone of shape
void Picture::add(const Shape& shape) {
    ListNode* newNode = new ListNode{shape.clone(), nullptr};
    if (tail) {
        tail->next = newNode;
    } else {
        head = newNode;
    }
    tail = newNode;
}

// Print all shapes
void Picture::print_all(std::ostream& out) const {
    ListNode* current = head;
    while (current != nullptr) {
        current->shape->print(out);
        current = current->next;
    }
}

// Draw all shapes
void Picture::draw_all(std::ostream& out) const {
    ListNode* current = head;
    while (current != nullptr) {
        current->shape->draw(out);
        current = current->next;
    }
}

// Calculate total area
double Picture::total_area() const {
    double total = 0.0;
    ListNode* current = head;
    while (current != nullptr) {
        total += current->shape->area();
        current = current->next;
    }
    return total;
}

