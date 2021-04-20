#pragma once

#include "node.h"

class TwoThreeTree {
public:
    ~TwoThreeTree();
    bool search (int value) const;
    void insert (int value);
    void remove (int value);

private:
    Node* root;

    Node* search_node (int value) const;
    void update_keys (Node* t);
    void split (Node* t);
    void erase (Node* t);

    int max_value (Node* node) const;
};