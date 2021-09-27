#include <iostream>

using namespace std;

class dataClass {
    private: 
        int data;
    public:
        void setData(int d) {
            data = d;
        }
        int getData() {
            return data;
        }
};

int main(){
    dataClass d;
    d.setData(10);
    // it will invoke the default copy constuctor. don't think that we need 
    // to define a one-arg constructor in dataClass class
    dataClass d2(d); 
    // this is not a simple assignment statement. it will also invoke the default copy constuctor
    dataClass d3 = d;
    cout<<d2.getData()<<endl;
    cout<<d3.getData()<<endl;
}
