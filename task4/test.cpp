#include "AVL.cpp"
#include <iostream>

int main() {
    // Test move constructor
    {
        AVLTree tree1;
        tree1.insert(5);
        tree1.insert(3);
        tree1.insert(7);

        AVLTree tree2 = std::move(tree1);

        std::cout << "tree 2: ";
        tree2.printTree(); 
    }

    // Test move assignment operator
    {
        AVLTree tree1;
        tree1.insert(5);
        tree1.insert(3);
        tree1.insert(7);

        AVLTree tree2;
        tree2.insert(10);
        tree2.insert(15);

        tree2 = std::move(tree1);

        std::cout << "tree 2: ";
        tree2.printTree(); 
    }

    // Test self move assignment
    {
        AVLTree tree1;
        tree1.insert(5);
        tree1.insert(3);
        tree1.insert(7);

        AVLTree& treeRef = tree1;
        treeRef = std::move(tree1);

        std::cout << "tree 1: ";
        tree1.printTree(); 
        std::cout << "tree after self move assignment: ";
        treeRef.printTree();
    }

    return 0;
}
