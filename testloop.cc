#include <time.h>
#include <string.h>
#include <iostream>

using namespace std;

int main(){
    const int n = 4096*10;

#ifdef ALLOCATE_SEPERATE
    double *a1 = (double*)malloc(n * sizeof(double));
    double *b1 = (double*)malloc(n * sizeof(double));
    double *c1 = (double*)malloc(n * sizeof(double));
    double *d1 = (double*)malloc(n * sizeof(double));
#else
    double *a1 = (double*)malloc(n * sizeof(double) * 4);
    double *b1 = a1 + n;
    double *c1 = b1 + n;
    double *d1 = c1 + n;
#endif

    //  Zero the data to prevent any chance of denormals.
    memset(a1,0,n * sizeof(double));
    
    memset(c1,0,n * sizeof(double));
    memset(b1,0,n * sizeof(double));
    memset(d1,0,n * sizeof(double));

    //  Print the addresses
    cout << a1 << endl;
    cout << b1 << endl;
    cout << c1 << endl;
    cout << d1 << endl;

    clock_t start = clock();

    int c = 0;
    while (c++ < 10000){

#if ONE_LOOP
        for(int j=0;j<n;j++){
            a1[j] += b1[j];
            c1[j] += d1[j];
        }
#else
        for(int j=0;j<n;j++){
            a1[j] += b1[j];
        }
        for(int j=0;j<n;j++){
            c1[j] += d1[j];
        }
#endif

    }

    clock_t end = clock();
    cout << "seconds = " << (double)(end - start) / CLOCKS_PER_SEC << endl;

    return 0;
}