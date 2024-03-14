#include<iostream>
#include<vector>
#include<cmath>

using namespace std;

void printMatrix(vector<vector<int>> matrix) {
    int n = matrix.size();
    int m = matrix[0].size();
    for (int i=0; i<n; i++) {
        for (int j =0; j<m; j++) {
            cout << matrix[i][j] << "\t";
        }
        cout << "\n";
    }
}

vector<vector<int>> eraseRowCol(vector<vector<int>> matrix, int row, int col) {
    int n = matrix.size();
    for (int i =0; i<n; i++) {
        matrix[i].erase(matrix[i].begin()+col);
    }
    matrix.erase(matrix.begin()+row);
    return matrix;
}

int wyznacznikMac(vector<vector<int>> matrix) {
    int n = matrix.size();
    if (n==1) {
        return matrix[0][0];
    }
    int sum = 0;
    int i = 0;
    // for (int i=0; i< n; i++) {
        for (int j =0; j<n; j++) {
            sum += pow(-1, (i+j))*matrix[i][j]*wyznacznikMac(eraseRowCol(matrix, i,j));
        }
    // }
    return sum;
}

vector<vector<int>> matrixTransposition(vector<vector<int>> matrix) {
    int n = matrix.size();
    int m = matrix[0].size();
    vector<vector<int>> matrixT;

    for (int j = 0; j<m; j++) {
        // By columns
        vector<int> row;
        for (int i = 0; i<n; i++) {
            // By rows
            row.push_back(matrix[i][j]);
        }
        matrixT.push_back(row);
    }
    return matrixT;
}

int main() {
    vector<vector<int>> matrix1 = {{1, 3, 7, 2}, {3, 2, -6, 1}, {1, -1, -1, 2}, {3, 8, 5, -4}};

    // cout << "Wyznacznik macierzy 1: " << wyznacznikMac(matrix1) << "\n";

    cout << "Original matrix:\n";
    printMatrix(matrix1);
    cout << "Matrix after transposition:\n";
    printMatrix(matrixTransposition(matrix1));
    
}