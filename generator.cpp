/*
 * Outputs random number between 1 and 10^6, inclusive.
 * To generate different values, call "igen.exe" with different parameters.
 * For example, "igen.exe 1" returns 504077, but "igen.exe 3" returns 808747.
 * 
 * It is typical behaviour of testlib generator to setup randseed by command line.
 */

#include "testlib.h"
#include <iostream>

using namespace std;

int main(int argc, char* argv[])
{

    ofstream cout("tc7.in");
    registerGen(argc, argv, 1);
    int N = 500, M = 500;
    cout << N << " " << M << endl;
    for (int i=1;i<=M;i++) {
        cout << rnd.next(1, 5) << " ";
    }
    int L = 500;
    cout << L << endl;
    for (int i=1;i<=L;i++) {
        cout << rnd.next(1, N) << " " << rnd.next(1, M) << endl;
    }

    return 0;
}