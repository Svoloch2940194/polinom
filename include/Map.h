#pragma once

#include<iostream>
#include<queue>
using namespace std;

typedef long long ll;
typedef long double ld;

template<class Key, class Value>
class Map {
    struct node
    {
        pair<Key, Value> key;
        node* left;
        node* right;
        node* father;

        node()
        {
            father = nullptr;
            left = nullptr;
            right = nullptr;
        }
    };

    node* be;
    node* head;
    size_t size;
public:

    struct iterator
    {
        node* id;

        iterator() { id = head; }
        iterator(node* x) { id = x; }
        pair<Key, Value>& operator*() { return id->key; }

        bool operator==(iterator x) { return id == x.id; }
        bool operator!=(iterator x) { return id != x.id; }

        iterator& operator=(node* x) { id = x; return *this; }
        iterator operator++()
        {
            Key max_ = id->key.first;
            iterator last = nullptr;
            while (true)
            {
                if (id == nullptr) break;

                if (id->right != nullptr && last != id->right)
                {
                    id = id->right;
                    break;
                }
                else
                {
                    max_ = id->key.first;
                    if (id->father == nullptr || max_ > id->father->key.first) last = id, id = id->father;
                    else { id = id->father; break; }
                }
            }

            return *this;
        }

        iterator operator--()
        {
            Key min_ = id->key.first;
            iterator last = nullptr;

            while (true)
            {
                if (id->left != nullptr && last != id->left)
                {
                    id = id->left;
                    break;
                }
                else
                {
                    min_ = id->key.first;
                    if (id->father == nullptr || min_ < id->father->key.first)last = id, id = id->father;
                    else { id = id->father; break; }
                }

                if (id == nullptr) return id;
            }

            return *this;
        }
    };

    iterator begin(){return be;}
    iterator end(){return nullptr;}

    size_t _size() { return size; }

    Map()
    {
        be = nullptr;

        head = nullptr;
        size = 0;
    }

    ~Map()
    {
        if (head == nullptr) return;

        queue<node*> q;
        q.push(head);
        while (!q.empty())
        {
            node* h = q.front();
            q.pop();

            if (h->left != nullptr) q.push(h->left);
            if (h->right != nullptr) q.push(h->right);

            delete h;
        }

        size = 0;
        head = nullptr;
        be = nullptr;
    }

    Value& operator[](const Key& key)
    {
        bool find = true;
        node* h = head;
        while (h != nullptr)
        {
            if (h->key.first > key)
            {
                if (h->left != nullptr)h = h->left;
                else { find = false; break; }
            }
            if (h->key.first < key)
            {
                if (h->right != nullptr)h = h->right;
                else { find = false; break; }
            }
            if (h->key.first == key) break;
        }

        if (find)
        {
            if (h == nullptr)
            {
                ++size;
                auto x = new node;
                head = x;
                x->key.first = key;
                h = x;
                be = x;
            }
        }
        else
        {
            ++size;
            auto x = new node;
            if (h->key.first > key)
            {
                x->father = h;
                h->left = x;
                x->key.first = key;
                h = h->left;
                if (be->key.first > key) be = x;
            }
            else
            {
                x->father = h;
                h->right = x;
                x->key.first = key;
                h = h->right;
            }
            return h->key.second;
        }

        return h->key.second;
    }
};
