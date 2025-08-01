#define _USE_MATH_DEFINES

#include <iostream>
#include <cmath>

using namespace std;

// całki
// h = (b-a)/n  - długość przedziału
// h * for(i=0;i<n){sum += f(a+h*(i+0.5))}

const double FA_INTEGRAL = 1.0/3.0;
const double FB_INTEGRAL = 1.0;
const double FC_INTEGRAL = 1.0;

double fa(double x) {
    return x*x;
}

double fb(double x) {
    return cos(x);
}

double fc(double x) {
    return 1/x;
}

double rectangleIntegral(double a, double b, double (*f)(double), double n) {
    double h = (b-a)/n;
    double sum = 0;
    for(int i=0; i<n; i++) {
        sum += f(a + h*(i+0.5));
    }

    return h*sum;
}

// całka metodą trapezów
// h * ((f(a)+f(b))/2 + for(i=1;i<n){sum += f(a + i*h)})

double trapezoidIntegral(double a, double b, double (*f)(double), double n) {
    double h = (b-a)/n;
    double sum = 0;
    for (int i=1; i<n; i++) {
        sum += f(a + i*h);
    }
    return h * ((f(a) + f(b))/2 + sum);
}

// całka metodą Simpsona
// h/6 * (f(a)+4*for(i=0;i<n){f(a+i*h+h/2)} + 2*for(i=1;i<n){f(a+i*h)} + f(b))

double simpsonIntegral(double a, double b, double (*f)(double), double n) {
    double h = (b-a)/n;
    double sum1 = 0;
    for (int i=0; i<n; i++) {
        sum1 += f(a + i*h + h/2);
    }
    double sum2 = 0;
    for (int i=1; i<n; i++) {
        sum2 += f(a + i*h);
    }

    return h/6 * (f(a) + 4*sum1 + 2*sum2 + f(b));
}

double error(double calculated, double exact) {
    return (exact - calculated)/exact;
}

int main() {
    double n = 100;

    double faRect = rectangleIntegral(0, 1, fa, n);
    double fbRect = rectangleIntegral(0, M_PI/2, fb, n);
    double fcRect = rectangleIntegral(M_E, pow(M_E, 2), fc, n);
    cout << "Rectangle integral for a): " << faRect << "\tError: " << error(faRect, FA_INTEGRAL) << "\n";
    cout << "Rectangle integral for b): " << fbRect << "\tError: " << error(fbRect, FB_INTEGRAL) << "\n";
    cout << "Rectangle integral for c): " << fcRect << "\tError: " << error(fcRect, FC_INTEGRAL) << "\n";
    cout << "\n";

    double faTrap = trapezoidIntegral(0, 1, fa, n);
    double fbTrap = trapezoidIntegral(0, M_PI/2, fb, n);
    double fcTrap = trapezoidIntegral(M_E, pow(M_E, 2), fc, n);
    cout << "Trapezoid integral for a): " << faTrap << "\tError: " << error(faTrap, FA_INTEGRAL) << "\n";
    cout << "Trapezoid integral for b): " << fbTrap << "\tError: " << error(fbTrap, FB_INTEGRAL) << "\n";
    cout << "Trapezoid integral for c): " << fcTrap << "\tError: " << error(fcTrap, FC_INTEGRAL) << "\n";
    cout << "\n";

    double faSimp = simpsonIntegral(0, 1, fa, n);
    double fbSimp = simpsonIntegral(0, M_PI/2, fb, n);
    double fcSimp = simpsonIntegral(M_E, pow(M_E, 2), fc, n);
    cout << "Simpson integral for a): " << faSimp << "\tError: " << error(faSimp, FA_INTEGRAL) << "\n";
    cout << "Simpson integral for b): " << fbSimp << "\tError: " << error(fbSimp, FB_INTEGRAL) << "\n";
    cout << "Simpson integral for c): " << fcSimp << "\tError: " << error(fcSimp, FC_INTEGRAL) << "\n";

    return 0;
}