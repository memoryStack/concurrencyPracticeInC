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

///////////////////methods for class rentRecord/////////////////
rentRecord::~rentRecord() {
    while(!setPtrsRR.empty()) {
        iter = setPtrsRR.begin();
        delete *iter;
        setPtrsRR.erase(iter);
    }
}

void rentRecord::insertRent(int aptNo, int month, float amount) {
    rentRow searchRow(aptNo); //temp row with same aptNo
    iter = setPtrsRR.begin(); //search setPtrsRR
    while(iter != setPtrsRR.end()) {
        if (searchRow == **iter) {
            (*iter)->setRent(month, amount);
            return;
        }
        else iter++;
    }
    rentRow* ptrRow = new rentRow(aptNo); //make new row
    ptrRow->setRent(month, amount); //put rent in row
    setPtrsRR.insert(ptrRow); //put row in vector
} // end insertRent()

void rentRecord::display() {
    cout << "\nAptNo\tJan  Feb  Mar  Apr  May  Jun  "
    << "Jul Aug Sep Oct Nov Dec\n"
    << "---------------------------------"
    << "---------------------------------\n";
    if (setPtrsRR.empty()) cout << "***No rents***\n";
    else {
        iter = setPtrsRR.begin();
        while(iter != setPtrsRR.end()) cout << **iter++;
    }
}

float rentRecord::getSumOfRents() {
    float sumRents = 0.0;
    iter = setPtrsRR.begin();
    while(iter != setPtrsRR.end()) {
        sumRents += (*iter)->getSumOfRow();
        iter++;
    }
   return sumRents;
}

/////////////////methods for class rentInputScreen//////////////
void rentInputScreen::getRent() {
    cout << "Enter tenant’s name: ";
    getaLine(renterName);
    aptNo = ptrTenantList->getAptNo(renterName);
    if (aptNo > 0) { // if name found,
        // get rent amount
        cout << "Enter amount paid (345.67): ";
        cin >> rentPaid;
        cin.ignore(80, '\n');
        cout << "Enter month rent is for (1-12): ";
        cin >> month;
        cin.ignore(80, '\n');
        month--; // (internal is 0-11)
        ptrRentRecord->insertRent(aptNo, month, rentPaid);
    }
    else cout << "No tenant with that name.\n";
} // end getRent()

///////////////////methods for class expense////////////////////
bool operator < (const expense& e1, const expense& e2) {
    if (e1.month == e2.month) return e1.day < e2.day;
    else return e1.month < e2.month;
}

bool operator == (const expense& e1, const expense& e2) {
    return e1.month == e2.month && e1.day == e2.day;
}

ostream& operator << (ostream& s, const expense& exp) {
    s << exp.month << '/' << exp.day << '\t' << exp.payee << '\t';
    s << exp.amount << '\t' << exp.category << endl;
    return s;
}

bool compareDates::operator () (expense* ptrE1, expense* ptrE2) const {
    return *ptrE1 < *ptrE2;
}

bool compareCategories::operator () (expense* ptrE1, expense* ptrE2) const {
    return ptrE1->category < ptrE2->category;
}

//////////////////methods for class expenseRecord///////////////
expenseRecord::~expenseRecord() {
    while(!vectPtrsExpenses.empty()) {
        iter = vectPtrsExpenses.begin();
        delete *iter;
        vectPtrsExpenses.erase(iter);
    }
}

void expenseRecord::insertExp(expense* ptrExp) {
    vectPtrsExpenses.push_back(ptrExp);
}

void expenseRecord::display() {
   cout << "\nDate\tPayee\t\tAmount\tCategory\n"
        << "---------------------------------------\n";
    if (vectPtrsExpenses.size() == 0) cout << "***No expenses***\n";
    else {
        sort(vectPtrsExpenses.begin(), vectPtrsExpenses.end(), compareDates());
        iter = vectPtrsExpenses.begin();
        while(iter != vectPtrsExpenses.end())
            cout << **iter++;
    }
}

float expenseRecord::displaySummary() {// used by annualReport
    float totalExpenses = 0;
    if (vectPtrsExpenses.size() == 0) {
        cout << "\tAll categories\t0\n";
        return 0;
    }
    // sort by category
    sort(vectPtrsExpenses.begin(), vectPtrsExpenses.end(), compareCategories());
    // for each category, sum the entries
    iter = vectPtrsExpenses.begin();
    string tempCat = (*iter)->category;
    float sumCat = 0.0;
    while( iter != vectPtrsExpenses.end()) {
        if(tempCat == (*iter)->category)
            sumCat += (*iter)->amount; // same category
        else {                            // different category
            cout << '\t' << tempCat << '\t' << sumCat << endl;
            totalExpenses += sumCat;
            tempCat = (*iter)->category;
            sumCat = (*iter)->amount;
        }
        iter++;
    } // end while
    totalExpenses += sumCat;
    cout << '\t' << tempCat << '\t' << sumCat << endl;
    return totalExpenses;
} // end displaySummary()

