#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

float zad1Euklides(vector<int> v1) {
    int n = v1.size();
    float euklides = 0;
    for (int i=0; i<n; i++) {
        euklides += v1[i]*v1[i];
    }
    return sqrt(euklides);
}

float zad1Manhattan(vector<int> v1) {
    int n = v1.size();
    float manhattan = 0;
    for (int i=0; i<n; i++) {
        manhattan += abs(v1[i]);
    }
    return manhattan;
}

float zad1Maximum(vector<int> v1) {
    int n = v1.size();
    float maximum = v1[0];
    for (int i=0; i<n; i++) {
        int curr = abs(v1[i]);
        if (curr > maximum) {
            maximum = curr;
        }
    }
    return maximum;

}

float zad2Euklides(vector<float> p1, vector<float> p2) {
    return sqrt(pow(p1[0]-p2[0], 2) + pow(p1[1]-p2[1], 2));
}

float zad2Manhattan(vector<float> p1, vector<float> p2) {
    return abs(p1[0]-p2[0]) + abs(p1[1]-p2[1]);
}

float zad2Maximum(vector<float> p1, vector<float> p2) {
    float d1 = abs(p1[0]-p2[0]);
    float d2 = abs(p1[1]-p2[1]);

    if (d1 > d2) {
        return d1;
    } else {
        return d2;
    }
}

// Metryka rzeki
// d = deukl(p,q) dla p i q na tej samej prostej prostopadłej do ox
// d = deukl(p, c1) + deukl(c1, c2) + deukl (c2, q) w pozostałych przypadkach
float zad2River(vector<float> p1, vector<float> p2) {
    if (p1[0] == p2[0]) {
        return zad2Euklides(p1, p2);
    } else {
        vector<float> c1 = {p1[0], 0};
        vector<float> c2 = {p2[0], 0};
        return zad2Euklides(p1, c1) + zad2Euklides(c1, c2) + zad2Euklides(c2, p2);
    }
}

// Metryka kolejowa
// d = deukl(p, q) jeśli są współliniowe
// d = deukl(p, o) + deukl(o, q)
float zad2Railway(vector<float> p1, vector<float> p2) {
    // x1*y2 - y1*x2 = 0 to współliniowe
    vector<float> o = {0,0};
    if ((p1[0]*p2[1]-p1[1]*p2[0]) == 0) {
        return zad2Euklides(p1, p2);
    } else {
        return zad2Euklides(p1, o) + zad2Euklides(o, p2);
    }
}

float zad3Frobeinus(int** matrix, int n, int m) {
    // sumi(sumj)
    float sum = 0;
    for (int i=0; i<n; i++) {
        float sumi = 0;
        for (int j=0; j<m; j++) {
            sumi += pow(matrix[i][j],2);
        }
        sum += sumi;
    }
    return sqrt(sum);
}

float zad3Manhattan(int** matrix, int n, int m) {
    float sum = 0;
    for (int i=0; i<n; i++) {
        float sumi = 0;
        for (int j=0; j<m; j++) {
            sumi += abs(matrix[i][j]);
        }
        sum += sumi;
    }
    return sum;
}

float zad3Maximum(int** matrix, int n, int m){
    float maximum = matrix[0][0];
    for (int i=0; i<n; i++) {
        for (int j=0; j<m; j++) {
            float curr = abs(matrix[i][j]);
            if (curr > maximum) {
                maximum = curr;
            }
        }
    }
    return maximum;
}

vector<vector<float>> matrixMultiplying(vector<vector<float>> matrix1, int n1, int m1, vector<vector<float>> matrix2, int n2, int m2) {
    vector<vector<float>> output;
    if(n1 != m2) {
        cout << "These matrixes cannot be multiplyed\n";
        output = {{0,0},{0,0}};
        return output;
    }
    for (int i=0; i<n1; i++) {
        for (int j=0; j<m2; j++) {
            for(int k=0; k<m1; k++) {
                output[i][j] += matrix1[i][j] + matrix2[k][j];
            }
        }
    }
    return output;
}

int main() {
    // Zad1
    vector<int> v1 = {1, 1};
    cout << "Euklides:" << zad1Euklides(v1) << "\n";
    cout << "Manhattan: " << zad1Manhattan(v1) << "\n";
    cout << "maximum: " << zad1Maximum(v1) << "\n";

    // Zad2
    vector<float> p1 = {1, 1};
    vector<float> p2 = {3, 2};
    cout << "\nDistances:\n";
    cout << "Euklides:" << zad2Euklides(p1, p2) << "\n";
    cout << "Manhattan: " << zad2Manhattan(p1, p2) << "\n";
    cout << "Maximum: " << zad2Maximum(p1, p2) << "\n";
    cout << "River: " << zad2River(p1, p2) << "\n";
    cout << "Railway: " << zad2Railway(p1, p2) << "\n";

    // Zad3
    vector<vector<float>> matrix1 = {{1,1,1},{1,1,1},{1,1,1}, {1,1,1}};
    vector<vector<float>> matrix2 = {{1,1,1,1}, {1,1,1,1}, {1,1,1,1}};
    cout << "\nMatrix multiplying:\n";
    vector<vector<float>> result = matrixMultiplying(matrix1, 3, 4, matrix2, 4, 3);
    cout << result[0][0] << "\n";

    return 0;
}