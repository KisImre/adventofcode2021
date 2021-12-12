/* Copyright (c) 2021, Kis Imre. All rights reserved. */
/* SPDX-License-Identifier: MIT */

#include <algorithm>
#include <fstream>
#include <iostream>
#include <list>
#include <map>
#include <numeric>
#include <string>

bool is_lowercase(const std::string &s) {
    for (auto c : s) {
        if (isupper(c)) {
            return false;
        }
    }
    return true;
}

unsigned int traverse(const std::multimap<std::string, std::string> &graph, std::list<std::string> &visited_nodes, const std::string &node, bool can_visit_twice) {
    if (is_lowercase(node) && std::find(visited_nodes.begin(), visited_nodes.end(), node) != visited_nodes.end()) {
        if (!can_visit_twice) {
            return 0;
        }
        can_visit_twice = false;
    }

    if (node.compare("start") == 0 && visited_nodes.size() != 0)
        return 0;

    if (node.compare("end") == 0)
        return 1;

    visited_nodes.push_back(node);
    unsigned int visit_current = 0;
    auto accumulate_paths = [&](auto res, auto& n){ return res + traverse(graph, visited_nodes, n.second, can_visit_twice);};
    auto it = graph.equal_range(node);
    visit_current += std::accumulate(it.first, it.second, 0, accumulate_paths);
    visited_nodes.pop_back();

    return visit_current;
}

int main() {
    std::fstream input("input");
    std::multimap<std::string, std::string> graph;
    std::list<std::string> visited_nodes;

    for (std::string line; input >> line; ) {
        auto sep = line.find('-');
        std::pair edge = {line.substr(0, sep), line.substr(sep + 1, line.size())};
        graph.insert(edge);
        graph.insert(std::pair{edge.second, edge.first});
    }

    std::cout << traverse(graph, visited_nodes, "start", false) << std::endl;
    std::cout << traverse(graph, visited_nodes, "start", true) << std::endl;
}
