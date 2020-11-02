//
//  main.cpp
//  Midterm
//
//  Created by Evan He on 10/29/20.
//  Copyright © 2020 Evan He. All rights reserved.
//

#include <iostream>
#include <cctype>
#include <string>

using namespace std;

int main()
{
    /*
    string s;
    getline(cin, s);
    
    for (int i = 0; i != s.size() - 1; i++)
    {
        if (isdigit(s.at(i)) && isupper(s.at(i + 1)))
        {
            cout << s.at(i) << endl;
        }
    }
    */
    /*
    string s = "";
    getline(cin, s);
    
    int numHyphens = s.size() - 1;
    for (int i = 0; i != s.size(); i++)
    {
        for (int j = numHyphens; j >= 1; j--)
        {
            cout << "-";
        }
        
        numHyphens--;
        cout << s.at(i) << endl;
    }
    */
    /*
    int n = 0;
    string s = "";
    
    cin >> n;
    cin.ignore(10000, '\n');
    
    getline(cin, s);
    
    int startPos = 0;
    
    for (int i = 1; i <= n; i++)
    {
        for (int j = startPos; j < s.size(); j += n)
        {
            cout << s.at(j);
        }
        startPos++;
        cout << endl;
    }
    */
}
