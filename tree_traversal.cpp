#include <vector>
#include <stack>
#include <queue>
#include <iostream>

template<typename T>
class BST {
public:
  BST(T val): data {val}, left {nullptr}, right {nullptr} {}
  T data;
  BST* left;
  BST* right;
};

template<typename T>
std::vector<BST<T>*> preorder_traversal(BST<T>* root)
{
  std::vector<BST<T>*> iter;

  if (!root)
    return iter;

  std::stack<BST<T>*> S;

  S.push(root);

  while (!S.empty()) {
    auto node = S.top(); S.pop();
    iter.push_back(node);  // visit the node

    if (node->right)
      S.push(node->right);

    if (node->left)
      S.push(node->left);
  }
}

template<typename T>
std::vector<BST<T>*> inorder_traversal(BST<T>* root)
{
  std::vector<BST<T>*> iter;

  auto current = root;

  std::stack<BST<T>*> S;

  while (!S.empty() || current) {
    if (current) {
      S.push(current);
      current = current->left;
    } else {
      auto node = S.top(); S.pop();
      iter.push_back(node);  // visit the node
      current = node->right;
    }
  }

  return iter;
}

template<typename T>
std::vector<BST<T>*> postorder_traversal(BST<T>* root)
{
  std::vector<BST<T>*> iter;

  BST<T> *current = root, *last = nullptr;

  std::stack<BST<T>*> S;

  while (!S.empty() || current) {
    if (current) {
      S.push(current);
      current = current->left;
    } else {
      auto node = S.top();
      if (node->right && node->right != last) {
        current = node->right;
      } else {
        iter.push_back(node);  //visit the node
        last = node;
        S.pop();
      }
    }
  }

  return iter;
}

template<typename T>
std::vector<BST<T>*> levelorder_traversal(BST<T>* root)
{
  std::vector<BST<T>*> iter;

  if (!root)
    return iter;

  std::queue<BST<T>*> Q;

  Q.push(root);
  
  while (!Q.empty()) {
    auto node = Q.front(); Q.pop();
    iter.push_back(node);

    if (node->left)
      Q.push(node->left);

    if (node->right)
      Q.push(node->right);
  }
}


int main()
{
  BST<int> tree {1};
  tree.left = new BST<int> {2};
  tree.right = new BST<int> {3};
  tree.left->left = new BST<int> {4};
  tree.left->right = new BST<int> {5};
  tree.right->left = new BST<int> {6};

  std::vector<BST<int>*> path = preorder_traversal(&tree);
  for (auto x : path)
    std::cout << x->data << " ";
  std::cout << '\n';

  path = inorder_traversal(&tree);
  for (auto x : path)
    std::cout << x->data << " ";
  std::cout << '\n';

  path = postorder_traversal(&tree);
  for (auto x : path)
    std::cout << x->data << " ";
  std::cout << '\n';

  path = levelorder_traversal(&tree);
  for (auto x : path)
    std::cout << x->data << " ";
  std::cout << '\n';
}
