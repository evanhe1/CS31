//
//  main.cpp
//  Project6
//
//  Created by Evan He on 11/28/20.
//  Copyright © 2020 Evan He. All rights reserved.
//

#include <iostream>
using namespace std;

void removeS(char* c)
{
    char* rotatePtr; // used to shift characters leftward to overwrite any 's' or 'S' characters found
    while (*c != 0)
    {
        /* if an 's' or 'S' is found, shift all elements that come after the match to the left by one index,
         if this process results in another 's' or 'S' occupying the index where the match was previously found
         (there were consecutive 's' or 'S' characters in the original string), repeat the shifting process until
         index no longer contains an 's' or 'S' character
         */
        while (*c == 's' || *c == 'S')
        {
            rotatePtr = c;
            while (*rotatePtr != 0)
            {
                *rotatePtr = *(rotatePtr + 1);
                rotatePtr++;
            }
        }
        c++;
        rotatePtr = c;
    }
}

int main()
{
    char msg[50] = "She'll be a massless princesssssssssss.";
    removeS(msg);
    cout << msg;  // prints   he'll be a male prince.
}

