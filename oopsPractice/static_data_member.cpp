#include <iostream>
using namespace std;

class dataClass {
    private:
        // here we can only declare (not define) this variable here. since it's just a
        // blueprint of the class and no memory allocation will happen here
        static int objCount;
        int data;
    public:
        // constuctor
        dataClass(int d = -1): data(d) {
            objCount++;
        }
        int getData() {
            return data;
        }
        int getObjCount() {
            return objCount;
        }
        // destructor
        ~dataClass() {
            objCount--;
        }
};

// a. we have to define this variable before using it in above funcs otherwise we will 
//      get error at linker step (TODO: understand the linking process and get back to this example)
//      compiler wouldn't give the warning if we don't perform the below step but linker would
// b. we can not define this variable inside the main func because it has to be allocated only 
//      once and shared among all the objects, so we achieve so by defining it globally (it's like a global variable only)
int dataClass::objCount = 0;

int main() {
    dataClass d(1), d2(10);
    cout<<d.getObjCount()<<endl;
}

/*
    caveats
        a. 
*/