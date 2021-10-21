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

// TODO: find out if these operator loading funcs can be declared as const or not ?
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

////////////////method for class tenantInputScreen//////////////
void tenantInputScreen::getTenant() {     //get tenant info
    cout << "Enter tenant's name (George Smith): ";
    getaLine(tName);
    cout << "Enter tenant’s apartment number (101): ";
    cin >> aptNo;
    cin.ignore(80, '\n'); //make tenant
    tenant* ptrTenant = new tenant(tName, aptNo);
    ptrTenantList->insertTenant(ptrTenant); //send to tenant list
}

////////////////////////////////////////////////////////////////
bool compareTenants::operator () (tenant* ptrT1, tenant* ptrT2) const {
    return *ptrT1 < *ptrT2;
}

///////////////////methods for class tenantList/////////////////
tenantList::~tenantList() { // destructor
    while(!setPtrsTens.empty()) {
        iter = setPtrsTens.begin();
        delete *iter;
        setPtrsTens.erase(iter);
    }
} // end ~tenantList()

void tenantList::insertTenant(tenant* ptrT) {
    setPtrsTens.insert(ptrT); //insert
}

int tenantList::getAptNo(string tName) { //name on list?
    int aptNo;
    tenant dummy(tName, 0);
    iter = setPtrsTens.begin();
    while(iter != setPtrsTens.end()) {
        aptNo = (*iter)->getAptNumber();
        if(dummy == **iter++) return aptNo;
    }
    return -1;
}

void tenantList::display() {
    cout << "\nApt#\tTenant name\n-------------------\n";
    if (setPtrsTens.empty()) cout << "***No tenants***\n";
    else {
        iter = setPtrsTens.begin();
        while(iter != setPtrsTens.end())
            cout << **iter++;
    }
}

/////////////////////methods for class rentRow//////////////////
rentRow::rentRow(int an) : aptNo(an) { // 1-arg constructor
   fill(&rent[0], &rent[12], 0);
}

void rentRow::setRent(int m, float am) {
    rent[m] = am;
}

float rentRow::getSumOfRow() { // sum of rents in row
    return accumulate( &rent[0], &rent[12], 0);
}

bool operator < (const rentRow& t1, const rentRow& t2) {
    return t1.aptNo < t2.aptNo;
}

bool operator == (const rentRow& t1, const rentRow& t2) {
    return t1.aptNo == t2.aptNo;
}

ostream& operator << (ostream& s, const rentRow& an) {
    s << an.aptNo << '\t';
    for(int j=0; j<12; j++) {
        if (an.rent[j] == 0) s<<" 0 ";
        else   s << an.rent[j] << " ";
    }
    s << endl;
    return s;
}

bool compareRows::operator () (rentRow* ptrR1, rentRow* ptrR2) const {
    return *ptrR1 < *ptrR2;
}
