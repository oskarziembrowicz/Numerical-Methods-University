#include <iostream>
#include <cmath>
#include <vector>
#include <complex>

using namespace std;
typedef complex<double> Complex;

// Wielomian
// P(z) = an*z^n + a(n-1)*z^(n-1) + ... + a1*z + a0
// P(z) = (((an*z + a(n-1))*z + a(n-2))*z + ... + a1)*z + a0
// p=0
//p <- p*z + ai, i=n...0

Complex horner(Complex z, vector<Complex> a) {
    int n = a.size();
    Complex p = 0;
    for (int i=n-1; i>=0; i--) {
        p = p * z + a[i];
    }
    return p;
}

// First derivative
// p = p*z + i*ai, i=n...1

Complex deriv1(Complex z, vector<Complex> a) {
    int n = a.size();
    Complex p = 0;
    for (int i=n-1; i>=1; i--) {
        p = p * z + Complex(i, 0) * a[i];
    }
    return p;
}

// Second derivarive
// p = p*z + i*(i-1)*ai, i=n...2

Complex deriv2(Complex z, vector<Complex> a) {
    int n = a.size();
    Complex p = 0;
    for (int i=n-1; i>=2; i--) {
        p = p * z + Complex(i, 0) * Complex(i-1, 0) * a[i];
    }
    return p;
}

// Laguerre'a
// G = P'(z0)/P(z0)
// H = G^2 - P''(z0)/P(z0)
// s = sqrt((n-1)(n*H-G^2))
// a = n/(G +- s)
// |G + s|  |G - s| (wybierz większe)
// z(i+1) = zi - a
// z0, eps = 10^(-4), iter = 10 v 100

Complex laguerre(Complex z, vector<Complex> poly, double eps, int iter) {
    int n = poly.size();
    for (int i=0; i<iter; i++) {
        if (abs(horner(z, poly)) < eps) {
            return z;
        }
        Complex G = deriv1(z, poly)/horner(z, poly);
        Complex H = G*G - deriv2(z, poly)/horner(z, poly);
        Complex s = sqrt(Complex(n-1,0)*(Complex(n,0) * H - G*G));
        Complex a;
        if (abs(G + s) >= abs(G - s)) {
            a = Complex(n, 0)/(G + s);
        } else {
            a = Complex(n, 0)/(G - s);
        }
        z = z - a;
    }
    return z;
}

// P(z) = (z-z(solve) - Q(z))
// q(n-1) = an
// qi = a(i+1) + zn*q(i+1)
// i = n-2...0

vector<Complex> allRoots(Complex z, vector<Complex> poly, double eps, int iter) {
    z = laguerre(z, poly, eps, iter);
    vector<Complex> results;
    results.push_back(z);
    int n = poly.size();
    while(true) {
        vector<Complex> a;
        a.push_back(poly[n-1]);
        for (int i=n-2;i>=0; i--) {
            a.push_back(poly[i+1] + z * a[i+1]);
        }
        if(a.size() < 2) {
            return results;
        }
        z = laguerre(z, a, eps, iter);
        results.push_back(z);
    }
}

int main() {
    vector<Complex> polynominal1 = {Complex(-6, 0), Complex(11, 0), Complex(-6, 0), Complex(1, 0)};
    // w(1) = 0
    // w'(1) = 2
    // w''(1) = -6
    // w(x) = 0 for x = 1, 2, 3
    vector<Complex> polynominal2 = {Complex(-1, 0), Complex(11, 0), Complex(-6, 0), Complex(1, 0)};
    // w(1) = 5
    // w'(1) = 2
    // w''(1) = -6

    cout << "Polynominal 1 in Horner: " << horner(Complex(1, 0), polynominal1) << "\n";
    cout << "Polynominal 2 in Horner: " << horner(Complex(1, 0), polynominal2) << "\n\n";

    cout << "First derivative for 1: " << deriv1(Complex(1, 0), polynominal1) << "\n";
    cout << "Second derivative for 1: " << deriv2(Complex(1, 0), polynominal1) << "\n";
    cout << "First derivative for 2: " << deriv1(Complex(1, 0), polynominal2) << "\n";
    cout << "Second derivative for 2: " << deriv2(Complex(1, 0), polynominal2) << "\n\n";

    double epsilon = pow(10, -4);
    int iterNumber = 10;
    cout << "Laguerre'a for 1: " << laguerre(Complex(10, 0), polynominal1, epsilon, iterNumber) << "\n";

    return 0;
}