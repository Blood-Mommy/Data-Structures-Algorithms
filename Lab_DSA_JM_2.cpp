#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <string>
#include <chrono>
#include <iomanip>
#include <windows.h>  
#include <direct.h>  
#include <cstdio>
#include <limits>

using namespace std;
using namespace chrono;

// Passenger structure for list elements
struct Passenger {
    string name;
    string surname;
    int index = 0; 
};

// Function to have the executable directory
string get_direction() {
    char buf[MAX_PATH]; // buffer to hold the path
    DWORD len = GetModuleFileNameA(NULL, buf, MAX_PATH); // get the executable path
    if (len == 0 || len == MAX_PATH) return string(); // error handling
    string p(buf, len);
    size_t pos = p.find_last_of("\\/"); // find last directory separator
    if (pos == string::npos) return string(); // no separator found
    return p.substr(0, pos);
}
// Function to load passengers from file
vector<Passenger*> load_passengers(const string& filename) {
    vector<Passenger*> list;
	ifstream inFile(filename); // try to open file

	// If file not found, try alternative path
    if (!inFile) {
        // Diagnostic: show current working directory and attempted filename
        char cwd[FILENAME_MAX];
        if (_getcwd(cwd, sizeof(cwd)) != nullptr) {
            cerr << "Error: Could not open file: " << filename << endl; 
            cerr << "Current working directory: " << cwd << endl;
        }
        else {
            cerr << "Error: Could not open file: " << filename << " (failed to get current directory)" << endl;
        }

		// try to open from executable directory
        string exeDir = get_direction();
        if (!exeDir.empty()) {
            string fullPath = exeDir + "\\" + filename;
            cerr << "Trying executable directory path: " << fullPath << endl;
            inFile.open(fullPath);
            if (!inFile) {
                cerr << "Still could not open file at: " << fullPath << endl;
                return list;
            }
        }
        else {
            cerr << "Could not determine executable directory." << endl;
            return list;
        }
    }
	// Check for UTF-8 BOM (byte order mark) and skip if present
	// for interpreting provided file correctly
    char UTF_garbage[3] = { 0,0,0 };
    inFile.read(UTF_garbage, 3);
    if (inFile.gcount() == 3) {
        if (!(static_cast<unsigned char>(UTF_garbage[0]) == 0xEF &&
            static_cast<unsigned char>(UTF_garbage[1]) == 0xBB &&
            static_cast<unsigned char>(UTF_garbage[2]) == 0xBF)) {
            inFile.clear();
            inFile.seekg(0, ios::beg);
        }
    }
    else {
		// file shorter than should be for BOM, reset to start
        inFile.clear();
        inFile.seekg(0, ios::beg);
    }
	// Read passengers from file
    string name, surname;
	int index = 1; // start index from 1
    while (inFile >> name >> surname) {
        Passenger* p = new Passenger;
		p->index = index++; // assign and increment index
		p->name = name; //  assign name
		p->surname = surname; // assign surname
		list.push_back(p); // add to list
    }
	// Close file and return list
    inFile.close();
    return list;
}
// Function to print all passengers
void print_passengers(const vector<Passenger*>& passengers) {
    if (passengers.empty()) {
        cout << "Eror. The list is empty." << endl;
        return;
    }
    cout << "\nPassenger provided list (" << passengers.size() << " total):\n";
    cout << string(40, '-') << endl;
    for (auto p : passengers) {
        cout << setw(2) << p->index << ". " << p->name << " " << p->surname << endl;
    }
    cout << string(40, '-') << endl;
}
// Function to clear passengers and free memory
void clear_passengers(vector<Passenger*>& passengers) {
    for (auto p : passengers)
        delete p;
    passengers.clear();
}
// Function to search passengers by different keys (index, name, surname, full name)
void search_by_key(vector<Passenger*>& passengers) {
    if (passengers.empty()) {
        cout << "No passengers to search.\n";
        return;
    }
	// Menu for search options
    int choice = 0;
    while (true) {
	cout << "----------------------------------------------------\n";
    cout << "Please enter, how you want to find value:\n";
    cout << " 1) By Index\n";
    cout << " 2) By First name\n";
    cout << " 3) By Surname\n";
    cout << " 4) By Full name\n";
    cout << "----------------------------------------------------\n";

    if (!(cin >> choice) || choice < 1 || choice > 4) {
        cin.clear();
        cout << "Error in input\n";
    }
    else break;
    }
	// Perform search based on choice
    switch (choice) {
    case 1: {
        cout << "Please, enter index: ";
        int idx;
        if (!(cin >> idx)) {
            cin.clear();
            cout << "Invalid index.\n";
            return;
        }
        Passenger* found = nullptr;
        for (Passenger* p : passengers) {
            if (p->index == idx) { found = p; break; }
        }
        if (found) {
            cout << "Found: " << found->index << ". " << found->name << " " << found->surname << "\n";
        }
        else {
            cout << "No passenger with index " << idx << " found in provided list.\n";
        }
        cout << "----------------------------------------------------\n";
        break;
    }
    case 2: {
        cout << "Please, enter first name: ";
        string name;
        if (!(cin >> name)) { cout << "Invalid name.\n"; return; }
        vector<Passenger*> matches;
        for (Passenger* p : passengers) {
            if (p->name == name) matches.push_back(p);
        }
        if (matches.empty()) {
            cout << "No passengers with first name \"" << name << "\" found in provided list.\n";
        }
        else {
            cout << matches.size() << " match(es):\n";
            for (Passenger* p : matches)
                cout << p->index << ". " << p->name << " " << p->surname << "\n";
        }
        cout << "\n----------------------------------------------------\n";
        break;
    }
    case 3: {
        cout << "Please, enter surname: ";
        string surname;
        if (!(cin >> surname)) { cout << "Invalid surname.\n"; return; }
        vector<Passenger*> matches;
        for (Passenger* p : passengers) {
            if (p->surname == surname) matches.push_back(p);
        }
        if (matches.empty()) {
            cout << "No passengers with surname \"" << surname << "\" found in provided list.\n";
        }
        else {
            cout << matches.size() << " match(es):\n";
            for (Passenger* p : matches)
                cout << p->index << ". " << p->name << " " << p->surname << "\n";
        }
        cout << "\n----------------------------------------------------\n";
        break;
    }
    case 4: {
        cout << "Please, enter first name and surname separated by space: ";
        string name, surname;
        if (!(cin >> name >> surname)) { cout << "Invalid full name.\n"; return; }
        Passenger* found = nullptr;
        for (Passenger* p : passengers) {
            if (p->name == name && p->surname == surname) { found = p; break; }
        }
        if (found) {
            cout << "Found: " << found->index << ". " << found->name << " " << found->surname << "\n";
        }
        else {
            cout << "No passenger named \"" << name << " " << surname << "\" found in provided list.\n";
        }
        break;
    }
    default:
        cout << "Error. Choice is out of provided range.\n";
        cout << "\n----------------------------------------------------\n";
        break;
    }
}
// Function to add passenger to the end of the list
void add_to_the_end(vector<Passenger*>& passengers) {
    Passenger* p = new Passenger;
    cout << "----------------------------------------------------\n";
    cout << "Please, enter name: ";
    cin >> p->name;
    cout << "Please, enter surname: ";
    cin >> p->surname;
	// assign index
    p->index = passengers.empty() ? 1 : passengers.back()->index + 1;
    passengers.push_back(p);

    cout << "Passenger added at the end successfully.\n";
    cout << "----------------------------------------------------\n";
}
// Function to add passenger to the beginning of the list
void add_to_the_beginning(vector<Passenger*>& passengers) {
    Passenger* p = new Passenger;
    cout << "----------------------------------------------------\n";
    cout << "Please, enter name: ";
    cin >> p->name;
    cout << "Please, enter surname: ";
    cin >> p->surname;
	// insert at beginning
    passengers.insert(passengers.begin(), p);
	// update indixes
    for (size_t i = 0; i < passengers.size(); ++i)
        passengers[i]->index = static_cast<int>(i + 1);

    cout << "Passenger added at the beginning successfully.\n";
    cout << "----------------------------------------------------\n";
}
// Function to add passenger at specified position
void add_after_specified(vector<Passenger*>& passengers) {
    int posit;

    cout << "----------------------------------------------------\n";
    cout << "Please, enter position (1 to " << passengers.size() << "): ";
    cin >> posit;

    if (posit < 1 || posit > static_cast<int>(passengers.size())) {
        cout << "----------------------------------------------------\n";
        cout << "Error.\n";
        cout << "Don't contain this position in provided list.";
        cout << "----------------------------------------------------\n";
        return;
    }
	// create new passenger
    Passenger* p = new Passenger;
    cout << "Please, enter name: ";
    cin >> p->name;
    cout << "Please, enter surname: ";
    cin >> p->surname;
	// insert at after specified position
    passengers.insert(passengers.begin() + posit, p);
	// update indexes
    for (size_t i = 0; i < passengers.size(); ++i)
        passengers[i]->index = static_cast<int>(i + 1);

    cout << "Passenger added at the specified place successfully.\n";
    cout << "----------------------------------------------------\n";
}
// Function to delete passenger at specified position
void delete_specified(vector<Passenger*>& passengers) {
    int posit;
    while (true) {
        cout << "----------------------------------------------------\n";
        cout << "Please, enter position that you want to remove (1 to " << passengers.size() + 1 << "): ";
        cin >> posit;

        if (posit < 1 || posit > static_cast<int>(passengers.size()) + 1) {
            cout << "Error.\n";
            cout << "Don't contain this position in provided list.";
            return;
        }
        else {
            break;
        }
    }
    // delete element pointer to avoid leak
    delete passengers[posit - 1];
    passengers.erase(passengers.begin() + (posit - 1));
	// update indexes
    for (size_t i = 0; i < passengers.size(); ++i)
        passengers[i]->index = static_cast<int>(i + 1);

    cout << "Passenger deleted at the specified place successfully.\n";
    cout << "----------------------------------------------------\n";
}

