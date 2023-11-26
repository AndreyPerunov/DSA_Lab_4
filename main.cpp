#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <queue>

// Requirements: build binary sorted tree✅
class Tree {
  struct Node {
    int data;
    int height;
    Node* left;
    Node* right;
  };
public:
  Node* root;

  Tree() {
    root = nullptr;
  }

  Tree(Node* node) {
    root = node;
  }

  Node* createNode(int data) {
    Node* newNode = new Node;
    newNode->data = data;
    newNode->height = 0;
    newNode->left = nullptr;
    newNode->right = nullptr;
    return newNode;
  }

  // Task for all: void addElement(node)✅
  void addElement(Node* newNode) {
    root = insert(root, newNode);
  }

  Node* insert(Node* currentNode, Node* newNode) {
    if (currentNode == nullptr) {
      currentNode = newNode;
      return currentNode;
    }
    if (newNode->data < currentNode->data) {
      currentNode->left = insert(currentNode->left, newNode);
    } else if (newNode->data > currentNode->data) {
      currentNode->right = insert(currentNode->right, newNode);
    } else {
      // Task for all: prevent to add non unique number give error✅
      std::cout << "Error: non unique number" << std::endl;
      return currentNode;
    }

    // Update height
    updateHeight(currentNode);

    // Task 2. Balance: Double Rotation
    int balance = getBalance(currentNode);
    if (balance > 1 && newNode->data < currentNode->left->data) {
      return rightRotate(currentNode);
    }
    if (balance < -1 && newNode->data > currentNode->right->data) {
      return leftRotate(currentNode);
    }
    if (balance > 1 && newNode->data > currentNode->left->data) {
      currentNode->left = leftRotate(currentNode->left);
      return rightRotate(currentNode);
    }
    if (balance < -1 && newNode->data < currentNode->right->data) {
      currentNode->right = rightRotate(currentNode->right);
      return leftRotate(currentNode);
    }
    return currentNode;
  }

  // Task for all: void deleteElement(node)🕐
  void deleteElement(Node* node);

  // Task for all: int treeHeight(root)✅
  int treeHeight(Node* root) {
    return root == nullptr ? -1 : root->height;
  }

  void updateHeight(Node* node) {
    node->height = std::max(treeHeight(node->left), treeHeight(node->right)) + 1;
  }

  // Task 1. Traverse: Level order traversal: Visits nodes level-by-level and in left-to-right fashion at the same level.✅
  void print(Node* root) {
    std::queue<Node*> queue; // FIFO
    queue.push(root);
    while (queue.size() > 0) {
      Node* node = queue.front(); // get first element
      queue.pop(); // remove first element
      std::cout << node->data << " ";
      if (node->left != nullptr) {
        queue.push(node->left);
      }
      if (node->right != nullptr) {
        queue.push(node->right);
      }
    }
  }

  // Requirements: Implement a tree element search by a given value.✅
  Node* search(int data) {
    return getNode(root, data);
  }

  Node* getNode(Node* node, int data) {
    if (node == nullptr) {
      return nullptr;
    }
    if (node->data == data) {
      return node;
    }
    return (data < node->data) ? getNode(node->left, data) : getNode(node->right, data);
  }
  
  // Task 2. Balance: Double Rotation (Left and Right Rotation) ✅
  int getBalance(Node* node) {
    return node == nullptr ? 0 : treeHeight(node->left) - treeHeight(node->right);
  }

  Node* rightRotate(Node* node) {
    Node* x = node->left;
    Node* T = x->right;
    // Perform rotation
    x->right = node;
    node->left = T;
    // Update heights
    updateHeight(node);
    updateHeight(x);
    return x;
  }

  Node* leftRotate(Node* node) {
    Node* x = node->right;
    Node* T = x->left;
    // Perform rotation
    x->left = node;
    node->right = T;
    // Update heights
    updateHeight(node);
    updateHeight(x);
    return x;
  }

  // Task 3. Serialize and Deserialize: a Binary Tree to a String ( convert binary tree to a String )🕐
  std::string serialize(Node* root);
  Node* deserialize(std::string data);
};

int main() {
  // Declare Tree  
  Tree tree;

  // Read Data
  std::ifstream file("delta.txt");

  if (!file.is_open() || !file) {
    std::cerr << "Error opening file" << std::endl;
    return 1;
  }

  std::string line;

  while (getline(file, line)) {
    try {      
      int number = std::stoi(line);
      tree.addElement(tree.createNode(number));
    } catch (const std::invalid_argument& e) {
      std::cerr << "Error reading line number." << std::endl;
    }
  }

  file.close();
  std::cout << std::endl;

  tree.print(tree.root);

  tree.search(5);

  return 0;
}