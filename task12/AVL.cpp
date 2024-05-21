#include <iostream>
#include <vector>
#include <stack>

class AVLTree {
private:
    struct Node {
        int data;
        Node* left;
        Node* right;
        int height;

        Node(int value) {
            data = value;
            left = nullptr;
            right = nullptr;
            height = 1;
        }
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

    Node* insert(Node* node, int value) {
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

    Node* deleteNode(Node* node, int value) {
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

    void printLevel(Node* node) {
        if (node != nullptr) {
            printLevel(node->left);
            std::cout << node->data << " ";
            printLevel(node->right);
        }
    }

    void inOrderTraversal(Node* node, std::vector<int>& result) {
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

public:
    AVLTree() {
        root = nullptr;
    }

    ~AVLTree() {
        destroyTree(root);
    }

    void insert(int value) {
        root = insert(root, value);
    }

    void deleteNode(int value) {
        root = deleteNode(root, value);
    }

    std::vector<int> toSortArray() {
        std::vector<int> sortedArray;
        inOrderTraversal(root, sortedArray);
        return sortedArray;
    }

    bool isBalanced() {
        return checkBalance(root);
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

    class Iterator {
    private:
        Node* current;
        std::stack<Node*> parents;

    public:
        Iterator(Node* root) : current(root) {
            if (current) {
                while (current->left) {
                    parents.push(current);
                    current = current->left;
                }
            }
        }

        int operator*() const {
            return current->data;
        }

        Iterator& operator++() {
            if (current->right) {
                current = current->right;
                while (current->left) {
                    parents.push(current);
                    current = current->left;
                }
            }
            else if (!parents.empty()) {
                current = parents.top();
                parents.pop();
            }
            else {
                current = nullptr;
            }
            return *this;
        }

        bool operator!=(const Iterator& other) const {
            return current != other.current;
        }
    };

    Iterator begin() {
        return Iterator(root);
    }

    Iterator end() {
        return Iterator(nullptr);
    }

};

int main() {
    AVLTree tree;

    tree.insert(5);
    tree.insert(3);
    tree.insert(7);
    tree.insert(1);
    tree.insert(4);
    tree.insert(19);
    tree.insert(25);
    tree.insert(2);
    tree.insert(52);
    tree.insert(6);


    std::cout << "ranged based loop: ";
    for (int value : tree) {
        std::cout << value << " ";
    }
    std::cout << std::endl;

    AVLTree::Iterator it = tree.begin();
    AVLTree::Iterator end = tree.end();

    std::cout << "begin(): ";
    for (; it != end; ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    return 0;
}