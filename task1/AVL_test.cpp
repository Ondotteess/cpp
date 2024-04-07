#include "AVL.cpp"
#include <vector>
#include <cstdlib> 
#include <algorithm> 

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

    std::sort(randomArray.begin(), randomArray.end());

    bool isSuccess = true;
    for (int i = 0; i < SIZE; i++) {
        if (avlArray[i] != randomArray[i]) {
            isSuccess = false;
        }
    }

    if (isSuccess) {
        std::cout << "Success!" << std::endl;
    } else {
        std::cout << "Failed!" << std::endl;
    }

    

    int x;
    std::cin >> x;
    return 0;
}
