#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

double funA(double x) {
    return 2*x*x + 2;
}

double funAder(double x) {
    return 4*x;
}

double funB(double x) {
    return 2*pow(x, 4) - x*x + 3*x - 7;
}

double funBder(double x) {
    return 8*pow(x, 3) - 2*x + 3;
}

double funC(double x) {
    double e = exp(1.0);
    return x*x*pow(e, x);
}

double funCder(double x) {
    double e = exp(1.0);
    return 2*x*pow(e, x) + x*x*pow(e, x);
}

double newton(double(*f)(double), double x, double h) {
    return (f(x+h) - f(x))/h;
}

double backwards(double(*f)(double), double x, double h) {
    return (f(x) - f(x-h))/h;
}

double central(double(*f)(double), double x, double h) {
    double n1 = f(x+h) - f(x-h);
    double n2 =  2 * h;
    return n1/n2;
}

// Wprzód
//
// Wsteczna 3pkt
//
// Centralna 4pkt
//

double newton3(double(*f)(double), double x, double h) {
    double n1 = -3*f(x) + 4*f(x+h) - f(x+2*h);
    double n2 = 2*h;
    return n1/n2;
}

double backwards3(double(*f)(double), double x, double h) {
    double n1 = 3*f(x) - 4*f(x-h) + f(x-2*h);
    double n2 = 2*h;
    return n1/n2;
}

double central4(double(*f)(double), double x, double h) {
    double n1 = f(x-2*h) - 8*f(x-h) + 8*f(x+h) - f(x+2*h);
    double n2 = 12*h;
    return n1/n2;
}

// lagrange
// w(x) = sum(i=0,i<n){yi*(mul(j=0,j!=i,j<n){(x-xj)/(xi-xj)})}
// (w(x+h)-w(x))/h

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

double derivLagrange(double(*f)(double,vector<double>,vector<double>), double num, double h, vector<double> x, vector<double> y) {
    return (lagrange(num+h, x, y) - lagrange(num, x, y))/h;
}

double error(double exact, double calculated) {
    return abs(exact - calculated)/exact;
}

int main() {
    double x = 3;
    double h = pow(10, -2);
    
    cout << "Function A newton: " << newton(funA,x, h) << "\n";
    cout << "Function A newton error: " << error(funAder(x), newton(funA, x, h)) << "\n";
    cout << "\n";
    cout << "Function A back: " << backwards(funA,x, h) << "\n";
    cout << "Function A back error: " << error(funAder(x), backwards(funA, x, h)) << "\n";
    cout << "\n";
    cout << "Function A central: " << central(funA,x, h) << "\n";
    cout << "Function A central error: " << error(funAder(x), central(funA, x, h)) << "\n";
    cout << "\n";
    cout << "Function A newton3: " << newton3(funA,x, h) << "\n";
    cout << "Function A newton3 error: " << error(funAder(x), newton3(funA, x, h)) << "\n";
    cout << "\n";
    cout << "Function A back3: " << backwards3(funA,x, h) << "\n";
    cout << "Function A back3 error: " << error(funAder(x), backwards3(funA, x, h)) << "\n";
    cout << "\n";
    cout << "Function A central4: " << central4(funA,x, h) << "\n";
    cout << "Function A central4 error: " << error(funAder(x), central4(funA, x, h)) << "\n";
    cout << "\n\n";

    cout << "Function B newton: " << newton(funB, x, h) << "\n";
    cout << "Function B newton error: " << error(funBder(x), newton(funB, x, h)) << "\n";
    cout << "\n";
    cout << "Function B back: " << backwards(funB, x, h) << "\n";
    cout << "Function B back error: " << error(funBder(x), backwards(funB, x, h)) << "\n";
    cout << "\n";
    cout << "Function B central: " << central(funB, x, h) << "\n";
    cout << "Function B central error: " << error(funBder(x), central(funB, x, h)) << "\n";
    cout << "\n";
    cout << "Function B newton3: " << newton3(funB,x, h) << "\n";
    cout << "Function B newton3 error: " << error(funBder(x), newton3(funB, x, h)) << "\n";
    cout << "\n";
    cout << "Function B back3: " << backwards3(funB,x, h) << "\n";
    cout << "Function B back3 error: " << error(funBder(x), backwards3(funB, x, h)) << "\n";
    cout << "\n";
    cout << "Function B central4: " << central4(funB,x, h) << "\n";
    cout << "Function B central4 error: " << error(funBder(x), central4(funB, x, h)) << "\n";
    cout << "\n\n";

    cout << "Function C newton: " << newton(funC, x, h) << "\n";
    cout << "Function C newton error: " << error(funCder(x), newton(funC, x, h)) << "\n";
    cout << "\n";
    cout << "Function C back: " << backwards(funC, x, h) << "\n";
    cout << "Function C back error: " << error(funCder(x), backwards(funC, x, h)) << "\n";
    cout << "\n";
    cout << "Function C central: " << central(funC, x, h) << "\n";
    cout << "Function C central error: " << error(funCder(x), central(funC, x, h)) << "\n";
    cout << "\n";
    cout << "Function C newton3: " << newton3(funC,x, h) << "\n";
    cout << "Function C newton3 error: " << error(funCder(x), newton3(funC, x, h)) << "\n";
    cout << "\n";
    cout << "Function C back3: " << backwards3(funC,x, h) << "\n";
    cout << "Function C back3 error: " << error(funCder(x), backwards3(funC, x, h)) << "\n";
    cout << "\n";
    cout << "Function C central4: " << central4(funC,x, h) << "\n";
    cout << "Function C central4 error: " << error(funCder(x), central4(funC, x, h)) << "\n";
    
    vector<double> x1 = {1, 2, 3, 4, 5};
    vector<double> y1 = {4, 10, 20, 34, 52};
    double num = 3.5;
    cout << "lagrange for " << num << ": " << derivLagrange(lagrange, num, h, x1, y1) << "\n";

    return 0;
}