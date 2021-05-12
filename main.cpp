#include <iostream>
#include "matrix.h"
using namespace std;
int main() {
    matrix<double> a(4, 4);
    cin >> a;
    matrix<double> c = a.makeM();
    cout << c;
}