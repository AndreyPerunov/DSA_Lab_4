#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <queue>

// Requirements: build binary sorted tree✅
class Tree {
public:
  struct Node {
    int data;
    int height;
    Node* left;
    Node* right;
  };

  Node* root;

  Tree() {
    root = nullptr;
  }

  Tree(Node* node) {
    root = node;
  }

  Tree(std::string data) {
    root = nullptr;
    deserialize(data);
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

  // Task for all: void deleteElement(node)✅
  void deleteElement(Node* node) {
    root = deleteNode(root, node);
  }

  Node* deleteNode(Node* root, Node* node) {
    if (root == nullptr) {
      return root;
    } else if (node->data < root->data) {
      root->left = deleteNode(root->left, node);
    } else if (node->data > root->data) {
      root->right = deleteNode(root->right, node);
    } else {
      if (root->left == nullptr) {
        Node* temp = root->right;
        delete root;
        return temp;
      } else if (root->right == nullptr) {
        Node* temp = root->left;
        delete root;
        return temp;
      } else {
        Node* temp = minValueNode(root->right);
        root->data = temp->data;
        root->right = deleteNode(root->right, temp);
      }
    }

    // Update height
    updateHeight(root);

    int balance = getBalance(root);
    if (balance == 2 && getBalance(root->left) >= 0) {
      return rightRotate(root);
    } else if (balance == 2 && getBalance(root->left) == -1) {
      root->left = leftRotate(root->left);
      return rightRotate(root);
    } else if (balance == -2 && getBalance(root->right) <= 0) {
      return leftRotate(root);
    } else if (balance == -2 && getBalance(root->right) == 1) {
      root->right = rightRotate(root->right);
      return leftRotate(root);
    }
    return root;
  }

  Node* minValueNode(Node* node) {
    Node* current = node;
    while (current->left != nullptr) {
      current = current->left;
    }
    return current;
  }

  // Task for all: int treeHeight(root)✅
  int treeHeight(Node* root) {
    return root == nullptr ? -1 : root->height;
  }

  void updateHeight(Node* node) {
    node->height = std::max(treeHeight(node->left), treeHeight(node->right)) + 1;
  }

  void print(Node* root) {
    std::cout << serialize(root) << std::endl;
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

  // Task 3. Serialize and Deserialize: a Binary Tree to a String ( convert binary tree to a String )✅
  std::string serialize(Node* root) {
    std::string result = "";
    // Task 1. Traverse: Level order traversal: Visits nodes level-by-level and in left-to-right fashion at the same level.✅
    std::queue<Node*> queue; // FIFO
    queue.push(root);
    while (queue.size() > 0) {
      Node* node = queue.front(); // get first element
      queue.pop(); // remove first element
      result += std::to_string(node->data) + " ";
      if (node->left != nullptr) {
        queue.push(node->left);
      }
      if (node->right != nullptr) {
        queue.push(node->right);
      }
    }
    if (result.length() > 0) {
      result.pop_back();
    }
    return result;
  };
  
  Node* deserialize(std::string data) {
    std::vector<std::string> nodes;
    std::string node = "";
    for (int i = 0; i < data.length(); i++) {
      if (data[i] == ' ') {
        nodes.push_back(node);
        node = "";
      } else {
        node += data[i];
      }
    }
    nodes.push_back(node);
    for (int i = 0; i < nodes.size(); i++) {
      try {
        addElement(createNode(std::stoi(nodes[i])));
      } catch (const std::invalid_argument& e) {
        std::cout << "Error reading number." << std::endl;
      }
    }
    return Tree::root;
  }
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

  std::cout << "Tree:" << std::endl;
  tree.print(tree.root);

  std::cout << std::endl;

  std::cout << "Search 5:" << std::endl;
  tree.search(5);
  std::cout << "Search 91:" << std::endl;
  tree.search(91);
  std::cout << "Search 41:" << std::endl;
  tree.search(41);

  std::cout << std::endl;

  std::cout << "Serialize:" << std::endl;
  std::string resultOfSerialization = tree.serialize(tree.root);
  std::cout << resultOfSerialization << std::endl;  

  std::cout << std::endl;
  
  Tree tree2;
  std::cout << "Deserialize:" << std::endl;
  tree2.deserialize(resultOfSerialization);
  tree2.print(tree2.root);

  std::cout << std::endl;

  std::cout << "Delete 5:" << std::endl;
  Tree::Node* node = tree.search(5);
  tree.deleteElement(node);
  tree.print(tree.root);

  return 0;
}