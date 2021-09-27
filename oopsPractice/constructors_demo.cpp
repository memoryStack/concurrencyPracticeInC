#include <iostream>

using namespace std;

class dataClass {
    private: 
        int dataA, dataB;
    public:
        dataClass(int dA = -1, int dB = -1): dataA(dA), dataB(dB) // this is known as initializer list
        {
            cout<<"constructor called"<<endl;
        }
        void setData(int d) {
            dataA = d;
        }
        
        int getData() {
            return dataA;
        }
};

int main(){
    dataClass d(10, 20);
    cout<<d.getData()<<endl;
}

/*
    a little theory about constructors
        a. constructors should be defined in the "public" block always else 
            the compiler will give errror
        b. always use initializer list for initializing the data members. why ?
            a. members initialized in the initializer list are given a value before
                the constructor even starts to execute
            b. initializer list is the only way to initialize const member data and references.
                TODO: test this thing someday
*/