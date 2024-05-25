#include <iostream>
#include <vector>
#include <algorithm> 
#include <utility> 

//templates
template <typename T>
class AVLTree {
private:
    struct Node {
        T data;
        Node* left;
        Node* right;
        Node* parent; 
        int height;

        Node(T value, Node* parent = nullptr) : data(value), left(nullptr), right(nullptr), parent(parent), height(1) {}
    };

    Node* root;

    int getHeight(Node* node) const {
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

        if (LR) LR->parent = X;
        L->parent = X->parent;
        X->parent = L;

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

        if (RL) RL->parent = X; 
        R->parent = X->parent; 
        X->parent = R;

        updateHeight(X);
        updateHeight(R);

        return R;
    }

    int getBalance(Node* node) const {
        return (node == nullptr) ? 0 : getHeight(node->left) - getHeight(node->right);
    }

    Node* insert(Node* node, T value, Node* parent) {
        if (node == nullptr) {
            return new Node(value, parent);
        }

        if (value <= node->data) {
            node->left = insert(node->left, value, node);
        }
        else {
            node->right = insert(node->right, value, node);
        }

        return balance(node);
    }

    Node* deleteNode(Node* node, T value) {
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
                    node->parent = temp->parent; 
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

    Node* findMin(Node* node) const {
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

    void inOrderTraversal(Node* node, std::vector<T>& result) const {
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

    Node* copyTree(Node* node, Node* parent) const {
        if (node == nullptr) {
            return nullptr;
        }
        Node* newNode = new Node(node->data, parent);
        newNode->left = copyTree(node->left, newNode);
        newNode->right = copyTree(node->right, newNode);
        newNode->height = node->height;
        return newNode;
    }

public:
    AVLTree() : root(nullptr) {}

    AVLTree(const AVLTree& other) : root(copyTree(other.root, nullptr)) {}  //copy

    AVLTree(AVLTree&& other) noexcept : root(other.root) {
        other.root = nullptr;           //move
    }

    ~AVLTree() {
        destroyTree(root);
    }

    AVLTree& operator=(AVLTree other) {
        std::swap(root, other.root); // copy-swap
        return *this;
    }

    void insert(T value) {
        root = insert(root, value, nullptr);
    }

    void deleteNode(T value) {
        root = deleteNode(root, value);
    }

    std::vector<T> toSortArray() const {
        std::vector<T> sortedArray;
        inOrderTraversal(root, sortedArray);
        return sortedArray;
    }

    bool isBalanced() const {
        return checkBalance(root);
    }

    bool checkBalance(Node* node) const {
        if (node == nullptr) {
            return true;
        }

        int balance = getBalance(node);

        if (balance > 1 || balance < -1) {
            return false;
        }

        return checkBalance(node->left) && checkBalance(node->right);
    }

    class Iterator {
    private:
        Node* current;
        
        //remove stack
        Node* findNext(Node* node) {
            if (node == nullptr) return nullptr;

            if (node->right) {
                node = node->right;
                while (node->left) {
                    node = node->left;
                }
                return node;
            }
            else {
                Node* parent = node->parent;
                while (parent && node == parent->right) {
                    node = parent;
                    parent = parent->parent;
                }
                return parent;
            }
        }

    public:
        Iterator(Node* root) : current(root) {
            if (current) {
                while (current->left) {
                    current = current->left;
                }
            }
        }

        //reference
        T& operator*() const {
            return current->data;
        }

        Iterator& operator++() {
            current = findNext(current);
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
    AVLTree<double> tree;

    tree.insert(5.4);
    tree.insert(3.555);
    tree.insert(7.73);
    tree.insert(1.83);
    tree.insert(4.72);
    tree.insert(19.946);
    tree.insert(25.87);
    tree.insert(2.000634);
    tree.insert(52.95);
    tree.insert(6.24536);

    std::cout << "Range-based loop: ";
    for (double value : tree) {
        std::cout << value << " ";
    }
    std::cout << std::endl;

    auto it = tree.begin();
    auto end = tree.end();

    std::cout << "begin(): ";
    for (; it != end; ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    return 0;
}
