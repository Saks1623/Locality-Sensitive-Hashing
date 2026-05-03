#include <iostream>
#include <bits/stdc++.h>
using namespace std;

// Generation of data points
vector<vector<double>> generate_vectors(int n, int d) {
    vector<vector<double>> X(n, vector<double>(d));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < d; j++) {
            X[i][j] = ((double)rand() / RAND_MAX) * 2 - 1; // [-1,1]
        }
    }
    return X;
}

//Generating hash family

vector<vector<double>> generate_hash_family(int d, int L) {
    vector<vector<double>> H;

    for (int i = 0; i < L; i++) {
        vector<double> a(d);
        for (int j = 0; j < d; j++) {
            a[j] = ((double)rand() / RAND_MAX) * 2 - 1;
        }
        H.push_back(a);
    }

    return H;
}


double dot_product(const vector<double>& a, const vector<double>& b) {     //dot product
    double res = 0;
    for (int i = 0; i < a.size(); i++) {
        res += a[i] * b[i];
    }
    return res;
}


string hash_function(const vector<double>& x,
                     const vector<vector<double>>& H) {        //hash function

    string h = "";

    for (auto& a : H) {
        double dp = dot_product(a, x);
        h += (dp >= 0 ? '1' : '0');   
    }

    return h;
}

//hash table 

unordered_map<string, vector<vector<double>>> build_hash_table(const vector<vector<double>>& X,
                 const vector<vector<double>>& H) {

    unordered_map<string, vector<vector<double>>> table;

    for (auto& x : X) {
        string h = hash_function(x, H);
        table[h].push_back(x);
    }

    return table;
}

// cosine distance (to compute similarity)

double cosine_similarity(const vector<double>& a, const vector<double>& b) {
    double dot = 0, normA = 0, normB = 0;

    for (int i = 0; i < a.size(); i++) {
        dot += a[i] * b[i];
        normA += a[i] * a[i];
        normB += b[i] * b[i];
    }

    return dot / (sqrt(normA) * sqrt(normB));
}

//comparision with query

vector<double> query(const vector<double>& q,
                     unordered_map<string, vector<vector<double>>>& table,
                     const vector<vector<double>>& H) {

    string hq = hash_function(q, H);
    

    if (table.find(hq) == table.end()) return {};

    auto& candidates = table[hq];

    vector<double> best = candidates[0];
    double best_sim = cosine_similarity(best, q);

    for (auto& x : candidates) {
        double sim = cosine_similarity(x, q);
        if (sim > best_sim) {   //checking similarity with candidates
            best_sim = sim;
            best = x;
        }
    }

    return best;
}

// -------------------------------
// Main (same)
// -------------------------------
int main() {
    srand(time(0));

    int n = 100;
    int d = 10;
    int L = 10;

    auto X = generate_vectors(n, d);
    auto H = generate_hash_family(d, L);

    auto table = build_hash_table(X, H);

    vector<double> q(d);
    for (int i = 0; i < d; i++) {      //generating query for Real numbers
        q[i] = ((double)rand() / RAND_MAX) * 2 - 1;
    }
    
    //vector<double> q = {0.1,0.1,0.1,0.1,0.1,0.1,0.1,0.1,0.1,0.1};
    
    auto nn = query(q, table, H);
    

    cout << "Query: ";
    for (double v : q) cout << v << " ";
    cout << endl;

    cout << "Nearest Neighbor (cosine approx): ";
    if (nn.empty()) {
      cout << "No neighbor found (empty bucket)\n";
    }
    else{
      for (double v : nn) cout << v << " ";
      cout << endl;
    }
    
    

    return 0;
}