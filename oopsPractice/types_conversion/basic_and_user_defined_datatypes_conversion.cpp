#include <iostream>
using namespace std;

class Distance {
    private:
        float feet, inches;
    public:
        Distance(): feet(0), inches(0) {}
        Distance(int in) { // let's make it as int for the sake of simplicity
            feet = in / 12;
            inches = in % 12;
        }

        void printDistance() {
            cout<<"feet: "<<feet<<"  "<<"inches: "<<inches<<endl;
        }

        // conversion operator 
        operator int() {
            return static_cast<int>(feet * 12.0 + inches);
        }

};

int main() {
    
    Distance d1 = 200; // this is converting "int" basic datatype to an object of "Distance" datatype
    d1.printDistance();

    // this is coverting an object of Distance type into int datatype by using 
    // the "operator conversion" member func in the class
    int inches = d1; 
    cout<<inches<<endl;

    return 0;
}

/*
    every time compiler sees that a type conversion is required when it sees two different
    types on the opposite sides of the "=" operator then it basically looks for the 
    "conversion operator" to convert the one type into another.
    this mechanism happens in both explicit and implicit types of conversions
*/