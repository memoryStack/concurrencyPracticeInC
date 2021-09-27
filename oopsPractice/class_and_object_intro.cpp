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
    cout<<d.getData()<<endl;
}