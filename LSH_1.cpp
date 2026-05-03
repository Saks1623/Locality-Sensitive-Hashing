#include <iostream>
#include <bits/stdc++.h>
using namespace std;

//dataset generation

vector<vector<int>> generate_binary_vectors(int n, int d) {
    vector<vector<int>> X(n, vector<int>(d));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < d; j++) {
            X[i][j] = rand() % 2;
        }
    }
    return X;
}

//hash family generation

vector<vector<int>> generate_hash_family(int d, int k, int num_hashes) {
    vector<vector<int>> hash_family;

    for (int i = 0; i < num_hashes; i++) {
        vector<int> indices;
        unordered_set<int> used;

        while ((int)indices.size() < k) {
            int idx = rand() % d;
            if (used.find(idx) == used.end()) {
                indices.push_back(idx);
                used.insert(idx);
            }
        }
        hash_family.push_back(indices);
    }

    return hash_family;
}

string hash_function(const vector<int>& x, const vector<int>& indices) {   //hashfunction
    string h = "";
    for (int i : indices) {
        h += (x[i] ? '1' : '0');
    }
    return h;
}

//hash table creation

vector<pair<vector<int>, unordered_map<string, vector<vector<int>>>>>
build_hash_tables(const vector<vector<int>>& X,
                  const vector<vector<int>>& hash_family) {

    vector<pair<vector<int>, unordered_map<string, vector<vector<int>>>>> hash_tables;

    for (auto& indices : hash_family) {
        unordered_map<string, vector<vector<int>>> table;

        for (auto& x : X) {
            string h = hash_function(x, indices);
            table[h].push_back(x);
        }

        hash_tables.push_back({indices, table});
    }

    return hash_tables;
}


int hamming_distance(const vector<int>& a, const vector<int>& b) {  //hamming distance b/w two vectors
    int dist = 0;
    for (int i = 0; i < a.size(); i++) {
        if (a[i] != b[i]) dist++;
    }
    return dist;
}

//comparision with query

vector<int> query(const vector<int>& q,
    vector<pair<vector<int>, unordered_map<string, vector<vector<int>>>>>& hash_tables) {

    
    int idx = rand() % hash_tables.size();
    auto& [indices, table] = hash_tables[idx];

    
    string hq = hash_function(q, indices);

    
    if (table.find(hq) == table.end() || table[hq].empty()) {
        return {}; 
    }

    vector<vector<int>>& candidates = table[hq];

    
    vector<int> best = candidates[0];
    int best_dist = hamming_distance(best, q);

    for (auto& x : candidates) {      //checking similarity with the candidates
        int dist = hamming_distance(x, q);
        if (dist < best_dist) {
            best_dist = dist;
            best = x;
        }
    }

    return best;
}


void print_vector(const vector<int>& v) {
    for (int x : v) cout << x << " ";
    cout << endl;
}

int main() {
    srand(time(0));

    int n = 100;  
    int d = 20;   
    int k = 5;    
    int L = 10;   


    vector<vector<int>> X = generate_binary_vectors(n, d);


    vector<vector<int>> H = generate_hash_family(d, k, L);


    auto hash_tables = build_hash_tables(X, H);


    vector<int> q(d);
    for (int i = 0; i < d; i++) q[i] = rand() % 2;   //random query generation


    vector<int> nn = query(q, hash_tables);

    cout << "Query: ";
    print_vector(q);

    cout << "Nearest Neighbor (approx): ";
    if (nn.empty()) cout << "None found\n";
    else print_vector(nn);

    return 0;
}