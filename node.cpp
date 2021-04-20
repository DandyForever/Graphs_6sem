#include <iostream>
#include "node.h"

Node::Node(Node *son1, Node *son2, int key1, int key2, Node *parent, int length):
    leaf_flag(false),
    parent(parent),
    length(length),
    value(0) {
    sons.push_back(son1);
    sons.push_back(son2);
    keys.push_back(key1);
    keys.push_back(key2);
}

Node* Node::get_parent() const { return parent; }
bool Node::is_leaf() const { return leaf_flag; }
std::vector <int> Node::get_keys() const { return keys; }
std::vector <Node*>* Node::get_sons() { return &sons; }
int Node::get_length() const { return length; }
int Node::get_value() const { return value; }

void Node::set_key(int index, int val) { keys[index] = val; }
void Node::set_parent(Node *node) { parent = node; }
void Node::add_son(Node *node) {
    sons.push_back(node);
    keys.push_back(0);
    length++;
}
void Node::del_son (Node* node) {
    auto it = std::find(sons.begin(), sons.end(), node);
    sons.erase(it);
    keys.erase(keys.begin()+(it-sons.begin()));
    length--;
}

Node::~Node() {
    for (auto& item : sons) {
        delete item;
    }
}

std::ostream& operator<< (std::ostream& out, Node& item){
    out << "me: " << &item << std::endl;
    out << "parent: " << item.get_parent() << std::endl;
    out << "length: " << item.get_length() << std::endl;
    out << "leaf flag: " << item.is_leaf() << std::endl;
    out << "value: " << item.get_value() << std::endl;
    out << "keys: ";
    for (auto x : item.get_keys())
        out << x << " ";
    out << std::endl << "sons: ";
    for (auto x : *item.get_sons())
        out << x << " ";
    out << std::endl <<std::endl;
    for (auto x : *item.get_sons())
        out << *x;
    return out;
}