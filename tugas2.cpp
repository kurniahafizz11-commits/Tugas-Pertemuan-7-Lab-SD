#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>

using namespace std;

const int NUM_LOCATIONS = 6;
const int INF = INT_MAX;

int charToIdx(char c) { return c - 'A'; }
char idxToChar(int i) { return i + 'A'; }

// Fungsi pembantu untuk mencetak rute terpendek yang ditempuh
void printRoute(int currentVertex, const vector<int>& parent) {
    if (currentVertex == -1) return;
    printRoute(parent[currentVertex], parent);
    cout << idxToChar(currentVertex) << (parent[currentVertex] != -1 ? "" : "");
    if (currentVertex != -1) {
    }
}

// Fungsi bantu untuk mendapatkan vektor rute secara berurutan
vector<int> getRoute(int target, const vector<int>& parent) {
    vector<int> path;
    for (int v = target; v != -1; v = parent[v]) {
        path.push_back(v);
    }
    reverse(path.begin(), path.end());
    return path;
}

// Implementasi Algoritma Dijkstra
void dijkstra(const vector<vector<int>>& graph, int src, vector<int>& dist, vector<int>& parent) {
    vector<bool> sptSet(NUM_LOCATIONS, false);
    
    dist.assign(NUM_LOCATIONS, INF);
    parent.assign(NUM_LOCATIONS, -1);
    
    dist[src] = 0;
    
    for (int count = 0; count < NUM_LOCATIONS - 1; count++) {
        int u = -1, min_dist = INF;
        for (int v = 0; v < NUM_LOCATIONS; v++) {
            if (!sptSet[v] && dist[v] <= min_dist) {
                min_dist = dist[v];
                u = v;
            }
        }
        
        if (u == -1 || dist[u] == INF) break;
        
        sptSet[u] = true;
        
        for (int v = 0; v < NUM_LOCATIONS; v++) {
            if (!sptSet[v] && graph[u][v] && dist[u] != INF && dist[u] + graph[u][v] < dist[v]) {
                parent[v] = u;
                dist[v] = dist[u] + graph[u][v];
            }
        }
    }
}

int main() {
    vector<vector<int>> graph(NUM_LOCATIONS, vector<int>(NUM_LOCATIONS, 0));
    
    graph[charToIdx('A')][charToIdx('B')] = 4; graph[charToIdx('B')][charToIdx('A')] = 4;
    graph[charToIdx('A')][charToIdx('C')] = 2; graph[charToIdx('C')][charToIdx('A')] = 2;
    graph[charToIdx('B')][charToIdx('C')] = 1; graph[charToIdx('C')][charToIdx('B')] = 1;
    graph[charToIdx('B')][charToIdx('D')] = 5; graph[charToIdx('D')][charToIdx('B')] = 5;
    graph[charToIdx('B')][charToIdx('E')] = 3; graph[charToIdx('E')][charToIdx('B')] = 3;
    graph[charToIdx('C')][charToIdx('D')] = 8; graph[charToIdx('D')][charToIdx('C')] = 8;
    graph[charToIdx('C')][charToIdx('E')] = 6; graph[charToIdx('E')][charToIdx('C')] = 6;
    graph[charToIdx('D')][charToIdx('E')] = 2; graph[charToIdx('E')][charToIdx('D')] = 2;
    graph[charToIdx('D')][charToIdx('F')] = 4; graph[charToIdx('F')][charToIdx('D')] = 4;
    graph[charToIdx('E')][charToIdx('F')] = 3; graph[charToIdx('F')][charToIdx('E')] = 3;

    cout << "=== SISTEM NAVIGASI KOTA (DIJKSTRA) ===\n";
    
    // Rute Terpendek dari Lokasi A ke Semua Lokasi Lain
    vector<int> distA, parentA;
    dijkstra(graph, charToIdx('A'), distA, parentA);
    
    cout << "\n[1] Rute Terpendek dari Lokasi A ke semua lokasi lain:\n";
    for (int i = 0; i < NUM_LOCATIONS; i++) {
        if (i == charToIdx('A')) continue;
        
        cout << "Ke " << idxToChar(i) << " -> Jarak: " << distA[i] << " km | Rute: ";
        vector<int> route = getRoute(i, parentA);
        for (size_t j = 0; j < route.size(); j++) {
            cout << idxToChar(route[j]);
            if (j < route.size() - 1) cout << " -> ";
        }
        cout << endl;
    }
    
    // Rekomendasi Rute Berdasarkan Input Pengguna
    cout << "\n[2] Rekomendasi Rute Kustom\n";
    char start, target;
    cout << "Masukkan Lokasi Asal (A-F): ";
    cin >> start;
    cout << "Masukkan Lokasi Tujuan (A-F): ";
    cin >> target;
    
    start = toupper(start);
    target = toupper(target);
    
    int startIdx = charToIdx(start);
    int targetIdx = charToIdx(target);
    
    if (startIdx >= 0 && startIdx < NUM_LOCATIONS && targetIdx >= 0 && targetIdx < NUM_LOCATIONS) {
        vector<int> customDist, customParent;
        dijkstra(graph, startIdx, customDist, customParent);
        
        if (customDist[targetIdx] == INF) {
            cout << "Tidak ada rute yang menghubungkan lokasi " << start << " dan " << target << ".\n";
        } else {
            cout << "\n--- REKOMENDASI RUTE TERCEPAT ---\n";
            cout << "Asal : " << start << endl;
            cout << "Tujuan : " << target << endl;
            cout << "Total Jarak : " << customDist[targetIdx] << " km\n";
            cout << "Rute : ";
            vector<int> route = getRoute(targetIdx, customParent);
            for (size_t j = 0; j < route.size(); j++) {
                cout << idxToChar(route[j]);
                if (j < route.size() - 1) cout << " -> ";
            }
            cout << endl;
        }
    } else {
        cout << "Lokasi input tidak valid! Gunakan huruf A sampai F.\n";
    }
    
    return 0;
}
