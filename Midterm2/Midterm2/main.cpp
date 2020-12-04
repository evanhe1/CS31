//
//  main.cpp
//  Midterm2
//
//  Created by Evan He on 11/24/20.
//  Copyright © 2020 Evan He. All rights reserved.
//

#include <iostream>
#include <cctype>
#include <cstring>

using namespace std;


int hideNonDigits(char s[], char ch)
{
    int numReplaced = 0;
    
    for (int i = 0; s[i] != '\0'; i++)
    {
        if (!isdigit(s[i]))
        {
            s[i] = ch;
            numReplaced++;
        }
    }
    
    return numReplaced;
}

int process(int changes[], int n, int& maxLead)
{
    int bennyLead = 30;
    int maxLeadAtStart = maxLead;
    
    if (n <= 0)
        return -3;
    
    for (int i = 0; i < n; i++)
    {
        if (changes[i] < -15 || changes[i] > 15)
        {
            maxLead = maxLeadAtStart;
            return -2;
        }
        
        bennyLead += changes[i];
        
        if (bennyLead < 0)
        {
            maxLead = maxLeadAtStart;
            return -1;
        }
        
        if (bennyLead > maxLead)
            maxLead = bennyLead;
    }
    
    return bennyLead;
}

int main() {
    char text[100] = "It's November 24, 2020";
    int n = hideNonDigits(text, '*');
    cout << n << ": " << text << endl;

    assert(hideNonDigits(text, '*') == 16);
    assert(strcmp(text, "**************24**2020") == 0);
    
    strcpy(text, "Wow!");
    assert(hideNonDigits(text, '-') == 4);
    assert(strcmp(text, "----") == 0);
    
    strcpy(text, "1984");
    assert(hideNonDigits(text, '?') == 0);
    assert(strcmp(text, "1984") == 0);
    
    strcpy(text, "");
    assert(hideNonDigits(text, 'X') == 0);
    assert(strcmp(text, "") == 0);
    
    strcpy(text, "\n\n\n\n\n\n");
    assert(hideNonDigits(text, 'X') == 6);
    assert(strcmp(text, "XXXXXX") == 0);
    
    strcpy(text, "     1");
    assert(hideNonDigits(text, '\0') == 5);
    assert(strcmp(text, "") == 0);
    
    cout << "All tests succeeded" << endl;
    
    int chg1[14] = { 5, 2, 0, -3, 6, 2, -4, 0, 0, -5, -5, 1, -8 , 20};
    int m = -1;
    assert(process(chg1, 14, m) == -2);
    cerr << m << endl;
    assert(m == -1);
    
    int chg2[7] = { 0, 2, -12, -9, -13, 10, 10 };
    m = 999;
    assert(process(chg2, 5, m) == -1);
    assert(m == 999);
    
    int chg3[3] = { 10, 20, 10 };
    m = 999;
    assert(process(chg3, 3, m) == -2);
    assert(m == 999);
    
    int chg4[3] = { 10, 20, 10 };
    m = 999;
    assert(process(chg4, 0, m) == -3);
    assert(m == 999);
    
    cout << "All tests succeeded" << endl;
}
