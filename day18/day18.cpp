/* Copyright (c) 2021, Kis Imre. All rights reserved. */
/* SPDX-License-Identifier: MIT */

#include <fstream>
#include <functional>
#include <iostream>
#include <sstream>
#include <list>
#include <vector>

struct Node {
        Node() = default;
        Node(Node *parent) : parent(parent) {
        }

        ~Node() {
            delete left_subtree;
            delete right_subtree;

            if (parent != NULL) {
                if (parent->left_subtree == this) {
                    parent->left_subtree = NULL;
                }
                if (parent->right_subtree == this) {
                    parent->right_subtree = NULL;
                }
            }
        }

        void traverse(const std::function<void(Node *, int)> &f, int level) {
            if (left_subtree) {
                left_subtree->traverse(f, level + 1);
                if (right_subtree) {
                    right_subtree->traverse(f, level + 1);
                }
            } else {
                f(this, level);
            }
        }

        bool explode() {
            bool found = false, done = false, done_right = false;
            unsigned int right_val = 0;
            Node *prev = NULL;

            std::list<Node *> nodes_to_delete;

            traverse([&](Node *node, int level) {
                if (!found) {
                    if (level > 4) {
                        found = true;
                        if(prev) {
                            prev->value += node->value;
                        }

                        right_val = node->parent->right_subtree->value;

                        // Deleting object from lambda while traversing messes up the context
                        nodes_to_delete.push_back(node->parent->left_subtree);
                        nodes_to_delete.push_back(node->parent->right_subtree);

                        node->parent->value = 0;
                    }
                } else if (!done) {
                    done = true;
                } else if (!done_right) {
                    node->value += right_val;
                    done_right = true;
                }
                prev = node;
            }, 0);

            for (auto &node_to_delete : nodes_to_delete) {
                delete node_to_delete;
            }

            return found;
        }

        bool split() {
            bool done = false;
            traverse([&](Node *node, __attribute__((unused)) int level) {
                if (!done && node->value >= 10) {
                    node->left_subtree = new Node(node);
                    node->left_subtree->value = node->value / 2;
                    node->right_subtree = new Node(node);
                    node->right_subtree->value = node->value - node->left_subtree->value;
                    node->value = 0;

                    done = true;
                }
            }, 0);

            return done;
        }

        unsigned int magnitude() {
            return (left_subtree) ? left_subtree->magnitude() * 3 + right_subtree->magnitude() * 2 : value;
        }

        uint32_t value = 0;
        Node *parent = NULL;
        Node *left_subtree = NULL;
        Node *right_subtree = NULL;
};

std::istream &operator >>(std::istream &input, Node &node) {
    char c;

    if (input.peek() == '[') {
        node.left_subtree = new Node(&node);
        node.right_subtree = new Node(&node);
        input >> c >> *node.left_subtree >> c >> *node.right_subtree >> c;
    } else {
        input >> node.value;
    }

    return input;
}

std::ostream &operator <<(std::ostream &output, Node &node) {
    if (node.left_subtree)
        output << "[" << *node.left_subtree << "," << *node.right_subtree << "]";
    else
        output << node.value;
    return output;
}

void part1() {
    std::fstream input("input");

    // First left
    Node *res = new Node;
    input >> *res;
    input.seekg(1, std::ios_base::cur);

    while (input.good()) {
        Node *root = new Node;
        root->left_subtree = res;
        res->parent = root;
        root->right_subtree = new Node(root);

        if (!(input >> *root->right_subtree)) {
            break;
        }
        input.seekg(1, std::ios_base::cur);

        res = root;
        bool run = false;

        do {
            run = false;
            if(res->explode()) {
                run = true;
            }

            if (!run && res->split()) {
                run = true;
            }
        } while (run);
    }

    std::cout << res->magnitude() << std::endl;

    delete res;
}

void part2() {
    std::fstream input("input");

    // First left
    std::string line;
    std::vector<std::string> lines;

    while (input >> line) {
        lines.push_back(line);
    }

    unsigned int max = 0;
    for (size_t i = 0; i < lines.size(); i++) {
        for (size_t j = 0; j < lines.size(); j++) {
            if (i == j) {
                continue;
            }

            Node *root = new Node;
            root->left_subtree = new Node(root);

            std::stringstream a(lines[i]);
            a >> *root->left_subtree;

            root->right_subtree = new Node(root);
            std::stringstream b(lines[j]);
            b >> *root->right_subtree;

            bool run = false;
            do {
                run = false;
                if(root->explode()) {
                    run = true;
                }

                if (!run && root->split()) {
                    run = true;
                }
            } while (run);

            max = std::max(max, root->magnitude());
            delete root;
        }
    }

    std::cout << max << std::endl;
}

int main() {
    part1();
    part2();
}
