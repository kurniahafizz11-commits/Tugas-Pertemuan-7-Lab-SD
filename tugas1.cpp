#include <iostream>
#include <vector>
#include <queue>

using namespace std;

const int NUM_VERTICES = 6;

// Fungsi untuk mengubah karakter 'A'-'F' menjadi indeks 0-5
int charToIndex(char c) {
    return c - 'A';
}

// Fungsi untuk mengubah indeks 0-5 menjadi karakter 'A'-'F'
char indexToChar(int i) {
    return i + 'A';
}

int main() {
    // Inisialisasi Adjacency Matrix dengan 0
    vector<vector<int>> adjMatrix(NUM_VERTICES, vector<int>(NUM_VERTICES, 0));
    
    int numEdges;
    cout << "=== PROGRAM GRAF BFS (A-F) ===\n";
    cout << "Masukkan jumlah edge yang ingin diinput: ";
    cin >> numEdges;
    
    cout << "Masukkan edge (contoh: A B atau C D):\n";
    for (int i = 0; i < numEdges; i++) {
        char u, v;
        cout << "Edge " << i + 1 << ": ";
        cin >> u >> v;
        
        // Mengubah input ke huruf kapital jika pengguna memasukkan huruf kecil
        u = toupper(u);
        v = toupper(v);
        
        int idxU = charToIndex(u);
        int idxV = charToIndex(v);
        
        // Validasi input vertex
        if (idxU >= 0 && idxU < NUM_VERTICES && idxV >= 0 && idxV < NUM_VERTICES) {
            adjMatrix[idxU][idxV] = 1;
            adjMatrix[idxV][idxU] = 1; // Karena graf tidak berarah
        } else {
            cout << "Input tidak valid! Pastikan simpul berada di rentang A-F.\n";
            i--; // Ulangi input untuk indeks ini
        }
    }
    
    // Meminta vertex awal untuk BFS
    char startVertex;
    cout << "\nMasukkan vertex awal untuk BFS (A-F): ";
    cin >> startVertex;
    startVertex = toupper(startVertex);
    
    int startIdx = charToIndex(startVertex);
    if (startIdx < 0 || startIdx >= NUM_VERTICES) {
        cout << "Vertex awal tidak valid!\n";
        return 1;
    }
    
    // Algoritma BFS
    vector<bool> visited(NUM_VERTICES, false);
    queue<int> q;
    
    visited[startIdx] = true;
    q.push(startIdx);
    
    cout << "Urutan vertex yang dikunjungi (BFS): ";
    while (!q.empty()) {
        int curr = q.front();
        q.pop();
        
        cout << indexToChar(curr) << " ";
        
        for (int i = 0; i < NUM_VERTICES; i++) {
            if (adjMatrix[curr][i] == 1 && !visited[i]) {
                visited[i] = true;
                q.push(i);
            }
        }
    }
    cout << endl;
    
    return 0;
}
