#include <iostream>
using namespace std;

template <class T>
T abs(T n) {
    /* where did this go in execution ?? */
    cout<<n<<endl;
    return n < 0 ? -n : n;
}

int main() {
    cout<<abs(-1)<<endl;
    cout<<abs(-1.4)<<endl;
    cout<<abs(-100000000000)<<endl;
    return 0;
}
