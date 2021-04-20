#include <algorithm>
#include "two_three_tree.h"

bool comp (Node* lv, Node* rv) {
    if (lv->is_leaf())
        return (lv->get_value() < rv->get_value());
    else
        if (!lv->get_length())
            return false;
        if (!rv->get_length())
            return true;
        return (lv->get_keys()[lv->get_length() - 1] < rv->get_keys()[rv->get_length() - 1]);
}

Node* TwoThreeTree::search_node(int value) const {
    Node* t = root;
    if (!t)
        return nullptr;
    while (!t->is_leaf()) {
        if (t->get_length() == 2) {
            if (t->get_keys()[0] < value) {
                t = (*t->get_sons())[1];
            } else {
                t = (*t->get_sons())[0];
            }
        } else if (t->get_keys()[1] < value) {
            t = (*t->get_sons())[2];
        } else if (t->get_keys()[0] < value) {
            t = (*t->get_sons())[1];
        } else {
            t = (*t->get_sons())[0];
        }
    }
    return t;
}

bool TwoThreeTree::search(int value) const {
    Node* result = search_node(value);
    if (!result)
        return false;
    return (result->get_value() == value);
}

void TwoThreeTree::insert(int value) {
    Node* n = new Node(value);
    if (!root) {
        root = n;
        return;
    }
    Node* a = search_node(value);
    if (!a->get_parent()) {
        root = new Node (a, n, a->get_value(), n->get_value(), nullptr, 2);
        a->set_parent(root);
        n->set_parent(root);
        std::sort (root->get_sons()->begin(), root->get_sons()->end(), comp);
    } else {
        Node* p = a->get_parent();
        p->add_son(n);
        n->set_parent(p);
        std::sort (p->get_sons()->begin(), p->get_sons()->end(), comp);
        update_keys(n);
        split (p);
    }
    update_keys(n);
}

void TwoThreeTree::update_keys(Node *t) {
    Node* a = t->get_parent();
    while (a) {
        for (int i = 0; i < a->get_length(); i++) {
            a->set_key(i, max_value((*a->get_sons())[i]));
        }
        a = a->get_parent();
    }
}

int TwoThreeTree::max_value (Node* node) const {
    if (node->is_leaf())
        return node->get_value();
    if (node->get_length())
        return max_value((*node->get_sons())[node->get_length() - 1]);
    return 0;
}

void TwoThreeTree::split(Node *t) {
    if (t->get_length() > 3) {
        Node* a = new Node((*t->get_sons())[2], (*t->get_sons())[3], t->get_keys()[2], t->get_keys()[3], t->get_parent(), 2);
        (*t->get_sons())[2]->set_parent(a);
        (*t->get_sons())[3]->set_parent(a);
        t->del_son((*t->get_sons())[2]);
        t->del_son((*t->get_sons())[2]);
        if (t->get_parent()) {
            t->get_parent()->add_son(a);
            std::sort (t->get_parent()->get_sons()->begin(), t->get_parent()->get_sons()->end(), comp);

            update_keys(t);
            split(t->get_parent());
        } else {
            root = new Node(t, a, t->get_keys()[t->get_length() - 1], a->get_keys()[a->get_length()], nullptr, 2);
            t->set_parent(root);
            a->set_parent(root);
            std::sort (root->get_sons()->begin(), root->get_sons()->begin() + root->get_length(), comp);
        }
    }
}

void TwoThreeTree::remove(int value) {
    Node* t = search_node(value);
    if (t->get_value() == value)
        erase(t);
}

TwoThreeTree::~TwoThreeTree() {
    delete root;
}

void TwoThreeTree::erase(Node *t) {
    if (!t->get_parent()) {
        delete root;
        root = nullptr;
        return;
    } else {
        Node* parent = t->get_parent();
        Node* bro;
        if ((*parent->get_sons())[0] == t)
            bro = (*parent->get_sons())[1];
        else
            bro = (*parent->get_sons())[0];
        if (parent->get_length() > 2) {
            parent->del_son(t);
            delete t;
        } else {
            if (parent == root) {
                root->del_son(t);
                Node* tmp = root;
                root = (*root->get_sons())[0];
                root->set_parent(nullptr);
                delete t;
                tmp->get_sons()->clear();
                delete tmp;
            } else {
                Node* grandparent = parent->get_parent(), *broparent;
                parent->del_son(bro);
                parent->del_son(t);
                if (grandparent->get_length() == 2) {
                    if ((*grandparent->get_sons())[1] == parent)
                        broparent = (*grandparent->get_sons())[0];
                    else
                        broparent = (*grandparent->get_sons())[1];
                } else {
                    if ((*grandparent->get_sons())[2] == parent)
                        broparent = (*grandparent->get_sons())[1];
                    else if ((*grandparent->get_sons())[1] == parent)
                        broparent = (*grandparent->get_sons())[2];
                    else
                        broparent = (*grandparent->get_sons())[1];
                }
                broparent->add_son(bro);
                bro->set_parent(broparent);
                delete t;
                std::sort (broparent->get_sons()->begin(), broparent->get_sons()->end(), comp);
                update_keys(bro);
                split(broparent);
                erase(parent);
            }
        }
        update_keys(bro);
    }
}
