#include "list.hpp"
#include <cassert>
#include <iostream>

namespace list {

Node* from_string(const char* s) {
    if (s == nullptr || *s == '\0') {
        return nullptr;
    }
    
    Node* head = new Node{.data = *s, .next = nullptr};
    Node* current = head;
    ++s;

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
        free(newHead);
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
        return 0;
    } else if (lhs == nullptr) {
        return -1;
    } else if (rhs == nullptr) {
        return 1;
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
    assert(n >= 0); 
    while (n > 0 && lhs != nullptr && rhs != nullptr && lhs->data == rhs->data) {
        lhs = lhs->next;
        rhs = rhs->next;
        --n;
    }

    if (n == 0 || (lhs == nullptr && rhs == nullptr)) {
        return 0; 
    } else if (lhs == nullptr) {
        return -1; 
    } else if (rhs == nullptr) {
        return 1; 
    } else {
        return lhs->data < rhs->data ? -1 : 1;
    }
}

Node* reverse(Node* head) {
    Node* prev = nullptr;
    Node* current = head;
    Node* next = nullptr;
    
    while (current != nullptr) {
        next = current->next;  
        current->next = prev;  
        prev = current;        
        current = next;       
    }
    return prev;
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
    return -1;
}

Node* find_char(Node* head, char c) {
    for (Node* current = head; current != nullptr; current = current->next) {
        if (current->data == c) {
            return current;
        }
    }
    return nullptr;
}

Node* find_list(Node* haystack, Node* needle) {
    if (needle == nullptr) return haystack;
    for (Node* h = haystack; h != nullptr; h = h->next) {
        Node* n = needle;
        Node* h_sub = h;
        while (h_sub != nullptr && n != nullptr && h_sub->data == n->data) {
            h_sub = h_sub->next;
            n = n->next;
        }
        if (n == nullptr) {
            return h;
        }
    }
    return nullptr;
}

Node* nth(Node* head, int n) {
    assert(n >= 0);
    while (n > 0 && head != nullptr) {
        head = head->next;
        --n;
    }
    return head;
}

Node* last(Node* head) {
    if (head == nullptr) return nullptr;
    while (head->next != nullptr) {
        head = head->next;
    }
    return head;
}
}
