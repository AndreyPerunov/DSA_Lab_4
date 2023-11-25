#include <iostream>
#include <fstream>
#include <string>
#include <vector>


int main() {
  // Declare Tree  

  // Read Data
  std::ifstream file("");

  if (!file.is_open() || !file) {
    std::cerr << "Error opening file" << std::endl;
    return 1;
  }

  std::string line;

  while (getline(file, line)) {
    try {      

    } catch (const std::invalid_argument& e) {
      std::cerr << "Error reading line number." << std::endl;
    }
  }

  file.close();
  std::cout << std::endl;

  // Build Binary Search Tree from file (There should be only tree no additional structures)
  // prevent to add non unique number give error
  // void addElement(node)
  // void deleteElement(node)
  // int treeHeight(root)

  // Task 1. Traverse: Level order traversal: Visits nodes level-by-level and in left-to-right fashion at the same level.  

  // Task 2. Balance: Double Rotation

  // Task 3. Serialize and Deserialize: a Binary Tree to a String ( conver binary tree to a String )

  return 0;
}