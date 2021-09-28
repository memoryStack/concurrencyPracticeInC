#include <iostream>
using namespace std;

class counter {
    private:
        int count;
    public:
        counter(): count(0) {}
        counter(int c): count(c) {}
        int getCount() {
            return count;
        }
        counter operator ++ () {
            return counter(++count);
        }
        counter operator ++ (int) {
            return counter(count++);
        }
};

int main() {
    counter c;
    ++c;
    counter dum = c++;
    counter dum2 = ++c;
    cout<<c.getCount()<<endl;
    cout<<dum.getCount()<<endl;
    cout<<dum2.getCount()<<endl;
    return 0;
}

/*
    how postfix ++ works
        "operator ++ (int)" this is just a syntax to represent that it's postfix overloading for this "++" operator
        here even int doesn't mean anything reklated to integer. it's just a simple syntax
    this example also shows how to return from operators which was absent in previous example
*/