// Evaluate algorithm on different numbers of elements by speed
void eval_speed() {
    cout << "----------------------------------------------------\n";
    cout << "Performance evaluation for lists of sizes: 50, 100, 1000, 5000\n";
    cout << "Speed test is shown in microseconds.\n";

    vector<int> siz = {50, 100, 1000, 5000};

    for (int n : siz) {
        cout << "\nTesting with " << n << " elements:\n";

        // Providing new objects in a list
        auto t0 = high_resolution_clock::now(); //register the start of perfomance of this function
        vector<Passenger*> v;
        v.reserve(n + 10);  // for avoiding repeated reallocations in memory
        for (int i = 1; i <= n; ++i) { //loop that run this function n times (50, 100, etc.)
            Passenger* p = new Passenger; // create new objects
            p->index = i; // provide index for new object
            p->name = "Name" + to_string(i);
            p->surname = "Surname" + to_string(i);
            v.push_back(p); // adding passenger to the list
        }
        auto t1 = high_resolution_clock::now(); // register the final time
        cout << "Providing new objects was held:" << duration_cast<microseconds>(t1 - t0).count() << "us\n";

        // insert new value at end
        auto t2 = high_resolution_clock::now(); // register the start time
        Passenger* p_end= new Passenger; // create new objects
        p_end->index = n + 1; // add new index for object
        p_end->name = "End_Name"; 
        p_end->surname = "End_Surname";
		v.push_back(p_end); // insert at end
        auto t3 = high_resolution_clock::now(); // register the final time
        cout << "Adding to the end new value was held: " << duration_cast<microseconds>(t3 - t2).count() << " us\n";

        // insert new value at beginning
        auto t4 = high_resolution_clock::now(); // start time
        Passenger* p_beg = new Passenger; // create new objects
		p_beg->index = 0; // add new index for object
		p_beg->name = "Beg_Name"; // add new name for object
		p_beg->surname = "Beg_Surname"; // add new surname for object
		v.insert(v.begin(), p_beg); // insert at beginning
		auto t5 = high_resolution_clock::now(); // end time
        cout << "Insert at beginning was held: " << duration_cast<microseconds>(t5 - t4).count() << " us\n";

        // insert at middle
        auto t6 = high_resolution_clock::now();
        Passenger* p_mid = new Passenger;
        p_mid->index = 0;
        p_mid->name = "Mid_Name";
        p_mid->surname = "Mid_Surname";
        v.insert(v.begin() + (v.size() / 2), p_mid);
        auto t7 = high_resolution_clock::now();
        cout << "Insert new value at middle was held: " << duration_cast<microseconds>(t7 - t6).count() << " us\n";

        // search by index
		int search_index = n / 2; // searching for middle index
		auto t8 = high_resolution_clock::now(); //  start time
		Passenger* found = nullptr; // pointer to found object by index
		for (Passenger* m : v) { // linear search
			if (m->index == search_index) { found = m; break; } // if found break the loop
        }
		auto t9 = high_resolution_clock::now(); // end time
        cout << "Linear search by index was held: " << duration_cast<microseconds>(t9 - t8).count() << " us";
        if (!found) cout << "Not found this object by your provided index";
        cout << "\n";

        // search by name
        string search_name = "Name" + to_string(search_index);
		auto t10 = high_resolution_clock::now(); // start time
		Passenger* found_name = nullptr; // pointer to found object by name
        for (Passenger* m : v) {
            if (m->name == search_name) { found_name = m; break; }
        }
		auto t11 = high_resolution_clock::now(); // end time
        cout << "Linear search by name was held: " << duration_cast<microseconds>(t11 - t10).count() << " us";
        if (!found_name) cout << "Not found this object by your provided index";
        cout << "\n";

		// remove at specific position - middle
        size_t mid_pos = v.size() / 2;
		auto t12 = high_resolution_clock::now(); // start time
		delete v[mid_pos]; // avoid memory leak
		v.erase(v.begin() + mid_pos); // remove at middle
		auto t13 = high_resolution_clock::now(); // end time
        cout << "Remove your value from the list was held: " << duration_cast<microseconds>(t13 - t12).count() << " us\n";

        // cleanup
        for (Passenger* m : v) delete m;
        v.clear();

        cout << "Test for " << n << " elements completed.\n";
        cout << "----------------------------------------------------\n";

    }

    cout << "\nPerformance evaluation by speed was finished.\n";
    cout << "----------------------------------------------------\n";
}
// Main part
int main() {

    // Start of the program
    cout << "----------------------------------------------------\n";
    cout << "Author: Jaroslavs Monastirskis\n";
    cout << "Course: Data Structures and Algorithms\n";
    cout << "Laboratory work 2: Linear Data Structures\n";
    cout << "----------------------------------------------------\n";
	// Load passengers from file
    vector<Passenger*> passengers;
	// Measure loading time
	auto start = high_resolution_clock::now(); // start time
    passengers = load_passengers("passengers.data");
	auto end = high_resolution_clock::now(); // end time
	// Show loading time
    cout << "Loading time: "
        << duration_cast<microseconds>(end - start).count()
        << " microseconds\n";
	// Menu loop
    int ch = 0;
    cout << "\n----------------------------------------------------\n";
    cout << "Welcome, to the Passenger Management System!\n";
    cout << "----------------------------------------------------\n";
    while (ch != 7) {
        cout << "Please, choose an option from the menu below:\n";
        cout << "1) Print all passengers\n";
        cout << "2) Search passenger by key\n";
        cout << "3) Add passenger to the end\n";
        cout << "4) Add passenger to the beginning\n";
        cout << "5) Add passenger at after specified position\n";
        cout << "6) Delete passenger at specified position\n";
        cout << "7) Evaluate algorithms performance (sizes: 50,100, 1000, 5000) and exit\n";
        cout << "----------------------------------------------------\n";
        cout << "Choose (1-7): ";
		// Get user choice
        if (!(cin >> ch)) {
            cin.clear();
            cout << "Invalid input\n";
            continue;
        }
		// Execute chosen option
        switch (ch) {
		case 1: print_passengers(passengers); break; // print all passengers
		case 2: search_by_key(passengers); break; // search by key
		case 3: add_to_the_end(passengers);  break; // add to the end
		case 4: add_to_the_beginning(passengers); break; // add to the beginning
		case 5: add_after_specified(passengers); break; // add at specified position
		case 6: delete_specified(passengers); break; // delete at specified position
		case 7:  // evaluate performance and exit
            eval_speed(); 
            clear_passengers(passengers);
            cout << "Exiting the program\n";
            return 0;
		default: cout << "Choice out of range.\n"; break; // invalid choice
        }
    }
	// Cleanup and exit
    clear_passengers(passengers);
    cout << "Exiting the program\n";
    return 0;
}