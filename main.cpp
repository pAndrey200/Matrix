#include <iostream>
#include "matrix.h"
using namespace std;
int main(){
    matrix<int> a(2,5);
    a.SetMij(1,2,3);
    a.Print("a");
}