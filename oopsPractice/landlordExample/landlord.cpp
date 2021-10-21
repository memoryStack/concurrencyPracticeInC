#include "landlord.h"

int main() {
    userInterface theUserInterface;
    theUserInterface.interact();
    return 0;
}

//////////////////////global functions////////////////////////
void getaLine(string& inStr) {
    char temp[21];
    cin.get(temp, 20, '\n');
    cin.ignore(20, '\n');
    inStr = temp;
}

char getaChar() {
    char ch = cin.get();
    cin.ignore(80, '\n');
    return ch;
}

/////////////////////methods for class tenant///////////////////
// these costructors/distructors can be in class definition as well
tenant::tenant(string n, int aNo) : name(n), aptNumber(aNo) { /* empty */ }

tenant::~tenant() { /* empty */ }

int tenant::getAptNumber() {
    return aptNumber;
}

bool operator < (const tenant& t1, const tenant& t2) {
    return t1.name < t2.name;
}
bool operator == (const tenant& t1, const tenant& t2) {
    return t1.name == t2.name;
}

ostream& operator << (ostream& s, const tenant& t) {
    s << t.aptNumber << '\t' << t.name << endl;
    return s;
}
