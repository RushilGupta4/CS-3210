#include <iostream>
#include <fstream>
#include <vector>
#include <utility>
#include <algorithm>
using namespace std;

long long T = 0;

vector<pair<int,int>> read_input(const string &filename) {
    ifstream fin(filename);
    int n;
    fin >> n; 

    vector<pair<int,int>> points(n);
    for (int i = 0; i < n; i++) {
        int x, y;
        fin >> x >> y;
        points[i] = {x, y};
    }
    return points;
}

// Comparator to sort points by descending x; if x is equal, then by descending y.
bool cmp(const pair<int,int>& a, const pair<int,int>& b) {
    T += 2; // There are always 2 comparisions
    if (a.first != b.first) return a.first > b.first;
    else return a.second > b.second;
}

// Returns the smallest index i such that tops[i] < y. If none, returns tops.size().
int binary_search(const vector<int>& tops, int y) {
    int low = 0; 
    int high = tops.size(); 

    while (low < high) {
        T++; // loop condition

        int mid = (low + high) / 2;
        T++;

        T++; // comparison tops[mid] < y
        T++; // Assigning high or low
        if (tops[mid] < y) high = mid;
        else low = mid + 1;
    }
    return low;
}

vector<vector<pair<int,int>>> find_layers(const vector<pair<int,int>>& points) {
    vector<pair<int,int>> sorted_points = points;
    sort(sorted_points.begin(), sorted_points.end(), cmp); // Sort points by descending x, ys
    
    vector<vector<pair<int,int>>> layers; // Stores the layers
    vector<int> tops; // Stores the maximum y-value of each layer

    for (int i = 0; i < (int)sorted_points.size(); i++) {
        pair<int,int> p = sorted_points[i];
        int j = binary_search(tops, p.second); // Find the index of the layer that p belongs to

        T++; // comparison: i == tops.size()
        if (j == (int)tops.size()) {
            // Assert: p does not belong to any existing layer
            tops.push_back(p.second);
            layers.push_back(vector<pair<int,int>>());
            layers.back().push_back(p);
        } else {
            // Assert: p belongs to layer j
            tops[j] = p.second;
            layers[j].push_back(p);
        }
    }
    return layers;
}

void write_output(const string &filename, const vector<vector<pair<int,int>>>& layers) {
    ofstream fout(filename);
    for (int i = 0; i < (int)layers.size(); i++) {
        vector<pair<int,int>> layer = layers[i];
        for (int j = 0; j < (int)layer.size(); j++) {
            pair<int,int> p = layer[j];
            fout << p.first << " " << p.second << "\n";
        }
        fout << "\n";
    }
}

int main() {
    vector<pair<int,int>> points = read_input("input.txt");
    vector<vector<pair<int,int>>> layers = find_layers(points);
    write_output("output.txt", layers);
    
    ofstream foutT("T.txt");
    foutT << T;
    foutT.close();
    
    return 0;
}