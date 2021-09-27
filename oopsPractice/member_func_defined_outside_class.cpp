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

        void printSomething(); // it's must to declare it here. else we will get compiler error
};

void dataClass::printSomething() {
    cout<<"print something"<<endl;
}

int main(){
    dataClass d(10, 20);
    cout<<d.getData()<<endl;
    d.printSomething();
}

/*
    "::" is scope resolution operator
    "dataClass" -> name of the class "printSomething" is a member func of.
*/