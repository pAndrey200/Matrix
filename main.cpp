#include <iostream>
#include "matrix.h"
using namespace std;
int main() {
    matrix a(4, 4);
    cin >> a;
    matrix c = a.makeM();
    cout << c;
}