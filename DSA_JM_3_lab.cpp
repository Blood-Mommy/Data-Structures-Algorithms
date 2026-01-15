#include <iostream>
#include <vector>
#include <queue>
#include <chrono>
using namespace std;

// incidence list
vector<vector<int>> inc_list = {
    {1,5},           //0
    {0,5},           //1
    {3,7},           //2 
    {2},             //3 
    {5,9},           //4 
    {0,1,4,6,10},    //5 
    {5,9,11},        //6 
    {2,10,11},       //7 
    {9},             //8 
    {4,6,8},         //9 
    {5,7},           //10 
    {6,7}            //11 
};

void graph_repr() {

    //incidence list representation
    auto start_inc_list = chrono::high_resolution_clock::now();

    cout << "\nIncidence list:\n";

    for (int i = 0; i < inc_list.size(); i++) {
        cout << i << ": ";
        for (int j = 0; j < inc_list[i].size(); j++) {
            cout << inc_list[i][j];
            if (j + 1 < inc_list[i].size()) cout << " -> ";
        }
        cout << "\n";
    }

    auto end_inc_list = chrono::high_resolution_clock::now();
    auto time_inc_list = chrono::duration_cast<chrono::microseconds>(end_inc_list - start_inc_list).count();
    cout << "Incidence list function perfomance: " << time_inc_list << " ms\n";
    cout << "--------------------------------------\n";

    // adjacency matrix representation
    auto start_adj_matrix = chrono::high_resolution_clock::now();

    cout << "Adjacency matrix:\n";

    for (int i = 0; i < 12; i++) {
        cout << i << ":  ";
        vector<int> row(12, 0);
        for (int v : inc_list[i]) row[v] = 1;
        for (int j = 0; j < 12; j++)
            cout << row[j] << " ";
        cout << "\n";
    }
    auto end_adj_matrix = chrono::high_resolution_clock::now();
    auto time_adj_matrix = chrono::duration_cast<chrono::microseconds>(end_adj_matrix - start_adj_matrix).count();
    cout << "Adjacency matrix function perfomance: " << time_adj_matrix << " ms\n";
    cout << "--------------------------------------\n";
}

// traversal graph by width
vector<int> bfs(int start) {

    vector<int> vis(12, 0);
    queue<int> q;
    vector<int> order;

    vis[start] = true;
    q.push(start);

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        order.push_back(u);

        for (int x : inc_list[u]) {
            if (!vis[x]) {
                vis[x] = true;
                q.push(x);
            }
        }
    }

    return order;
}
//main part
int main() {
    string full_name;

    cout << "Laboratory work 3: Recursive Data Structure: Graph\n"
        << "Variant: 14"
        << "Author: Jaroslavs Monastirskis\n\n";
    // call function for representing data structures
    cout << "Your provided data structures: \n";
    graph_repr();

    // bfs
    cout << "Traverse the graph by width: \n";

    auto start_bfs = chrono::high_resolution_clock::now();

    vector<int> order = bfs(0);

    auto end_bfs = chrono::high_resolution_clock::now();
    auto time_bfs = chrono::duration_cast<chrono::microseconds>(end_bfs - start_bfs).count();

    for (int x : order) cout << x << " ";
    cout << "\n";

    cout << "BFS function perfomance: " << time_bfs << " ms\n";
    cout << "--------------------------------------------------\n";

    // Input 12-letter name
    while (full_name.length() != 12) {
        cout << "Please, write your name and surname without spaces (exactly 12 letters): ";
        cin >> full_name;
    }

    // Convert the string to the array
    vector<string> letters(12);
    for (int i = 0; i < 12; i++)
        letters[i] = string(1, full_name[i]);

    // Traversal before rearrangement
    cout << "\nTraversal of your full_name: \n";
    auto start_trav = chrono::high_resolution_clock::now();
    for (int x : order) cout << letters[x];
    auto end_trav = chrono::high_resolution_clock::now();

    auto time_trav = chrono::duration_cast<chrono::microseconds>(end_trav - start_trav).count();

    cout << "\n";
    cout << "Traversal function perofamnce: " << time_trav << " ms\n";
    cout << "--------------------------------------------------\n";

    // Rearrangement
    string rearranged;
    while (rearranged.length() != 12) {
        cout << "\nRearrange letters into readable form (enter new 12-letter string): ";
        cin >> rearranged;
    }

    for (int i = 0; i < 12; i++)
        letters[i] = string(1, rearranged[i]);

    // traversal after the second input
    cout << "\nTraversal graph with new sequence: ";
    auto start_trav_last = chrono::high_resolution_clock::now();
    for (int x : order) cout << letters[x];
    cout << "\n";

    auto end_trav_last = chrono::high_resolution_clock::now();
    auto time_trav_last = chrono::duration_cast<chrono::microseconds>(end_trav_last - start_trav_last).count();
    cout << "Traversal function perofamnce: " << time_trav_last << " ms\n";
    cout << "--------------------------------------------------\n";

    return 0;
}
