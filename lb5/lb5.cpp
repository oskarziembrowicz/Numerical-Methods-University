#include<iostream>
#include<vector>
#include<cmath>

using namespace std;

double maximum(vector<double> v1) {
    int n = v1.size();
    double maximum = v1[0];
    for (int i=0; i<n; i++) {
        double curr = abs(v1[i]);
        if (curr > maximum) {
            maximum = curr;
        }
    }
    return maximum;
}

vector<double> subtractVectors(vector<double> v1, vector<double>v2) {
    int n = v1.size();
    vector<double> result(n, 0);
    for (int i=0; i<n; i++){
        result[i] = v1[i] - v2[i];
    }
    return result;
}

// Metoda Jacobiego
// Xi = (bi - Sum(for j=1; j<n)(aij*xj^(k-1)))/aii
// k - number of iter
// n - matrix size
// A - matrix 2D
// b - matrix 1D
// x = matrix 1D

// Przykład:
/*
4x1 - 2x2 = 0
-2x1 + 5x2 - x3 = 2
-x2 + 4x3 + 2x4 = 3
2x3 + 3x4 = -2

A:
4 -2 0 0
-2 5 -1 0
0 -1 4 2
0 0 2 3

b:
0
2
3
-2

x:
0.5
1
2
-2
*/

vector<double> jacobiMethod(vector<vector<double>> A, vector<double> B, int number_of_iter) {
    int n = B.size();
    vector<double> X(n, 0);
    vector<double> Xnew(n, 0);

    // for (int k=0; k<number_of_iter; k++) {
    //     for (int i=0; i<n; i++) {
    //         double sum = 0;
    //         for (int j=0; j<n; j++) {
    //             if (j == i) {
    //                 continue;
    //             }
    //             sum += A[i][j]*X[j];
    //         }
    //         Xnew[i] = ((B[i] - sum)/A[i][i]);
    //     }
    //     for(int i=0; i<n; i++) {
    //         X[i]=Xnew[i];
    //     }
    // }

    double e = pow(10, -8);
    double diff = 1;
    int counter = 0;

    while (diff > e) {
        for (int i=0; i<n; i++) {
            double sum = 0;
            for (int j=0; j<n; j++) {
                if (j == i) {
                    continue;
                }
                sum += A[i][j]*X[j];
            }
            Xnew[i] = ((B[i] - sum)/A[i][i]);
        }

        diff = maximum(subtractVectors(Xnew, X))/maximum(Xnew);

        for(int i=0; i<n; i++) {
            X[i]=Xnew[i];
        }
        counter++;
    }

    cout << "Iterations in Jacobi: " << counter << "\n\n";

    return X;
}

bool zeroInDiagon(vector<vector<double>> v) {
    int n = v.size();
    for (int i=0; i<n; i++) {
        if (v[i][i] == 0) {
            return true;
        }
    }
    return false;
}

bool maxLowerThanOne(vector<vector<double>> v) {
    int n = v.size();
    int m = v[0].size();
}

vector<double> gaussSeidlMethod(vector<vector<double>> A, vector<double> B, int number_of_iter) {

    // Check conditions
    

    int n = B.size();
    vector<double> X(n, 0);
    vector<double> Xnew(n, 0);

    for (int k=0; k<number_of_iter; k++) {
        for (int i=0; i<n; i++) {
            double sum1 = 0;
            double sum2 = 0;
            for (int j=0; j<i; j++) {
                sum1 += A[i][j]*Xnew[j];
            }
            for (int j=i+1; j<n; j++) {
                sum2 += A[i][j]*X[j];
            }

            Xnew[i] = (B[i] - sum1 - sum2)/A[i][i];
        }
        for(int i=0; i<n; i++) {
            X[i]=Xnew[i];
            cout << X[i] << "  ";
        }
        cout << "\n";
    }

    // double e = pow(10, -8);
    // double diff = 1;
    // int counter = 0;

    // while (diff > e) {
    //     for (int i=0; i<n; i++) {
    //         double sum = 0;
    //         for (int j=0; j<n; j++) {
    //             if (j == i) {
    //                 continue;
    //             }
    //             sum += A[i][j]*X[j];
    //         }
    //         Xnew[i] = ((B[i] - sum)/A[i][i]);
    //     }

    //     diff = maximum(subtractVectors(Xnew, X))/maximum(Xnew);

    //     for(int i=0; i<n; i++) {
    //         X[i]=Xnew[i];
    //     }
    //     counter++;
    // }
    // cout << "Iterations in Jacobi: " << counter << "\n\n";

    return X;
}



// Warunek stopu
// || x^(k) - x(k-1) || / || x(k) ||

int main() {
    vector<vector<double>> A = {{4, -2, 0, 0}, {-2, 5, -1, 0}, {0, -1, 4, 2}, {0, 0, 2, 3}};
    vector<double> B = {0, 2, 3, -2};
    int n = 4;

    vector<double> jacobiResult = jacobiMethod(A, B, 100);
    cout << "Jacobi method result:\n";
    for (int i=0; i<n; i++) {
        cout << jacobiResult[i] << "\n";
    }
    cout << "\n";

    vector<double> gaussSeidlResult = gaussSeidlMethod(A, B, 100);
    cout << "Gauss-Seidl method result:\n";
    for (int i=0; i<n; i++) {
        cout << gaussSeidlResult[i] << "\n";
    }

    return 0;
}