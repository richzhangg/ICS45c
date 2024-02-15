#include "list.hpp"
#include <cassert>
#include <iostream>

namespace list {

Node* from_string(const char* s) {
    if (s == nullptr || *s == '\0') {
        return nullptr; // Handle empty or null input strings
    }
    
    Node* head = new Node{.data = *s, .next = nullptr};
    Node* current = head;
    ++s; // Move to the next character

    while (*s != '\0') {
        current->next = new Node{.data = *s, .next = nullptr};
        current = current->next;
        ++s;
    }

    return head;
}

void free(Node* head) {
    while (head != nullptr) {
        Node* tmp = head;
        head = head->next;
        delete tmp;
    }
}

void print(std::ostream& out, Node* head) {
    for (Node* current = head; current != nullptr; current = current->next) {
        out << current->data;
    }
}

Node* copy(Node* head) {
    if (!head) return nullptr;

    Node* newHead = new Node{head->data, nullptr};
    Node* current = newHead;
    
    try {
        for (Node* it = head->next; it != nullptr; it = it->next) {
            current->next = new Node{it->data, nullptr};
            current = current->next;
        }
    } catch (...) {
        free(newHead); // Deallocate if exception occurs during copy
        throw;
    }

    return newHead;
}

int compare(Node* lhs, Node* rhs) {
    while (lhs != nullptr && rhs != nullptr && lhs->data == rhs->data) {
        lhs = lhs->next;
        rhs = rhs->next;
    }
    
    if (lhs == nullptr && rhs == nullptr) {
        return 0; // Lists are equal
    } else if (lhs == nullptr) {
        return -1; // lhs is shorter than rhs
    } else if (rhs == nullptr) {
        return 1; // lhs is longer than rhs
    } else {
        return lhs->data < rhs->data ? -1 : 1;
    }
}

int length(Node* head) {
    int count = 0;
    for (Node* current = head; current != nullptr; current = current->next) {
        ++count;
    }
    return count;
}

int compare(Node* lhs, Node* rhs, int n) {
    assert(n >= 0); // Ensure n is non-negative
    while (n > 0 && lhs != nullptr && rhs != nullptr && lhs->data == rhs->data) {
        lhs = lhs->next;
        rhs = rhs->next;
        --n;
    }

    if (n == 0 || (lhs == nullptr && rhs == nullptr)) {
        return 0; // Lists are equal up to n nodes or both lists ended
    } else if (lhs == nullptr) {
        return -1; // lhs is shorter than rhs
    } else if (rhs == nullptr) {
        return 1; // lhs is longer than rhs
    } else {
        return lhs->data < rhs->data ? -1 : 1;
    }
}

Node* reverse(Node* head) {
    Node* newHead = nullptr;
    while (head != nullptr) {
        Node* next = head->next;
        head->next = newHead;
        newHead = head;
        head = next;
    }
    return newHead;
}

Node* append(Node* lhs, Node* rhs) {
    if (lhs == nullptr) return copy(rhs);
    Node* newHead = copy(lhs);
    last(newHead)->next = copy(rhs);
    return newHead;
}

int index(Node* head, Node* node) {
    int idx = 0;
    for (Node* current = head; current != nullptr; current = current->next, ++idx) {
        if (current == node) {
            return idx;
        }
    }
    return -1; // Node not found
}

Node* find_char(Node* head, char c) {
    for (Node* current = head; current != nullptr; current = current->next) {
        if (current->data == c) {
            return current;
        }
    }
    return nullptr; // Char not found
}

Node* find_list(Node* haystack, Node* needle) {
    if (needle == nullptr) return haystack; // An empty needle is found at the start
    for (Node* h = haystack; h != nullptr; h = h->next) {
        Node* n = needle;
        Node* h_sub = h;
        while (h_sub != nullptr && n != nullptr && h_sub->data == n->data) {
            h_sub = h_sub->next;
            n = n->next;
        }
        if (n == nullptr) {
            // Found the whole needle in haystack
            return h;
        }
    }
    return nullptr; // Needle not found
}

Node* nth(Node* head, int n) {
    assert(n >= 0); // Ensure n is non-negative
    while (n > 0 && head != nullptr) {
        head = head->next;
        --n;
    }
    return head; // This will return nullptr if n is out of bounds
}

Node* last(Node* head) {
    if (head == nullptr) return nullptr;
    while (head->next != nullptr) {
        head = head->next;
    }
    return head;
}
}
