#include <iostream>
using namespace std;

class counter {
    private:
        int count;
    public:
        counter(): count(0) {}
        int getCount() {
            return count;
        }
        void operator ++ () {
            count++;
        }
};

int main() {
    counter c;
    ++c;
    ++c;
    cout<<c.getCount()<<endl;
    return 0;
}

/*
    this is how we overload operators for our defined data types.
    this operator works as a prefix increment only.
*/
