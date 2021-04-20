#include <iostream>
#include "graph.h"

void Graph::add_edge(int src, int dest, int weight) {
    data[src][dest] = weight;
}

void Graph::add_vertex(int v) {
    if (!data.count(v))
        data[v] = std::map<int, int>();
}

std::map <int, std::map<int, int>> Graph::floyd() const{
    std::map <int, std::map<int, int>> path = data;
    for (const auto& jtem : path) {
        for (const auto& ktem : path) {
            if (!path[jtem.first].count(ktem.first)) {
                if (jtem.first == ktem.first)
                    path[jtem.first][ktem.first] = 0;
                else
                    path[jtem.first][ktem.first] = INF;
            }
        }
    }
    for (const auto& item : path) {
        for (const auto& jtem : path) {
            for (const auto& ktem : path) {
                path[jtem.first][ktem.first] = std::min(path[jtem.first][ktem.first],
                        path[jtem.first][item.first] + path[item.first][ktem.first]);
            }
        }
    }
    return path;
}

void Graph::calculate_end_visit (int v){
    visited.insert(v);
    if (!data.count(v))
        return;
    for (const auto& item : data.at(v)) {
        if (!visited.count(item.first))
            calculate_end_visit (item.first);
    }
    end_visit.push_back(v);
}

Graph Graph::reversed() const {
    Graph h;
    for (const auto& item : data) {
        h.add_vertex(item.first);
    }

    for (const auto& item : data) {
        for (const auto& jtem : item.second) {
            h.add_edge(jtem.first, item.first, jtem.second);
        }
    }
    return h;
}

std::set <std::set<int>> Graph::get_components () {
    if (!is_calculated) {
        is_calculated = true;
        calculate_component();
    }
    return components;
}

void Graph::calculate_component() {
    Graph h = reversed();
    for (const auto& item : h.data) {
        if (!h.visited.count(item.first))
            h.calculate_end_visit(item.first);
    }
    end_visit = h.end_visit;

    for (int i = static_cast<int>(end_visit.size()) - 1; i >= 0; i--) {
        if (!visited.count(end_visit[i])){
            std::set <int> current;
            set_component(&current, end_visit[i]);
            components.insert(current);
        }
    }
}


void Graph::set_component (std::set <int>* component, int v){
    visited.insert(v);
    component->insert(v);
    if (!data.count(v))
        return;
    for (const auto& item : data.at(v)) {
        if (!visited.count(item.first))
            set_component (component, item.first);
    }
}