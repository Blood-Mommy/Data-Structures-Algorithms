// Bubble Sort Algorithm
// This program implements bubble sort with visualization of each pass

#include <iostream>
using namespace std;

// Function to display array
void displayArray(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

// Function to swap two elements
void swap(int &a, int &b) {
    int temp = a;
    a = b;
    b = temp;
}

// Bubble sort implementation with visualization
void bubbleSort(int arr[], int size) {
    cout << "\nStarting Bubble Sort..." << endl;
    cout << "Initial array: ";
    displayArray(arr, size);
    
    bool swapped;
    for (int i = 0; i < size - 1; i++) {
        swapped = false;
        cout << "\n--- Pass " << (i + 1) << " ---" << endl;
        
        for (int j = 0; j < size - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
                swapped = true;
                cout << "Swapped " << arr[j + 1] << " and " << arr[j] << ": ";
                displayArray(arr, size);
            }
        }
        
        if (!swapped) {
            cout << "No swaps made - array is sorted!" << endl;
            break;
        }
    }
    
    cout << "\nFinal sorted array: ";
    displayArray(arr, size);
}

int main() {
    int size;
    
    cout << "=== Bubble Sort Program ===" << endl;
    cout << "\nEnter the number of elements: ";
    cin >> size;
    
    if (size <= 0 || size > 100) {
        cout << "Invalid size! Please enter a value between 1 and 100." << endl;
        return 1;
    }
    
    int arr[100];
    cout << "Enter " << size << " elements: " << endl;
    for (int i = 0; i < size; i++) {
        cout << "Element " << (i + 1) << ": ";
        cin >> arr[i];
    }
    
    bubbleSort(arr, size);
    
    return 0;
}
