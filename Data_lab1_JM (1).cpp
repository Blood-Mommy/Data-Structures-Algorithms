#include <iostream>
#include <algorithm>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>
#include <chrono>
#include <windows.h>

using namespace std;
using namespace chrono;

// load_coins provide a list of integers from the specified file (using vector)
vector<int> load_coins(const string& filename) {
    vector<int> data;
    ifstream inFile(filename);
    if (!inFile) {
        cerr << "Error: Could not open file: " << filename << endl;
        return data;
    }

    int value;
    while (inFile >> value) {
        data.push_back(value);
    }

    inFile.close();
    return data;
}

// print_the_list function, where limit is 30 for testing purposes
void print_the_list(const vector<int>& data, int limit = 30) {
    cout << "[ ";
    int n = min(limit, (int)data.size());
    for (int i = 0; i < n; ++i) {
        cout << data[i] << " ";
    }
    if ((int)data.size() > limit) {
        cout << "...";
    }
    cout << "]" << endl;
}

// insertion sort function, where is based on comparison, and contain time complexity O(n^2) in worst case
void insertion_sort(vector<int>& arr) {
    for (int i = 1; i < (int)arr.size(); ++i) {
        int k = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > k) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = k;
    }
}

//sqrt selection sort function provide a block-based selection-style sort
// for each blockperforms selection operations for each position in the block

void sqrt_selection_sort(vector<int>& arr) {
    int size = (int)arr.size();
	// Determine block size as the square root of the array size
    int block_size = max(1, (int)sqrt(size));
	// Process each block
    for (int i = 0; i < size; i += block_size) {
        int block_end = min(i + block_size, size);
		// Perform selection sort within the current block
        for (int j = i; j < block_end; ++j) {
            int min_index = j;
			// Find the minimum element in the unsorted portion of the block
            for (int k = j + 1; k < size; ++k) {
                if (arr[k] < arr[min_index])
                    min_index = k;
            }
			// Swap the found minimum element with the first element of the unsorted portion
            swap(arr[j], arr[min_index]);
        }
    }
}

// merge sort function, which is based on sorting two sorted subarrays into a single sorted array
// uses temporary vectors for the left and right sides

void merge_function(vector<int>& arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;
	// Create temporary lists for left and right subarrays
    vector<int> L(n1), R(n2);
    for (int i = 0; i < n1; ++i) L[i] = arr[left + i];
    for (int j = 0; j < n2; ++j) R[j] = arr[mid + 1 + j];
	// Merge the temporary arrays back into arr
    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) arr[k++] = L[i++];
        else arr[k++] = R[j++];
    }
	// Copy any remaining elements of L and R
    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];
}

// main part of merge sort
// using merge_function to sort the array recursively

void merge_sort(vector<int>& arr, int left, int right) {
	if (left < right) { // base case
		int mid = left + (right - left) / 2; // to avoid overflow
		merge_sort(arr, left, mid); // sort left half
		merge_sort(arr, mid + 1, right); // sort right half
		merge_function(arr, left, mid, right); // merge sorted halves
    }
}

// measure_time
template <typename Func>
long long measure_time(Func sortingFunction, vector<int> arr) {
	auto start = high_resolution_clock::now(); // start timer
	sortingFunction(arr); // perform sorting (insertion or sqrt selection)
	auto end = high_resolution_clock::now(); // end timer
	return duration_cast<milliseconds>(end - start).count(); // return duration in milliseconds
}

// measure function for merge sort
long long measureMergeSort(vector<int> arr) {
	auto start = high_resolution_clock::now(); // start timer
	merge_sort(arr, 0, (int)arr.size() - 1); // perform merge sort
	auto end = high_resolution_clock::now(); // end timer
	return duration_cast<milliseconds>(end - start).count(); // return duration in milliseconds
}

// Function to get the directory of the executable
string get_direction() {
	char buf[MAX_PATH]; // buffer to hold the path
	DWORD len = GetModuleFileNameA(NULL, buf, MAX_PATH); // get the executable path
	if (len == 0 || len == MAX_PATH) return string(); // error handling
    string p(buf, len);
	size_t pos = p.find_last_of("\\/"); // find last directory separator
	if (pos == string::npos) return string(); // no separator found
    return p.substr(0, pos);
}

// Main function
int main() {

	// Start the program
	cout << "Author: Jaroslavs Monastirskis\n";
    cout << "Course: Data Structures and Algorithms\n";
	cout << "Laboratory work 1: Arrays and Sorting Algorithms\n";
	cout << "----------------------------------------------------\n";


	// Filename to load data from
    const string filename = "coins.data";
    
	// Load data from file in the executable directory
    vector<int> data;
    string exeDir = get_direction();
	// If executable directory is found, load the data
    if (!exeDir.empty()) {
        string path = exeDir + "\\" + filename;
        cout << "Loading from executable directory: " << path << endl;
        data = load_coins(path);
    }
	// print error message
    else {
        cerr << "Error! Could not determine executable directory.\n";
    }
	// Check if data is loaded
    if (data.empty()) {
        cerr << "Error! No data loaded.\n";
        return 1;
    }

    cout << "Succesfully loaded " << data.size() << " coin values.\n";

	// test sorting algorithms on the first 30 values
    int n = min(30, (int)data.size());
    vector<int> subset(data.begin(), data.begin() + n);

    cout << "----------------------------------------------------\n";
    cout << "--- Testing Sorting Algorithms with first 30 values ---\n";
    cout << "Original list:\n";
    print_the_list(subset, n);
    cout << "----------------------------------------------------\n";

    // Insertion Sort demonstration (works in-place on the copy)
    vector<int> copy_insertion = subset;
    insertion_sort(copy_insertion);
    cout << "After Insertion Sort:\n";
    print_the_list(copy_insertion, n);
    cout << "----------------------------------------------------\n";

    // sqrt Selection Sort demonstration
    vector<int> copy_selection = subset;
    sqrt_selection_sort(copy_selection);
    cout << "After √ Selection Sort:\n";
    print_the_list(copy_selection, n);
    cout << "----------------------------------------------------\n";

    // Merge Sort demonstration 
    vector<int> copy_merge = subset;
    merge_sort(copy_merge, 0, n - 1); 
    cout << "After Merge Sort:\n";
    print_the_list(copy_merge, n);
    cout << "----------------------------------------------------\n";

    // Performance with different sortings algorithms (timings printed in milliseconds)
    vector<int> test_sizes = { 100, 500, 1000, 5000, 10000 };
    for (int n : test_sizes) {
        if (n > (int)data.size()) break;
		// Create subset for testing
        vector<int> subset(data.begin(), data.begin() + n);
		// Measure and print times for each sorting algorithm
        cout << "\nTesting with " << n << " elements:\n";
        cout << "Insertion Sort: " << measure_time(insertion_sort, subset) << " ms\n";
        cout << "sqrt Selection Sort: " << measure_time(sqrt_selection_sort, subset) << " ms\n";
        cout << "Merge Sort: " << measureMergeSort(subset) << " ms\n";
        cout << "----------------------------------------------------\n";
    }

    return 0;
}