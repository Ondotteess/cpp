#include "AVL.cpp"
#include <vector>
#include <iostream>
#include <cstdlib> 
#include <algorithm> 
#include <ctime>

std::vector<int> generateRandomArray(int size) {
    std::vector<int> randomArray;
    randomArray.reserve(size);

    for (int i = 0; i < size; ++i) {
        randomArray.push_back(rand() % 100 + 1);
    }

    return randomArray;
}

const size_t SIZE = 100;

int main() {
    srand(static_cast<unsigned>(time(nullptr)));

    AVLTree avl;
    std::vector<int> randomArray = generateRandomArray(SIZE);

    for (int num : randomArray) {
        avl.insert(num);
    }

    std::vector<int> avlArray;
    for (int num : avl.toSortArray()) {
        avlArray.push_back(num);
    }

    sort(randomArray.begin(), randomArray.end());

    bool isSuccess = true;
    for (int i = 0; i < SIZE; i++) {
        if (avlArray[i] != randomArray[i]) {
            isSuccess = false;
        }
    }

    if (isSuccess) {
        std::cout << "Sorting Success!" << std::endl;
    }
    else {
        std::cout << "Failed!" << std::endl;
    }

    AVLTree tree;
    tree.insert(10);
    tree.insert(20);
    tree.insert(30);
    tree.insert(40);
    tree.insert(50);

    tree.deleteNode(30);
    tree.deleteNode(40);

    if (tree.toSortArray().size() == 3) {
        std::vector<int> test = { 10, 20, 50 };
        for (int i = 0; i < 3; i++) {
            if (tree.toSortArray()[i] == test[i]) continue;
            else std::cout << "failed" << std::endl;
        }
        std::cout << "Removing Success!" << std::endl;
    }
    else {
        std::cout << "Removing Failed!" << std::endl;
    }


    AVLTree avl0;
    std::vector<int> randomArray0 = generateRandomArray(SIZE);

    bool isBalanced = true;
    for (int num : randomArray0) {
        avl0.insert(num);
        if (!avl.isBalanced()) isBalanced = false;
    }

    if (isBalanced) {
        std::cout << "Tree is balanced" << std::endl;
    }
    else {
        std::cout << "Tree is not balanced" << std::endl;
    }

    int x;
    std::cin >> x;
    return 0;
}
