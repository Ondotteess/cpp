#include "AVL.h"
#include <vector>
#include <cstdlib> 

int main() {
    // Test copy constructor
    AVLTree tree1;
    tree1.insert(10);
    tree1.insert(5);
    tree1.insert(15);
    tree1.insert(12);
    tree1.insert(23);
    tree1.insert(9);

    std::cout << "tree1: ";
    tree1.printTree();

    AVLTree tree2(tree1);  
    std::cout << "tree2 (copied from tree1) : ";
    tree2.printTree();

    // Test assignment operator
    AVLTree tree3;
    tree3.insert(1);
    tree3.insert(2);
    tree3.insert(3);
    tree3.insert(4);
    tree3.insert(5);
    tree3.insert(6);

    std::cout << "tree3: ";
    tree3.printTree();

    tree1 = tree3;  
    std::cout << "tree1 after assign tree3: ";
    tree1.printTree();

    // Test self-assignment
    tree1 = tree1;  

    return 0;
}
