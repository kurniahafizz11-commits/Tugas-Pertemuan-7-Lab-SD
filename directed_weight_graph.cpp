#include <iostream>
#include <vector>
using namespace std;


class Graph {
    private:
        int numberVertex;
        vector<vector<int>> adjMatrix;

    public:
        Graph(int banyakTitik) {
            numberVertex = banyakTitik;
            adjMatrix.resize(numberVertex, vector<int>(numberVertex, 0));
    }

    // fungsi untuk menghubungkan tiap titik
    void addEdge(int i, int j, int weight) {
        if (i >= 0 && i < numberVertex && j >= 0 && j < numberVertex) {
            adjMatrix[i][j] = weight;
            // adjMatrix[j][i] = weight; //  1 arah 
        } else {
            cout << "Index nonvalid" << endl;
        }
    }

    void printAdjMatrix() {
        for (int i = 0; i < numberVertex; i++) {
            for (int j = 0; j < numberVertex; j++) {
                cout << adjMatrix[i][j] << " ";
            }
            cout << endl;
        }
    }

};

int main() {
    Graph graphh(5); //0, 1, 2, 3, 4

    graphh.addEdge(0, 1, 5);
    graphh.addEdge(0, 2, 3);   
    graphh.addEdge(1, 3, 4);  
    graphh.addEdge(1, 4, 7);  
    graphh.addEdge(2, 3, 2);  
    graphh.addEdge(3, 4, 8);  
    graphh.printAdjMatrix();
}