// Binary Search Tree Implementation
// This program demonstrates BST operations: insertion, traversal (inorder, preorder, postorder), and search

#include <iostream>
using namespace std;

// Node structure for BST
struct Node {
    int data;
    Node* left;
    Node* right;
    
    Node(int value) {
        data = value;
        left = nullptr;
        right = nullptr;
    }
};

class BinarySearchTree {
private:
    Node* root;
    
    // Helper function to insert a node recursively
    Node* insertNode(Node* node, int value) {
        if (node == nullptr) {
            return new Node(value);
        }
        
        if (value < node->data) {
            node->left = insertNode(node->left, value);
        } else if (value > node->data) {
            node->right = insertNode(node->right, value);
        } else {
            cout << "Duplicate value " << value << " not inserted" << endl;
        }
        
        return node;
    }
    
    // Helper function for inorder traversal (Left, Root, Right)
    void inorderTraversal(Node* node) {
        if (node != nullptr) {
            inorderTraversal(node->left);
            cout << node->data << " ";
            inorderTraversal(node->right);
        }
    }
    
    // Helper function for preorder traversal (Root, Left, Right)
    void preorderTraversal(Node* node) {
        if (node != nullptr) {
            cout << node->data << " ";
            preorderTraversal(node->left);
            preorderTraversal(node->right);
        }
    }
    
    // Helper function for postorder traversal (Left, Right, Root)
    void postorderTraversal(Node* node) {
        if (node != nullptr) {
            postorderTraversal(node->left);
            postorderTraversal(node->right);
            cout << node->data << " ";
        }
    }
    
    // Helper function to search for a value
    bool searchNode(Node* node, int value) {
        if (node == nullptr) {
            return false;
        }
        
        if (value == node->data) {
            return true;
        } else if (value < node->data) {
            return searchNode(node->left, value);
        } else {
            return searchNode(node->right, value);
        }
    }
    
public:
    // Constructor
    BinarySearchTree() {
        root = nullptr;
    }
    
    // Insert a value into the BST
    void insert(int value) {
        root = insertNode(root, value);
        cout << "Inserted " << value << " into the BST" << endl;
    }
    
    // Inorder traversal (sorted order)
    void inorder() {
        if (root == nullptr) {
            cout << "Tree is empty!" << endl;
            return;
        }
        cout << "Inorder traversal: ";
        inorderTraversal(root);
        cout << endl;
    }
    
    // Preorder traversal
    void preorder() {
        if (root == nullptr) {
            cout << "Tree is empty!" << endl;
            return;
        }
        cout << "Preorder traversal: ";
        preorderTraversal(root);
        cout << endl;
    }
    
    // Postorder traversal
    void postorder() {
        if (root == nullptr) {
            cout << "Tree is empty!" << endl;
            return;
        }
        cout << "Postorder traversal: ";
        postorderTraversal(root);
        cout << endl;
    }
    
    // Search for a value
    bool search(int value) {
        return searchNode(root, value);
    }
    
    // Check if tree is empty
    bool isEmpty() {
        return root == nullptr;
    }
};

int main() {
    BinarySearchTree bst;
    int choice, value;
    
    cout << "=== Binary Search Tree Program ===" << endl;
    
    do {
        cout << "\n--- Menu ---" << endl;
        cout << "1. Insert Element" << endl;
        cout << "2. Inorder Traversal" << endl;
        cout << "3. Preorder Traversal" << endl;
        cout << "4. Postorder Traversal" << endl;
        cout << "5. Search Element" << endl;
        cout << "6. Check if Empty" << endl;
        cout << "7. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        
        switch (choice) {
            case 1:
                cout << "Enter value to insert: ";
                cin >> value;
                bst.insert(value);
                break;
                
            case 2:
                bst.inorder();
                break;
                
            case 3:
                bst.preorder();
                break;
                
            case 4:
                bst.postorder();
                break;
                
            case 5:
                cout << "Enter value to search: ";
                cin >> value;
                if (bst.search(value)) {
                    cout << "Element " << value << " found in the BST" << endl;
                } else {
                    cout << "Element " << value << " not found in the BST" << endl;
                }
                break;
                
            case 6:
                if (bst.isEmpty()) {
                    cout << "Tree is empty" << endl;
                } else {
                    cout << "Tree is not empty" << endl;
                }
                break;
                
            case 7:
                cout << "Exiting program..." << endl;
                break;
                
            default:
                cout << "Invalid choice! Please try again." << endl;
        }
    } while (choice != 7);
    
    return 0;
}
