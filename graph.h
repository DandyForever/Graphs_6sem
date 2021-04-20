#pragma once

#include <map>
#include <set>
#include <vector>

class Graph {
public:
    void add_vertex (int v);
    void add_edge (int src, int dest, int weight);
    std::map <int, std::map<int, int>> floyd () const;
    std::set <std::set<int>> get_components ();

private:
    const int INF = 1e9;

    std::map <int, std::map<int, int>> data;

    std::set <std::set<int>> components;
    bool is_calculated = false;
    std::vector <int> end_visit;
    std::set <int> visited;

    void calculate_component();
    void calculate_end_visit(int v);
    void set_component (std::set <int>* component, int v);
    Graph reversed() const;
};
