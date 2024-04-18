#include <iostream>
#include <vector>
#include <map>

using namespace std;

// Lagrange
// W(x) = for(i=0; i<n; i++){sum(yi*(for(j=0; j<n; j++; j!=i){(x-xi)/(xi-xj)}))}
// Dane wejściowe:
// n - punktów
// x - którego f(x) mamy interpolować

double lagrange(double num, vector<double> x, vector<double> y) {
    double sum = 0;
    int n = x.size();
    for (int i = 0; i < n; i++) {
        double mul = 1;
        for (int j = 0; j < n; j++) {
            if (j != i) {
                mul *= (num-x[j])/(x[i]-x[j]);
            }
        }
        sum += y[i] * mul;
    }
    return sum;
}

// Newton
// W(x) = for(k=0;k<n){f[x0,x1,...,xk]*for(j=0;j<k-1){x-xj}}
// f[xi] = f(xi) = y[i]
// f[xi, x(i+1)] = (f[x(i+1)] - f[x])/(x(i+1)-xi)
// f[x0, x1, x2, x3, ..., xk] = (f[x1, x2, ..., xk] - f[x0, x1, ..., x(k-1)])/(xk-x0)

double diffmul(vector<double> x, map<double, double> f) {
    int n = x.size();
    vector<double> v1;
    vector<double> v2;
    if (n == 1) {
        return f[x[0]];
    } else if (n == 2) {
        v1.push_back(x[0]);
        v2.push_back(x[1]);
    } else {
        copy(x.begin()+1, x.end(), back_inserter(v1));
        copy(x.begin(), x.end()-1, back_inserter(v2));
    }
    // v1.erase(v1.begin());
    // v2.erase(v2.begin()+n-1);
    // cout << "Length: " << v1.size() << "\n";
    return (diffmul(v1, f) - diffmul(v2, f))/(x[n-1]-x[0]);
}

double newton(double num, vector<double> x, vector<double> y) {
    int n = x.size();
    double sum = 0;
    map<double, double> f;
    for(int i=0; i<n; i++) {
        f[x[i]] = y[i];
    }

    for (int k = 0; k < n; k++) {
        double mul = 1;
        vector<double> tmp;
        if(k==0) {
            tmp.push_back(x[0]);
        } else {
            copy(x.begin(), x.begin()+k+1, back_inserter(tmp));
        }
        for (int j = 0; j < (k-1); j++) {
            mul *= num - x[j];
        }
        sum += diffmul(tmp, f) * mul;
    }

    return sum;
}

double line(double num, vector<double> x, vector<double> y) {
    int n = x.size();
    int i, j;
    for (int k=0; k<n; k++) {
        if (x[k] < num && x[k+1] > num) {
            i = k;
            j = k+1;
            break;
        }
    }
    return y[i] + (y[j]-y[i])/(x[j]-x[i])*(num-x[i]);
}

int main() {
    double num = 1.5;
    vector<double> x = {-1.4,-1, 0,1, 2, 2.2, 2.5, 2.7, 3, 3.2};
    vector<double> y = {11.95,1.85,1,0.54,0.17,0.31,0.57,0.76,0.97,0.99};

    cout << "Lagrange for " << num << ": " << lagrange(num, x, y) << "\n";
    cout << "Newton for " << num << ": " << newton(num, x, y) << "\n";
    cout << "Line for " << num << ": " << line(num, x, y) << "\n";

    return 0;
}