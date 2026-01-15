// Stack Implementation using Array
// This program demonstrates stack operations: push, pop, peek, and display

#include <iostream>
using namespace std;

const int MAX_SIZE = 100;

class Stack {
private:
    int arr[MAX_SIZE];
    int top;
    
public:
    // Constructor
    Stack() {
        top = -1;
    }
    
    // Check if stack is empty
    bool isEmpty() {
        return (top == -1);
    }
    
    // Check if stack is full
    bool isFull() {
        return (top == MAX_SIZE - 1);
    }
    
    // Push element onto stack
    void push(int element) {
        if (isFull()) {
            cout << "Stack Overflow! Cannot push " << element << endl;
            return;
        }
        top++;
        arr[top] = element;
        cout << "Pushed " << element << " onto stack" << endl;
    }
    
    // Pop element from stack
    int pop() {
        if (isEmpty()) {
            cout << "Stack Underflow! Stack is empty" << endl;
            return -1;
        }
        int poppedElement = arr[top];
        top--;
        cout << "Popped " << poppedElement << " from stack" << endl;
        return poppedElement;
    }
    
    // Peek at top element without removing it
    int peek() {
        if (isEmpty()) {
            cout << "Stack is empty!" << endl;
            return -1;
        }
        return arr[top];
    }
    
    // Display all elements in the stack
    void display() {
        if (isEmpty()) {
            cout << "Stack is empty!" << endl;
            return;
        }
        cout << "Stack elements (top to bottom): ";
        for (int i = top; i >= 0; i--) {
            cout << arr[i] << " ";
        }
        cout << endl;
    }
    
    // Get current size of stack
    int size() {
        return top + 1;
    }
};

int main() {
    Stack stack;
    int choice, element;
    
    cout << "=== Stack Implementation Program ===" << endl;
    
    do {
        cout << "\n--- Menu ---" << endl;
        cout << "1. Push" << endl;
        cout << "2. Pop" << endl;
        cout << "3. Peek" << endl;
        cout << "4. Display Stack" << endl;
        cout << "5. Check if Empty" << endl;
        cout << "6. Get Size" << endl;
        cout << "7. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        
        switch (choice) {
            case 1:
                cout << "Enter element to push: ";
                cin >> element;
                stack.push(element);
                break;
                
            case 2:
                stack.pop();
                break;
                
            case 3:
                element = stack.peek();
                if (element != -1) {
                    cout << "Top element: " << element << endl;
                }
                break;
                
            case 4:
                stack.display();
                break;
                
            case 5:
                if (stack.isEmpty()) {
                    cout << "Stack is empty" << endl;
                } else {
                    cout << "Stack is not empty" << endl;
                }
                break;
                
            case 6:
                cout << "Current stack size: " << stack.size() << endl;
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
