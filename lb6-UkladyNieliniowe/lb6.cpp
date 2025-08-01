#include <iostream>
#include <cmath>

using namespace std;

// f(x)
// [a,b]
// epsilon
// warunek początkowy: f(a) * f(b) >= 0

// Bisekcja
// c = (a+b)/2
// f(c) == 0
// f(a) * f(c) < 0 -> podstawiamy b = c
// f(c) * f(b) < 0 -> podstawiamy a = c
// warunek |a-b| >= epsilon

double function1(double x) {
    return x*x - 4;
}

double function1Derivate(double x) {
    return 2*x;
}

double function1DerivateDerivate(double x) {
    return 2;
}

double function2(double x) {
    return sin(x) - 0.5;
}

double function2Derivate(double x) {
    return cos(x);
}

double function2DerivateDerivate(double x) {
    return -sin(x);
}

double bisection(double a, double b, double (*f)(double)) {
    if (f(a) * f(b) >= 0) {
        return -404;
    }

    double c = (a+b)/2;
    double epsilon = pow(10, -4);

    while(abs(a-b) >= epsilon) {
        if (f(c) == 0) {
            return c;
        } else if (f(a) * f(c) < 0) {
            return bisection(a, c, f);
        } else if (f(c) * f(b) < 0) {
            return bisection(c, b, f);
        }
    }
    return c;
}

// Newton
// xi = x(i-1) - (f(x(i-1)))/(f'(x(i-1))) < epsilon
// x = (a+b)/2
// f'(x) * f''(x) < 0, x1 = a
// f'(x) * f''(x) > 0, x1 = b

double newton(double a, double b, double (*f)(double), double (*fd)(double), double (*fdd)(double)) {
    if (f(a) * f(b) >= 0) {
        return -404;
    }

    double epsilon = pow(10, -4);
    double c = (a+b)/2;
    double x;

    if (fd(c) * fdd(c) < 0) {
        x = a;
    } else if (fd(c) * fdd(c) > 0) {
        x = b;
    }

    while (f(x)/fd(x) >= epsilon) {
        if (f(x) == 0)
            return x;
        x = x - f(x)/fd(x);
    }
    return x;
}

// Sieczne
// x = (a+b)/2
// f'(x) * f''(x) < 0, x1 = a
// f'(x) * f''(x) > 0, x1 = b
// x(i+1) = xi - f(xi) * (xi - x(i-1))/(f(xi) - f(x(i-1)))

double secant(double a, double b, double (*f)(double), double (*fd)(double), double (*fdd)(double)) {
    if (f(a) * f(b) >= 0) {
        return -404;
    }

    int iter = 100;
    double epsilon = pow(10, -4);
    double c = (a+b)/2;
    double x1, x2;

    if (fd(c) * fdd(c) < 0) {
        x1 = b;
        x2 = a;
    } else if (fd(c) * fdd(c) > 0) {
        x1 = a;
        x2 = b;
    }

    for (int i=0; i < iter; i++) {
        if (f(x2) == 0 || f(x2) * (x2 - x1)/(f(x2) - f(x1)) < epsilon) {
            return x2;
        }
        double x3 = x2 - f(x2) * (x2 - x1)/(f(x2) - f(x1));
        x1 = x2;
        x2 = x3;
    }
    return x2;
}

double regularFalsi(double a, double b, double (*f)(double)) {
    if (f(a) * f(b) >= 0) {
        return -404;
    }

    int iter = 100;
    double epsilon = pow(10, -4);
    double x = (a * f(b) - b * f(a)) / (f(b) - f(a));

    for (int i=0; i > iter; i++) {
        double x1 = 0;
        if(f(x) == 0)
            return x;
        if(f(a) * f(x) < 0) {
            x1 = (x * f(a) - a * f(x)) / (f(a) - f(x));
        } else if (f(b) * f(x) < 0) {
            x1 = (x * f(b) - b * f(x)) / (f(b) - f(x));
        }
        if(abs(x - x1) < epsilon)
            return x1;
        x = x1;
    }
    return x;
}

int main() {
    cout << "Bisection a): " << bisection(0, 2.2, function1) << "\n";
    cout << "Bisection b): " << bisection(0, 2.2, function2) << "\n";
    cout << "Newton a): " << newton(0, 2.2, function1, function1Derivate, function1DerivateDerivate) << "\n";
    cout << "Newton b): " << newton(0, 2.2, function2, function2Derivate, function2DerivateDerivate) << "\n";
    cout << "Secant a): " << secant(0, 2.2, function1, function1Derivate, function1DerivateDerivate) << "\n";
    cout << "Secant b): " << secant(0, 2.2, function2, function2Derivate, function2DerivateDerivate) << "\n";
    cout << "Regular Falsi a): " << regularFalsi(0, 2.2, function1) << "\n";
    cout << "Regular Falsi b): " << regularFalsi(0, 2.2, function2) << "\n";

    return 0;
}