/**
 * @cite Iterator Pattern states that when a data structure needs to be traversed on the client-side, then an iterator API needs to be provided that simplifies the traversal process.
 *
 * @brief Iterator Pattern can be exemplified by a Binary Tree data structure that needs to be traversed.
 */

#include <iostream>
#include <vector>

/**
 * @brief Node of a Binary Tree with left-child, right-child and parent Node ptrs.
 */
template <typename T>
struct Node
{
    Node<T> *left{nullptr}, *right{nullptr}, *parent{nullptr};
    T value = T();

    Node(T val,
         Node<T> *left = nullptr,
         Node<T> *right = nullptr) : left(left), right(right), value(val)
    {
        if (left)
            left->parent = this;

        if (right)
            right->parent = this;
    }

    ~Node()
    {
        if (left)
            delete left;
        if (right)
            delete left;
    }
};

/**
 * @brief Binary Tree class that represents a binary tree and provide traversal funtionality using iterators.
 */
template <typename T>
class BinaryTree
{
    Node<T> *root{nullptr};

public:
    BinaryTree(Node<T> *t) : root(t) {}
    ~BinaryTree() { delete root; }

    // Iterator Class that iterates over the Binary Tree.
    template <typename U>
    class InOrderIterator;

    typedef InOrderIterator<T> iterator;

    // for range-based loops
    iterator begin()
    {
        Node<T> *curr = root;
        while (curr && curr->left)
        {
            curr = curr->left;
        }
        return iterator(curr);
    }

    // for range-based loops
    iterator end()
    {
        return iterator{nullptr};
    }
};

template <typename T>
template <typename U>
class BinaryTree<T>::InOrderIterator
{
    Node<U> *current;

public:
    InOrderIterator(Node<U> *node) : current(node) {}

    bool operator!=(const InOrderIterator<U> &it)
    {
        return it.current != current;
    }

    Node<U> &operator*() { return *current; }

    InOrderIterator<U> &operator++()
    {
        if (current->right)
        {
            current = current->right;
            while (current->left)
            {
                current = current->left;
            }
        }
        else
        {
            Node<U> *p = current->parent;
            while (p && current == p->right)
            {
                current = p;
                p = p->parent;
            }
            current = p;
        }
        return *this;
    }
};

int main()
{
    /**
     *     43
     *    /  \
     *  45   83
     * /  \    \
     *32   46   21
     */
    BinaryTree<int> bt{
        new Node<int>{43,
                      new Node<int>{45,
                                    new Node{32},
                                    new Node{46}},
                      new Node<int>{83,
                                    nullptr,
                                    new Node{21}}}};

    for (auto &node : bt)
    {
        std::cout << node.value << " ";
    }

    return 0;
}