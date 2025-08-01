#include<iostream>
#include<cmath>
#include<cstdlib>
#include<vector>

using namespace std;

// LCG
// X(n+1) = (a*Xn+c) mod M
// X0 - ziarno
// M - zakres
// c - względnie pierwsza z M NWD(M,a) = 1
// p|M => p|(a-1)

vector<unsigned int> randomLcg(unsigned int seed, unsigned int a, unsigned int c, unsigned int m, unsigned int n) {
    vector<unsigned int> results(n);
    results[0] = seed;
    for (int i=1; i<n; i++) {
        results[i] = fmod((a*results[i-1]+c), m);
    }
    return results;
}

int countOnes(vector<unsigned int> numbers) {
    int size = numbers.size();
    int sum = 0;
    for (int i=0; i<size; i++) {
        while(numbers[i]) {
            sum += numbers[i] & 1;
            numbers[i] >>= 1;
        }
    }
    return sum;
}

// Mote Carlo
// p i q to środek koła
// generujemy punkt x,y
// sprawdzamy, czy punkt należy do koła:
// (x-p)^2 + (y-q)^2 <= r^2
// zwiększyć licznik

double monteCarlo(unsigned int r) {
    int n = 1000;
    int range = 100;
    int r = range/2;
    int p = r;
    int q = r;
    int counter = 0;
    vector<vector<unsigned int>> points(n);
    for (int i=0; i<n; i++) {
        points[i] = vector<unsigned int>(2);
        points[i][0] = (rand() / RAND_MAX) * range;
        points[i][1] = (rand() / RAND_MAX) * range;
    }

    return 4.0 * counter / (n/2);
}

int main() {

    const int n = 625;
    unsigned int seed = 10;
    unsigned int range = 201;
    unsigned int c = 43;
    unsigned int a = 403;
    vector<unsigned int> lcgResults = randomLcg(seed, a, c, range, n);
    // vector<vector<unsigned int>> points(n/2);

    // for (int i=0; i<(int)(n/2); i++) {`
    //     points[i] = vector<unsigned int>(2);
    // }

    // for (int i=0; i<n; i++) {
    //     cout << lcgResults[i] << " ";
    //     // points[(int)i/2][i%2] = lcgResults[i];
    // }
    // cout << "\n";

    // for (int i=0; i<n/2; i++) {
    //     cout << points[i][0] << "," << points[i][1] << " ";
    // }
    // cout << "\n";

    cout << "Number of ones in the algorith result: " << countOnes(lcgResults) << "\n";

    return 0;
}