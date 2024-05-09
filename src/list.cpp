#include <iostream>
#include "list.hpp"
using namespace std;
using list::Node;

Node* list::from_string(const char* s) {
	Node* head = nullptr;
    Node* current = nullptr;
    while (*s != '\0') {
        if (head == nullptr) {
            head = new Node{*s, nullptr};
            current = head;
        } else {
            current->next = new Node{*s, nullptr};
            current = current->next;
        }
        s++;
    }
    
    return head;
}

void list::free(Node* head) {
	while (head != nullptr) {
        Node* toDelete = head;
        head = head->next;
        delete toDelete;
    }
}

void list::print(std::ostream& out, Node* head) {
	Node* current = head;
    while (current != nullptr) {
        out << current->data;
        current = current->next;
    }
}

Node* list::copy(Node* head) {
	if (head == nullptr) {
        return nullptr;
    } else {
        Node* newNode = new Node{head->data, list::copy(head->next)};
        return newNode;
    }
}

int list::compare(Node* lhs, Node* rhs) {
	while (lhs != nullptr && rhs != nullptr) {
        if (lhs->data != rhs->data) {
            return lhs->data - rhs->data;
        }
        lhs = lhs->next;
        rhs = rhs->next;
    }
	if (lhs == nullptr) {
        return rhs == nullptr ? 0 : -rhs->data;
    }
    return lhs->data;
}

int list::compare(Node* lhs, Node* rhs, int n) {
	while (n-- > 0) {
        if (!lhs && rhs) return -1;
        if (lhs && !rhs) return 1;
        if (!lhs && !rhs) return 0;
        if (lhs->data < rhs->data) return -1;
        if (lhs->data > rhs->data) return 1;
        lhs = lhs->next;
        rhs = rhs->next;
    }
    return 0;
}

int list::length(Node* head) {
	int count = 0;
    Node* current = head;
    while (current) {
        count++;
        current = current->next;
    }
    return count;
}

Node* list::reverse(Node* head) {
	Node* rev = nullptr;
	for (Node* o = head; o; o = o->next) {
    	Node* newNode = new Node{o->data, rev};
    	rev = newNode;
	}
	return rev;
}

Node* list::append(Node* lhs, Node* rhs) {
	if (!lhs && !rhs) return nullptr;
    Node* newNode = new Node{};
    if (!lhs) {
        newNode->data = rhs->data;
        newNode->next = list::append(lhs, rhs->next);
    } else {
        newNode->data = lhs->data;
        newNode->next = list::append(lhs->next, rhs);
    }
    return newNode;
}

int list::index(Node* head, Node* node) {
	if (node == nullptr) return -1;
    Node* current = head;
    int index = 0;
    while (current != nullptr) {
        if (current == node) return index;
        current = current->next;
        index++;
    }
    return -1;
}

Node* list::find_char(Node* head, char c) {
	if (!c) return nullptr;
    Node* p = head;
    while (p) {
        if (p->data == c)
            return p;
        p = p->next;
    }
    return nullptr;
}

Node* list::find_list(Node* haystack, Node* needle) {
	int needle_len = list::length(needle);
    if (needle_len == 0) {
        return haystack;
    }
    Node* current = haystack;
    while (current = find_char(current, needle->data)) {
        if (list::compare(current, needle, needle_len) == 0) {
            return current;
        }
        current = current->next;
    }

    return nullptr;
}

Node* list::nth(Node* head, int n) {
	if (!head) {
        return nullptr;
    }
    if (n == 0) {
        return head;
    }
    return nth(head->next, n - 1);
}

Node* list::last(Node* head) {
	if (head == nullptr) {
        return nullptr;
    }
    if (head->next == nullptr) {
        return head;
    }
    return last(head->next);
}
