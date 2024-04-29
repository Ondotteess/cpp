#include <iostream>
#include <vector>

template <typename T>
class AVLTree {
private:
    struct Node {
        T data;
        Node* left;
        Node* right;
        int height;

        Node(const T& value) : data(value), left(nullptr), right(nullptr), height(1) {}
    };

    Node* root;

    int getHeight(Node* node) {
        return (node == nullptr) ? 0 : node->height;
    }

    void updateHeight(Node* node) {
        if (node != nullptr) {
            node->height = 1 + std::max(getHeight(node->left), getHeight(node->right));
        }
    }

    Node* rightRotate(Node* X) {
        if (X == nullptr || X->left == nullptr) return X;

        Node* L = X->left;
        Node* LR = L->right;

        L->right = X;
        X->left = LR;

        updateHeight(X);
        updateHeight(L);

        return L;
    }

    Node* leftRotate(Node* X) {
        if (X == nullptr || X->right == nullptr) return X;

        Node* R = X->right;
        Node* RL = R->left;

        R->left = X;
        X->right = RL;

        updateHeight(X);
        updateHeight(R);

        return R;
    }

    int getBalance(Node* node) {
        return (node == nullptr) ? 0 : getHeight(node->left) - getHeight(node->right);
    }

    Node* insert(Node* node, const T& value) {
        if (node == nullptr) {
            return new Node(value);
        }

        if (value <= node->data) {
            node->left = insert(node->left, value);
        }
        else {
            node->right = insert(node->right, value);
        }

        return balance(node);
    }

    Node* deleteNode(Node* node, const T& value) {
        if (node == nullptr) {
            return node;
        }

        if (value < node->data) {
            node->left = deleteNode(node->left, value);
        }
        else if (value > node->data) {
            node->right = deleteNode(node->right, value);
        }
        else {
            if (node->left == nullptr || node->right == nullptr) {
                Node* temp = (node->left != nullptr) ? node->left : node->right;

                if (temp == nullptr) {
                    temp = node;
                    node = nullptr;
                }
                else {
                    *node = *temp;
                }

                delete temp;
            }
            else {
                Node* temp = findMin(node->right);

                node->data = temp->data;

                node->right = deleteNode(node->right, temp->data);
            }
        }

        return balance(node);
    }

    Node* findMin(Node* node) {
        while (node->left != nullptr) {
            node = node->left;
        }
        return node;
    }

    Node* balance(Node* node) {
        if (node == nullptr)
            return node;

        updateHeight(node);

        int balanceFactor = getBalance(node);

        if (balanceFactor > 1) {
            if (getBalance(node->left) < 0) {
                node->left = leftRotate(node->left);
            }
            return rightRotate(node);
        }
        if (balanceFactor < -1) {
            if (getBalance(node->right) > 0) {
                node->right = rightRotate(node->right);
            }
            return leftRotate(node);
        }

        return node;
    }

    void inOrderTraversal(Node* node, std::vector<T>& result) {
        if (node != nullptr) {
            inOrderTraversal(node->left, result);
            result.push_back(node->data);
            inOrderTraversal(node->right, result);
        }
    }

    void destroyTree(Node* node) {
        if (node != nullptr) {
            destroyTree(node->left);
            destroyTree(node->right);
            delete node;
        }
    }

    bool checkBalance(Node* node) {
        if (node == nullptr) {
            return true;
        }

        int balance = getBalance(node);

        if (balance > 1 || balance < -1) {
            return false;
        }

        return checkBalance(node->left) && checkBalance(node->right);
    }

public:
    AVLTree() : root(nullptr) {}

    ~AVLTree() {
        destroyTree(root);
    }

    void insert(const T& value) {
        root = insert(root, value);
    }

    void deleteNode(const T& value) {
        root = deleteNode(root, value);
    }

    std::vector<T> toSortArray() {
        std::vector<T> sortedArray;
        inOrderTraversal(root, sortedArray);
        return sortedArray;
    }

    bool isBalanced() {
        return checkBalance(root);
    }

};


int main() {
    AVLTree<unsigned long> avlTree;

    avlTree.insert(10);
    avlTree.insert(20);
    avlTree.insert(30);
    avlTree.insert(40);
    avlTree.insert(50);
    avlTree.insert(25);


    std::vector<unsigned long> sortedArray = avlTree.toSortArray();
    std::cout << "Sorted array: ";
    for (int num : sortedArray) {
        std::cout << num << " ";
    }
    std::cout << std::endl;


    std::cout << "Is balanced: " << std::boolalpha << avlTree.isBalanced() << std::endl;


    avlTree.deleteNode(30);
    std::cout << "Is balanced after deletion: " << std::boolalpha << avlTree.isBalanced() << std::endl;

    return 0;
}
