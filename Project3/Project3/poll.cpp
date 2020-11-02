//
//  poll.cpp
//  Project3
//

#include <iostream>
#include <string>
#include <cctype>

using namespace std;

// Return true if the argument is a two-uppercase-letter state code, or
// false otherwise.

bool isValidUppercaseStateCode(string stateCode)
{
    const string codes =
    "AL.AK.AZ.AR.CA.CO.CT.DE.DC.FL.GA.HI.ID.IL.IN.IA.KS."
    "KY.LA.ME.MD.MA.MI.MN.MO.MS.MT.NE.NV.NH.NJ.NM.NY.NC."
    "ND.OH.OK.OR.PA.RI.SC.SD.TN.TX.UT.VT.VA.WA.WV.WI.WY";
    return (stateCode.size() == 2  &&
            stateCode.find('.') == string::npos  &&  // no '.' in stateCode
            codes.find(stateCode) != string::npos);  // match found
}

bool isSyntacticallyCorrect(string pollData)
{
    // checks if pollData is the empty string and returns true if this is the case
    if (pollData == "")
        return true;
    
    /* checks if pollData meets minimum length requirement for validity; a string with length
     less than 4 cannot possibly be valid
     */
    if (pollData.size() < 4)
        return false;
    
    // checks if all characters in pollData are letters or numbers
    for (size_t i = 0; i != pollData.size(); i++)
    {
        if (isalpha(pollData.at(i)) == false && isdigit(pollData.at(i)) == false)
            return false;
    }
    
    /* convert all lowercase letters in pollData to uppercase letters for use of isValidUppercaseStateCode
     since state codes are not case sensitive but the function is
     */
    for (size_t j = 0; j != pollData.size(); j++)
    {
        pollData.at(j) = toupper(pollData.at(j));
    }
    
    int k = 0;
    // upper bound prevents out of bounds case
    while (k < pollData.size() - 3)
    {
        /* checks case of one digit (representing a state having single-digit electoral votes)
         followed by a valid two-character state code (determined using isValidUppercasestateCode)
         and one-character party affiliation
         */
        if (isdigit(pollData.at(k)) && isValidUppercaseStateCode(pollData.substr(k + 1, 2)) && isalpha(pollData.at(k + 3)))
        {
            // move on to beginning of next state forecast
            k += 4;
        }
        /* checks case of two digits (representing a state having double-digit electoral votes)
         followed by a valid two-character state code (determined using isValidUppercasestateCode)
         and one-character party affiliation
         */
        else if (isdigit(pollData.at(k)) && isdigit(pollData.at(k + 1)) &&
            isValidUppercaseStateCode(pollData.substr(k + 2, 2)))
        {
            /* prevents out of bounds error by checking if k + 4 (the would-be position of the last party code for the last state forecast) is is equal to pollData.size(), a position which exceeds the largest defined index in pollData
             */
            if ((k + 4) == pollData.size())
                return false;
            else if (isalpha(pollData.at(k + 4)))
                // move on to beginning of next state forecast
                k += 5;
            /* need this else statement here so function does not get stuck in infinite loop when encountering
             two numbers, a valid two-letter state code, and another number
             */
            else
                return false;
        }
        // if neither condition is met, return false right away
        else
            return false;
    }
    return true;
}

int tallyVotes(string pollData, char party, int& voteTally)
{
    // return 0 and set voteTally to 0 if pollData is empty string
    if (pollData.size() == 0)
    {
        voteTally = 0;
        return 0;
    }
    
    // return 1 if pollData parameter not syntactically correct
    if (!(isSyntacticallyCorrect(pollData)))
        return 1;
    // return 2 if party parameter is not a letter
    if (!(isalpha(party)))
        return 2;
    // return 3 if first character of pollData is '0'
    if (pollData.at(0) == '0')
        return 3;
    else
        /* return 3 if the character immeidately preceding and following a '0' are both letters or if two '0' characters occur in a row
         */
        for (size_t n = 1; n != pollData.size() - 1; n++)
            if ((isalpha(pollData.at(n - 1)) && pollData.at(n) == '0' && isalpha(pollData.at(n + 1)))
                || (pollData.at(n) == '0' && pollData.at(n + 1) == '0'))
                return 3;
    
    /* set voteTally to 0 since none of the error situations occurred if the program
     reaches this stage in execution, will modify this value with next loop
     */
    voteTally = 0;
    
    int p = 0;
    // same loop structure as the one in isSyntacticallyCorrect()
    while (p < pollData.size() - 3)
    {
        /* checks case of one digit (representing a state having single-digit electoral votes)
         preceding a state code
         */
        if (isdigit(pollData.at(p)))
        {
            if (isalpha(pollData.at(p + 1)))
            {
                /* convert char to int by subtracting '0' (ASCII value 48),
                 since digit values start at 48 on ASCII table
                 */
                if (toupper(pollData.at(p + 3)) == toupper(party))
                    voteTally += (pollData.at(p) - '0');
                
                p += 4;
            }
            /* checks case of two digits (representing a state having double-digit electoral votes)
             preceding a state code, do not need to check other cases because pollData is already
             verified to be syntactically correct and the case of a state forecast predicting
             0 electoral votes has already been accounted for
             */
            else
            {
                /* convert char to int by subtracting '0' (ASCII value 48),
                 since digit values start at 48 on ASCII table
                 */
                if (toupper(pollData.at(p + 4)) == toupper(party))
                    voteTally += ((pollData.at(p) - '0') * 10 + (pollData.at(p + 1) - '0'));
                
                p += 5;
            }
        }
    }
    return 0;
}

int main()
{
    string s = "14NJD55CAP";
    int v = 98989;
    bool b = isSyntacticallyCorrect(s);
    int n = tallyVotes("", ' ', v);
    cout << s << endl;
    cout << "Is syntactically correct: ";
    if (b)
        cout << "True" << endl;
    else
        cout << "False" << endl;
    cout << "Vote tally: " << v << endl << "Exit code: " << n << endl;
}
