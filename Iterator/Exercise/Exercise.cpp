#include <vector>
using namespace std;

template <typename T>
struct Node
{
    T value = T();
    Node<T> *left{nullptr}, *right{nullptr};

    Node(T val, Node<T> *left = nullptr, Node<T> *right = nullptr) : value(val), left(left), right(right) {}

    void preorder_traversal(vector<Node<T>*> &res) {
        preorder_traversal_impl(this, res);
    }

    void preorder_traversal_impl(Node<T> *root, vector<Node<T>*> &res) {
        if(!root) return;
        res.push_back(root);
        preorder_traversal_impl(root->left, res);
        preorder_traversal_impl(root->right, res);
    }
};


