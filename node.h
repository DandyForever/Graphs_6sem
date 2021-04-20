#pragma once

#include <vector>
#include <algorithm>

class Node {
public:
    explicit Node (int value): leaf_flag(true), value(value), parent(nullptr), length(0){}
    explicit Node (Node* son1, Node* son2, int key1, int key2, Node* parent, int length);

    ~Node ();

    Node* get_parent () const;
    bool is_leaf () const;
    std::vector <Node*>* get_sons ();
    std::vector <int> get_keys () const;
    int get_length () const;
    int get_value () const;

    void set_key (int index, int val);
    void set_parent (Node* node);
    void add_son (Node* node);
    void del_son (Node* node);

private:
    Node* parent;
    std::vector <Node*> sons;
    std::vector <int> keys;
    int length;
    bool leaf_flag;
    int value;
};

std::ostream& operator<< (std::ostream& out, Node& item);