#include <math.h>
#include <stdio.h>
#include <stdlib.h>

void zad1() {
    float a = 0.51;
    float b = 0.98;
    float c = 450.67;
    float result1 = (a + b) + c;
    float result2 = a + (b + c);
    printf("Is %f equal to %f?\n", result1, result2);
}

void generateArray(float* array, const int N, int m) {
    for (int i=0; i<N; i++) {
        int mod = i%m;
        array[i] = 1./((mod + 1)*(mod + 2));
    }
}

float zad2() {
    const int N = 1<<20;
    int m = 1<<5;
    float* array = (float*)malloc(N*sizeof(float));

//    for (int i=0; i<N; i++) {
//        int mod = i%m;
//        array[i] = 1./((mod + 1)*(mod + 2));
//    }
    generateArray(array, N, m);

    float arraySum = 0;
    for (int i=0; i<N; i++) {
        arraySum += array[i];
    }
    return arraySum;
}

float altSum() {
    const int N = 1<<20;
    int m = 1<<5;
    float* array = (float*)malloc(N*sizeof(float));

    float alternativeSum = (float)N/(m+1);
    return alternativeSum;
}

float zad4() {
    const int N = 1<<20;
    int m = 1<<5;
    float* arr = (float*)malloc(N*sizeof(float));
    generateArray(arr, N, m);

    float sum=0;
    float p=0;
    float oldSum = 0;
    for (int i=0; i<N; i++) {
        sum = oldSum + arr[i];
        p = p + (arr[i]-(sum-oldSum));
        oldSum = sum;
    }
    return sum+p;
}

float zad6() {
    const int N = 1<<20;
    int m = 1<<5;
    float* array = (float*)malloc(N*sizeof(float));
    generateArray(array, N, m);

    float e = 0;
    float sum = 0;
    for (int i=0; i<N; i++) {
        float tmp = sum;
        float y = array[i] + e;
        sum = tmp + y;
        e = (tmp - sum) + y;
    }
    return sum;
}

int main()
{
//    zad1();
    float exactSum = zad2();
    float gmSum = zad4();
    float kahanSum = zad6();
    printf("Error GM: %f\n", fabs(gmSum-exactSum)/exactSum);
    printf("Error K: %f\n", fabs(kahanSum-exactSum)/exactSum);
    return 0;
}
