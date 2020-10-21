//
//  duty.cpp
//  Project2
//

#include <iostream>
#include <iomanip>
using namespace std;

int main()
{
    // variable delcarations for "cheeseType", "value", and "importer"
    string cheeseType;
    double value;
    string importer;
    
    // prompt user to enter cheese type, read user input for cheese type, store in string "cheeseType", check for empty string case and output appropriate message if necessary
    cout << "Cheese type: ";
    getline(cin, cheeseType);
    
    if (cheeseType == "")
    {
        cout << "---" << endl;
        cout << "You must enter a cheese type" << endl;
        return 0;
    }
    
    // prompt user to enter value, read user input for value, store in double "value", check for non-positive value and output appropriate message if necessary
    cout << "Value: ";
    cin >> value;
    cin.ignore(6969, '\n');
    
    if (value <= 0)
    {
        cout << "---" << endl;
        cout << "The value must be positive" << endl;
        return 0;
    }
    
    // prompt user to enter importer, read user input for importer, store in string "importer", check for empty string case and output appropriate message if necessary
    cout << "Importer: ";
    getline(cin, importer);
    
    if (importer == "")
    {
        cout << "---" << endl;
        cout << "You must enter an importer" << endl;
        return 0;
    }
    
    /* variable declarations and initializations for "first1000Duty", "next12000Duty",
     * "remainingDuty", and "totalDuty"
     */
    double first1000Duty = 0;
    double next12000Duty = 0;
    double remainingDuty = 0;
    double totalDuty = 0;
    
    // calculate "first1000Duty" based on first $1000 in value
    if (value < 1000)
    {
        first1000Duty = value * .011;
    }
    else
    {
        first1000Duty = 11;
    }
    
    /* calculate "next12000Duty" based on next $12000 in value,
     * adjust duty rate accordingly if "cheeseType" is "cheshire" or "stilton"
     */
    if (cheeseType == "cheshire" || cheeseType == "stilton")
    {
        if (value > 1000 && value < 13000)
            next12000Duty = (value - 1000) * .014;
        else if (value >= 13000)
            next12000Duty = 168;
    }
    else if (value > 1000 && value < 13000)
        next12000Duty = (value - 1000) * .02;
    else if (value >= 13000)
        next12000Duty = 240;
    
    // calculate "remainingDuty" based on remaining value above 13000
    if (value > 13000)
        remainingDuty = (value - 13000) * .029;
    
    // calculate "totalDuty" by summing "first1000Duty", "next12000Duty", and "remainingDuty"
    totalDuty = first1000Duty + next12000Duty + remainingDuty;
    
    // output hyphens and final statement
    cout << "---" << endl;
    cout << fixed << showpoint;
    cout << setprecision(2);
    cout << "The import duty for " << importer << " is $" << totalDuty << endl;
}
