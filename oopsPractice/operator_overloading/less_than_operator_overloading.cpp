#include <iostream>
using namespace std;

class Int {
    private:
        int num;
    public:
        Int(): num(0) {}
        Int(int c): num(c) {}
        int getInt() {
            return num;
        }
        bool operator < (Int i) {
            return num < i.num;
        }        
};

int main() {
    Int num1;
    Int num2(10);
    cout<<(num2 < num1)<<endl;
    return 0;
}

