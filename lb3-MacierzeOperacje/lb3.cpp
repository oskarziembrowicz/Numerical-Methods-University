#include<iostream>
#include<vector>
#include<cmath>

using namespace std;

void printMatrix(vector<vector<double>> matrix) {
    int n = matrix.size();
    int m = matrix[0].size();
    for (int i=0; i<n; i++) {
        for (int j =0; j<m; j++) {
            cout << matrix[i][j] << "\t";
        }
        cout << "\n";
    }
}

vector<vector<double>> eraseRowCol(vector<vector<double>> matrix, int row, int col) {
    int n = matrix.size();
    for (int i =0; i<n; i++) {
        matrix[i].erase(matrix[i].begin()+col);
    }
    matrix.erase(matrix.begin()+row);
    return matrix;
}

int wyznacznikMac(vector<vector<double>> matrix) {
    int n = matrix.size();
    if (n==1) {
        return matrix[0][0];
    }
    int sum = 0;
    // int i = 0;
    for (int i=0; i< n; i++) {
        for (int j =0; j<n; j++) {
            sum += pow(-1, (i+j))*matrix[i][j]*wyznacznikMac(eraseRowCol(matrix, i,j));
        }
    }
    return sum;
}

vector<vector<double>> matrixTransposition(vector<vector<double>> matrix) {
    int n = matrix.size();
    int m = matrix[0].size();
    vector<vector<double>> matrixT;

    for (int j = 0; j<m; j++) {
        // By columns
        vector<double> row;
        for (int i = 0; i<n; i++) {
            // By rows
            row.push_back(matrix[i][j]);
        }
        matrixT.push_back(row);
    }
    return matrixT;
}

vector<vector<double>> invertMatrix(vector<vector<double>> matrix) {
    int n = matrix.size();
    int m = matrix[0].size();
    vector<vector<double>> resultMatrix;

    int var = wyznacznikMac(matrix);
    // int var = 240;
    if (var == 0) {
        return {};
    }

    cout << "Wyznacznik: " << var << "\n";
    
    for (int i=0; i<n; i++) {
        vector<double> row;
        for (int j = 0; j<m; j++) {
            row.push_back((pow(-1, i+j) * wyznacznikMac(eraseRowCol(matrix, i, j)))/var);
        }
        resultMatrix.push_back(row);
    }

    return matrixTransposition(resultMatrix);
}

vector<vector<double>> multiplyMatrices(const vector<vector<double>>& matrix1, const vector<vector<double>>& matrix2) {
    int rows1 = matrix1.size();
    int cols1 = matrix1[0].size();
    int cols2 = matrix2[0].size();

    vector<vector<double>> result(rows1, vector<double>(cols2, 0));

    for (int i = 0; i < rows1; ++i) {
        for (int j = 0; j < cols2; ++j) {
            for (int k = 0; k < cols1; ++k) {
                result[i][j] += matrix1[i][k] * matrix2[k][j];
            }
        }
    }

    return result;
}

// Ax=b
// x = A^(-1) * b

vector<vector<double>> calculatingX(vector<vector<double>> matrixA, vector<vector<double>> B) {
    return multiplyMatrices(invertMatrix(matrixA), B);
}

// Ax=b
// LUx = b
// Ly = b
// Ux=y

vector<vector<double>> gaussU(vector<vector<double>> matrix) {
    int n = matrix.size();
    int m = matrix[0].size();

    for (int i=1; i<n; i++) {
        // Times to do
        for (int j=i; j<n; j++) {
            // Rows
            for (int k=i-1; k<m; k++) {
                // Cols
                matrix[j][k] = matrix[j][k] - (matrix[i-1][k]*(matrix[j][i-1]/matrix[i-1][i-1]));
            }
        }
    }

    return matrix;
}

int main() {
    // vector<vector<double>> matrix1 = {{1, 3, 7, 2}, {3, 2, -6, 1}, {1, -1, -1, 2}, {3, 8, 5, -4}};

    // printMatrix(multiplyMatrices(invertMatrix(matrix1), matrix1));

    // cout << "Wyznacznik macierzy 1: " << wyznacznikMac(matrix1) << "\n";

    // cout << "Original matrix:\n";
    // printMatrix(matrix1);

    // cout << "Matrix after transposition:\n";
    // printMatrix(matrixTransposition(matrix1));

    // cout << "Matrix after inverting:\n";
    // printMatrix(invertMatrix(matrix1));

    vector<vector<double>> matrixA = {{1, 2, 1},{3, -7, 2},{2, 4, 5}};
    vector<vector<double>> matrixB = {{-9},{61},{-9}};

    printMatrix(gaussU(matrixA));
    // printMatrix(calculatingX(matrixA, matrixB));
    
}