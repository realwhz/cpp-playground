#pragma once

#include <unordered_map>
#include <string>
#include <functional>
#include <iostream>
#include <vector>

class trie {
public:
    trie()
    {
        root_ = new node;
        root_->children.reserve(26);
        root_->is_word = false;
    }

    void insert(const std::string& word)
    {
        if (word.empty())
            return;

        auto n = root_;
        for (auto c: word) {
            auto it = n->children.find(c);
            if (it != n->children.end()) {
                n = it->second;
            } else {
                n->children[c] = new node;
                n = n->children[c];
            }
        }
        n->is_word = true;
    }

    bool search(const std::string& word)
    {
        if (word.empty())
            return true;

        auto n = root_;
        for (auto c: word) {
            if (!n)
                return false;
            if (n->children.find(c) == n->children.end())
                return false;
            n = n->children[c];
        }
        return !n || n->is_word;
    }

    bool prefix_search(const std::string& word)
    {
        if (word.empty())
            return true;

        auto n = root_;
        for (auto c: word) {
            if (!n)
                return false;
            if (n->children.find(c) == n->children.end())
                return false;
            n = n->children[c];
        }
        return !n; 
    }

    void print()
    {
        std::string word;
        print_internal(root_, word);
    }

private:
    struct node {
        std::unordered_map<char, node *> children;
        bool is_word;
    };

    void print_internal(node *n, std::string& word)
    {
        if (!n)
            return;
        if (n->is_word) {
            std::cout << word << std::endl;
            word.pop_back();
            return;
        }
        for (auto const& item: n->children) {
            word += item.first;
            print_internal(item.second, word);
        }
        word.pop_back();
    }

    node * root_;
};
