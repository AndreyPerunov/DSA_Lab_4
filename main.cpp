#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <queue>

// Requirements: build binary sorted tree
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

  // Task for all: prevent to add non unique number give error✅
  void addElement(Node* currentNode, Node* newNode) {
    if (root == nullptr) {
      root = newNode;
      return;
    }
    if (newNode->data < currentNode->data) {
      if (currentNode->left == nullptr) {
        currentNode->left = newNode;
      } else {
        addElement(currentNode->left, newNode);
      }
    } else if (newNode->data > currentNode->data) {
      if (currentNode->right == nullptr) {
        currentNode->right = newNode;
      } else {
        addElement(currentNode->right, newNode);
      }
    } else {
      std::cout << "Error: non unique number" << std::endl;
    }

    updateHeight(currentNode);
    // balanceTree(currentNode);
  }

  // ✅
  int treeHeight(Node* root) {
    return root == nullptr ? -1 : root->height;
  }

  // ✅
  void updateHeight(Node* node) {
    node->height = std::max(treeHeight(node->left), treeHeight(node->right)) + 1;
  }
  
  void deleteElement(Node* node);
  // Task 1. Traverse: Level order traversal: Visits nodes level-by-level and in left-to-right fashion at the same level.
  // Level Order Traversal ✅
  void printTree(Node* root) {
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
  // Requirements: Implement a tree element search by a given value.
  Node* getNode(int data);
  // Task 2. Balance: Double Rotation
  void balanceTree(Node* root);
};

int main() {
  // Declare Tree  
  Tree tree;

  tree.addElement(tree.root, tree.createNode(20));
  tree.addElement(tree.root, tree.createNode(10));
  tree.addElement(tree.root, tree.createNode(40));
  tree.addElement(tree.root, tree.createNode(30));
  tree.addElement(tree.root, tree.createNode(50));
  tree.addElement(tree.root, tree.createNode(21));

  tree.printTree(tree.root);
  return 0;

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
      tree.addElement(tree.root, tree.createNode(number));
    } catch (const std::invalid_argument& e) {
      std::cerr << "Error reading line number." << std::endl;
    }
  }

  file.close();
  std::cout << std::endl;

  // Task 1. Traverse: Level order traversal: Visits nodes level-by-level and in left-to-right fashion at the same level.  

  // Task 2. Balance: Double Rotation

  // Task 3. Serialize and Deserialize: a Binary Tree to a String ( conver binary tree to a String )

  return 0;
}