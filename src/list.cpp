#include "list.hpp"
#include <iostream>


using namespace std;
using list::Node;


Node* list::from_string(const char* s) {
    return (*s=='\0') ? nullptr : new Node{*s, from_string(&s[1])};
} // I use (*k).next for learning purposes. The rest of the functions are written with arrows.


void list::free(Node* head) {
    if (head) {
        Node* thisNode = head;
        Node* nextNode = head->next;
        for (; nextNode != nullptr; nextNode = nextNode->next) {
            delete thisNode;
            thisNode = nextNode;
        }
        delete thisNode;
    }
}


void list::print(std::ostream& out, Node* head) {
    for (Node* k = head; k != nullptr; k = k->next)
        out << k->data;
}


int list::length(Node* head) {
    int i = 0;
    for (Node* k = head; k != nullptr; k = k->next)
        ++i;
    return i;
}


Node* list::copy(Node* head) {
    if (!head) return nullptr;

    Node* c = head->next;
    Node* n = new Node{head->data, nullptr};
    Node* newNode = n;
    for (; c != nullptr; n = n->next, c = c->next)
        n->next = new Node{c->data, nullptr};
    return newNode;
}


int list::compare(Node* lhs, Node* rhs) {
    Node* l = lhs;
    Node* r = rhs;
    for (; l != nullptr && r != nullptr; l = l->next, r = r->next)
        if (l->data != r->data)
            return (l->data - r->data);
    if (l==nullptr)
        return (r==nullptr) ? 0 : (-(r->data));
    return (l->data);
}

int list::compare(Node* lhs, Node* rhs, int n) {
    Node* l = lhs;
    Node* r = rhs;
    int i;
    for (i=0; l != nullptr && r != nullptr && i<n; l = l->next, r = r->next, ++i)
        if (l->data != r->data)
            return (l->data - r->data);
    if (i==n)
        return 0;
    if (l==nullptr)
        return (r==nullptr) ? 0 : (-(r->data));
    return (l->data);
}


Node* list::reverse(Node* head) {
    Node* r = nullptr;
    Node* n = head;

    for (; n != nullptr; n = n->next)
        r = new Node{n->data, r};

    return r;
}


Node* list::append(Node* lhs, Node* rhs) {
    if (lhs==nullptr) return list::copy(rhs);
    if (rhs==nullptr) return list::copy(lhs);

    Node* l = list::copy(lhs);
    Node* r = list::copy(rhs);
    Node* n = l;

    for (; l->next!=nullptr; l=l->next) {}
    l->next = r;

    return n;
}


int list::index(Node* head, Node* node) {
    if (node==nullptr) return -1;
    Node* b = head;
    for (int i=0; b!= nullptr; ++i, b=b->next)
        if (b==node) return i;
    return -1;
}


Node* list::find_char(Node* head, char c) {
    if (head==nullptr) return nullptr;
    return (head->data==c) ? head : find_char(head->next, c);
}


Node* list::find_list(Node* haystack, Node* needle) {
    if (needle==nullptr) return haystack;
    if (haystack==nullptr) return nullptr;

    for (Node* h = haystack; h != nullptr; h = h->next) {
        Node* s = h;
        Node* n = needle;
        for (; n != nullptr; s = s->next, n = n->next)
            if (s==nullptr || s->data != n->data) break;
        if (n==nullptr) return h;
        if (s==nullptr) break;
    }
    return nullptr;
}


Node* list::nth(Node* head, int n) {
    if (head==nullptr) return nullptr;
    return (n==0) ? head : list::nth(head->next, --n);
}


Node* list::last(Node* head) {
    if (head==nullptr) return nullptr;
    return (head->next==nullptr) ? head : list::last(head->next);
}

