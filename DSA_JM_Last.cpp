#include <iostream>
#include <algorithm>
using namespace std;

struct BalancedBinaryTree {
    struct Node {
        int data;               // value stored in the node
        Node* left;             // pointer to left child
        Node* right;            // pointer to right child
        int height;             // height for AVL balancing
        //for leaf node initialization
        Node(int value) : data(value), left(nullptr), right(nullptr), height(1) {}
    };
    //root of the provided tree
    Node* root = nullptr;
    // height returning of a node
    int height(Node* node) {
        return node ? node->height : 0;
    }
    //checks if the tree is balanced
    int balanceFactor(Node* node) {
        return node ? height(node->left) - height(node->right) : 0;
    }
    //updates the height after removing and insertion
    void updateHeight(Node* node) {
        node->height = 1 + max(height(node->left), height(node->right));
    }
    //rotation to right
    Node* rotateRight(Node* y) {
        Node* x = y->left;
        Node* T2 = x->right;

        x->right = y;
        y->left = T2;

        updateHeight(y);
        updateHeight(x);

        return x;
    }
    //rotation to left
    Node* rotateLeft(Node* x) {
        Node* y = x->right;
        Node* T2 = y->left;

        y->left = x;
        x->right = T2;

        updateHeight(x);
        updateHeight(y);

        return y;
    }
    //insert essential keys and balance the tree
    Node* insert(Node* node, int key) {
        if (!node)
            return new Node(key);

        if (key < node->data)
            node->left = insert(node->left, key);
        else if (key > node->data)
            node->right = insert(node->right, key);
        else
            return node;

        updateHeight(node);
        int balance = balanceFactor(node);

        if (balance > 1 && key < node->left->data)
            return rotateRight(node);

        if (balance < -1 && key > node->right->data)
            return rotateLeft(node);

        if (balance > 1 && key > node->left->data) {
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }

        if (balance < -1 && key < node->right->data) {
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }

        return node;
    }
    //find the minimum value of the node
    Node* findMin(Node* node) {
        while (node->left)
            node = node->left;
        return node;
    }
    //removes key and rebalnce the provided tree
    Node* remove(Node* node, int key) {
        if (!node)
            return nullptr;

        if (key < node->data)
            node->left = remove(node->left, key);
        else if (key > node->data)
            node->right = remove(node->right, key);
        else {

            //node with one child or zero child
            if (!node->left || !node->right) {
                Node* temp = node->left ? node->left : node->right;
                if (!temp) {
                    temp = node;
                    node = nullptr;
                }
                else {
                    *node = *temp;
                }
                delete temp;
            }
            else {

                //node with two childs
                Node* temp = findMin(node->right);
                node->data = temp->data;
                node->right = remove(node->right, temp->data);
            }
        }

        if (!node)
            return nullptr;

        updateHeight(node);
        int balance = balanceFactor(node);

        if (balance > 1 && balanceFactor(node->left) >= 0)
            return rotateRight(node);

        if (balance > 1 && balanceFactor(node->left) < 0) {
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }

        if (balance < -1 && balanceFactor(node->right) <= 0)
            return rotateLeft(node);

        if (balance < -1 && balanceFactor(node->right) > 0) {
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }


        return node;
    }
    //search for a key in the provided tree
    bool search(Node* node, int key) {
        if (!node) return false;
        if (node->data == key) return true;
        if (key < node->data) return search(node->left, key);
        return search(node->right, key);
    }
    //function for postorder traversal algorithm
    void postorderTraversal(Node* node) {
        if (node) {
            postorderTraversal(node->left);
            postorderTraversal(node->right);
            cout << node->data << " ";
        }
    }
    // checks if the provided tree is balanced
    bool isBalanced(Node* node) {
        if (!node) return true;
        int bf = balanceFactor(node);
        if (bf < -1 || bf > 1) return false;
        return isBalanced(node->left) && isBalanced(node->right);
    }
    //shows the graphical representation of the tree
    void printTree(Node* node, string prefix = "", bool isLeft = false) {
        if (!node) return;

        if (node->right)
            printTree(node->right, prefix + (isLeft ? "|   " : "    "), false);

        cout << prefix << (isLeft ? "-- " : "-- ") << node->data << endl;

        if (node->left)
            printTree(node->left, prefix + (isLeft ? "    " : "|   "), true);
    }
    // for user interaction functions
    void insert(int key) { root = insert(root, key); }
    void remove(int key) { root = remove(root, key); }
    bool search(int key) { return search(root, key); }
    void printPostorder() { postorderTraversal(root); cout << endl; }
    void printGraphical() { printTree(root); }
    bool isBalanced() { return isBalanced(root); }
};

//main part
int main() {
    cout << "Laboratory work 4: Recursive data structure: Trees\n";
    cout << "Variant 2: Postorder traversal algorithm\n";
    cout << "Author: Jaroslavs Monastirskis\n";
    cout << "----------------------------------------------------------\n";
    BalancedBinaryTree tree;
    //the list of elements
    int elements[] = { 10, 20, 30, 40, 50, 25, 74, 11, 4, 88 };
    for (int x : elements)


        //insert a tree
        tree.insert(x);
    //call function for graphical representation of the provided tree
    cout << "Graphical representation of the tree:\n";
    tree.printGraphical();
    cout << "---------------------------------------------------------------------\n";

    //show postorder traversal of the tree
    cout << "\nPostorder traversal:\n";
    tree.printPostorder();
    cout << "---------------------------------------------------------------------\n";

    //ask user for a key
    int key;
    cout << "\nPlease, enter key that you want to remove: ";
    cin >> key;
    //found key and delete it if it is founded
    if (tree.search(key)) {
        tree.remove(key);
        cout << "Key successfully deleted.\n";
    }
    else {
        cout << "Error. The provided key does not exist in the provided tree.\n";
    }
    cout << "---------------------------------------------------------------------\n";


    //show updated tree
    cout << "\nTree after deletion:\n";
    tree.printGraphical();
    cout << "---------------------------------------------------------------------\n";

    //provide updated postorder traversal
    cout << "\nPostorder traversal:\n";
    tree.printPostorder();
    cout << "---------------------------------------------------------------------\n";

    //check if the tree is balanced or not
    cout << "\nIs the provided tree balanced?" << (tree.isBalanced() ? "yes" : "no") << endl;
    cout << "_____________________________________________________________________\n";

    return 0;
}
