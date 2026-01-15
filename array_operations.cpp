// Array Operations - Basic operations on arrays
// This program demonstrates insertion, deletion, searching, and display operations on an array

#include <iostream>
using namespace std;

const int MAX_SIZE = 100;

// Display array elements
void displayArray(int arr[], int size) {
    cout << "Array elements: ";
    for (int i = 0; i < size; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

// Insert element at a specific position
int insertElement(int arr[], int size, int element, int position) {
    if (size >= MAX_SIZE) {
        cout << "Array is full!" << endl;
        return size;
    }
    if (position < 0 || position > size) {
        cout << "Invalid position!" << endl;
        return size;
    }
    
    // Shift elements to the right
    for (int i = size; i > position; i--) {
        arr[i] = arr[i - 1];
    }
    
    arr[position] = element;
    cout << "Element " << element << " inserted at position " << position << endl;
    return size + 1;
}

// Delete element from a specific position
int deleteElement(int arr[], int size, int position) {
    if (size <= 0) {
        cout << "Array is empty!" << endl;
        return size;
    }
    if (position < 0 || position >= size) {
        cout << "Invalid position!" << endl;
        return size;
    }
    
    int deletedElement = arr[position];
    
    // Shift elements to the left
    for (int i = position; i < size - 1; i++) {
        arr[i] = arr[i + 1];
    }
    
    cout << "Element " << deletedElement << " deleted from position " << position << endl;
    return size - 1;
}

// Search for an element in the array
int searchElement(int arr[], int size, int element) {
    for (int i = 0; i < size; i++) {
        if (arr[i] == element) {
            return i;
        }
    }
    return -1;
}

int main() {
    int arr[MAX_SIZE];
    int size = 0;
    int choice, element, position;
    
    cout << "=== Array Operations Program ===" << endl;
    
    // Initialize array with some values
    cout << "\nInitializing array with values: 10, 20, 30, 40, 50" << endl;
    arr[0] = 10;
    arr[1] = 20;
    arr[2] = 30;
    arr[3] = 40;
    arr[4] = 50;
    size = 5;
    displayArray(arr, size);
    
    do {
        cout << "\n--- Menu ---" << endl;
        cout << "1. Display Array" << endl;
        cout << "2. Insert Element" << endl;
        cout << "3. Delete Element" << endl;
        cout << "4. Search Element" << endl;
        cout << "5. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        
        switch (choice) {
            case 1:
                displayArray(arr, size);
                break;
                
            case 2:
                cout << "Enter element to insert: ";
                cin >> element;
                cout << "Enter position (0 to " << size << "): ";
                cin >> position;
                size = insertElement(arr, size, element, position);
                break;
                
            case 3:
                cout << "Enter position to delete (0 to " << size - 1 << "): ";
                cin >> position;
                size = deleteElement(arr, size, position);
                break;
                
            case 4:
                cout << "Enter element to search: ";
                cin >> element;
                position = searchElement(arr, size, element);
                if (position != -1) {
                    cout << "Element " << element << " found at position " << position << endl;
                } else {
                    cout << "Element " << element << " not found in the array" << endl;
                }
                break;
                
            case 5:
                cout << "Exiting program..." << endl;
                break;
                
            default:
                cout << "Invalid choice! Please try again." << endl;
        }
    } while (choice != 5);
    
    return 0;
}
