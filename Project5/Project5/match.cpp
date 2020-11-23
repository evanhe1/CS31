//
//  match.cpp
//  Project5
//

#include <iostream>
#include <cstring>
#include <cctype>
#include <cassert>

using namespace std;

const int MAX_WORD_LENGTH = 20;
const int MAX_DOCUMENT_LENGTH = 250;

bool isOnlyLowerCase(char s[])
{
    if (strlen(s) <= 0)
        return false;
    
    for (int i = 0; i < strlen(s); i++)
        if (!islower(s[i]))
            return false;
    
    return true;
}

int cleanupRules(char wordin[][MAX_WORD_LENGTH + 1], char wordout[][MAX_WORD_LENGTH + 1], int nRules)
{
    // return 0 if parameter indicates to check 0 or less match rules
    if (nRules <= 0)
        return 0;
    
    /* iterate through both wordin and wordout and transform every uppercase letter
     in the match rule words into their lowercase counterparts
     */
    for (int i = 0; i < nRules; i++)
    {
        for (int j = 0; j < strlen(wordin[i]); j++)
        {
            wordin[i][j] = tolower(wordin[i][j]);
        }
        
        for (int k = 0; k < strlen(wordout[i]); k++)
        {
            wordout[i][k] = tolower(wordout[i][k]);
        }
    }
    
    /* nextLocationToStore tracks the next index in wordin and wordout that does not already contain a processed
     word rule
     */
    int nextLocationToStore = 0;
    
    // this loop will properly process all potential one-word rules
    for (int i = 0; i < nRules; i++)
    {
        // check if wordin[i] is not empty string
        if (strlen(wordin[i]) > 0)
        {
            /* check if all characters in wordin[i] are lowercase letters (this check is necessary
             because although all letters in wordin[i] are now lowercase, there could still be be
             nonletter characters in the string)
             */
            if (isOnlyLowerCase(wordin[i]))
            {
                // check if elements in wordin and wordout at index i constitute potential one-word rule
                if (strlen(wordout[i]) == 0)
                {
                    /* check if element at wordin[i] has already been processed as part of a one-word rule (moved
                     to the front of wordin), every element coming before wordin[nextLocationToStore] is an element
                     in clean form, so a match would indicate that the element at wordin[i] is a duplicate
                     */
                    int j;
                    for (j = 0; j < nextLocationToStore; j++)
                        if (strcmp(wordin[i], wordin[j]) == 0)
                            break;
                    
                    /* at this point all criteria are satisfied for a valid, non-duplicate one-word rule
                     so all elements between indices nextLocationToStore and i (the index of the newly found
                     word rule in clean form) in wordin and wordout are shifted over one to the right before
                     wordin[i] and wordout[i] (which is guarenteed to be the empty string) are reinserted into
                     their repsective arrays at index nextLocationToStore, nextLocationToStore is then incremented
                     
                     this process is analogous to a rotateRight function in Project 4
                     */
                    if (j == nextLocationToStore)
                    {
                        /* nextWordinElementToMove and nextWordoutElementToMove are char arrays that will serve as
                         temporary arrays to store a newly found clean form word rule while other elements are
                         shifted so the word rule can be stored in front of all unprocessed elements
                         */
                        char nextWordinElementToMove[MAX_WORD_LENGTH + 1];
                        char nextWordoutElementToMove[MAX_WORD_LENGTH + 1];
                        
                        strcpy(nextWordinElementToMove, wordin[i]);
                        strcpy(nextWordoutElementToMove, wordout[i]);
                        for (int p = i - 1; p >= nextLocationToStore; p--)
                        {
                            strcpy(wordin[p + 1], wordin[p]);
                            strcpy(wordout[p + 1], wordout[p]);
                        }
                        
                        strcpy(wordin[nextLocationToStore], nextWordinElementToMove);
                        strcpy(wordout[nextLocationToStore], nextWordoutElementToMove);
                        
                        nextLocationToStore++;
                    }
                }
            }
        }
    }
    
    /* this loop will properly process all potential two-word rules, while accounting for previously
     processed one-word rules
     */
    for (int i = 0; i < nRules; i++)
    {
        // check if wordin[i] and wordout[i] are not empty string
        if (strlen(wordin[i]) > 0 && strlen(wordout[i]) > 0)
        {
            /* check if all characters in wordin[i] and wordout[i] are lowercase letters (this check is necessary
             because although all letters in wordin[i] are now lowercase, there could still be be nonletter
             characters in the string)
             */
            if (isOnlyLowerCase(wordin[i]) && isOnlyLowerCase(wordout[i]))
            {
                // check if the corresponding elements at index i in wordin and wordout are not the same
                if (strcmp(wordin[i], wordout[i]) != 0)
                {
                    int k;
                    for (k = 0; k < nextLocationToStore; k++)
                    {
                        /* check if element at wordin[i] has not already been processed as part of a one-word rule
                         (a match for wordin[i] occurs before index nextLocationToStore in wordin)
                         */
                        if (strcmp(wordin[k], wordin[i]) == 0 && strlen(wordout[k]) == 0)
                            break;
                        /* check if element at wordin[i] and wordout[i] has not already been processed as part of
                         an identical two-word rule (a match for wordout occurs before index nextLocationToStore
                         in wordout, at this point in execution wordout[i] is already guarenteed to not be the
                         empty string)
                         */
                        if (strcmp(wordin[k], wordin[i]) == 0 && strcmp(wordout[k], wordout[i]) == 0)
                            break;
                    }
                    
                    /* at this point all criteria are satisfied for a valid, non-duplicate two-word rule
                     that does not also overlap with a pre-existing one-word rule, so all elements between
                     indices nextLocationToStore and i (the index of the newly found word rule in clean form)
                     in wordin and wordout are shifted over one to the right before wordin[i] and wordout[i]
                     are reinserted into their repsective arrays at index nextLocationToStore, nextLocationToStore
                     is then incremented
                     
                     this process is analogous to a rotateRight function in Project 4
                     */
                    if (k == nextLocationToStore)
                    {
                        /* nextWordinElementToMove and nextWordoutElementToMove are char arrays that will serve as
                         temporary arrays to store a newly found clean form word rule while other elements are
                         shifted so the word rule can be stored in front of all unprocessed elements
                         */
                        char nextWordinElementToMove[MAX_WORD_LENGTH + 1];
                        char nextWordoutElementToMove[MAX_WORD_LENGTH + 1];
                        
                        strcpy(nextWordinElementToMove, wordin[i]);
                        strcpy(nextWordoutElementToMove, wordout[i]);
                        for (int p = i - 1; p >= nextLocationToStore; p--)
                        {
                            strcpy(wordin[p + 1], wordin[p]);
                            strcpy(wordout[p + 1], wordout[p]);
                        }
                        
                        strcpy(wordin[nextLocationToStore], nextWordinElementToMove);
                        strcpy(wordout[nextLocationToStore], nextWordoutElementToMove);
                        
                        nextLocationToStore++;
                    }
                }
            }
        }
    }
    
    /* returns nextLocationToStore, which is equal to the length of the temporary arrays and therefore
     the number of word rules in clean form
     */
    return nextLocationToStore;
}

int determineScore(const char document[], const char wordin[][MAX_WORD_LENGTH + 1], const char wordout[][MAX_WORD_LENGTH + 1], int nRules)
{
    // score variable will track how many matches document contains with the word rule
    int score = 0;
    
    /* matchesWordin is an array of bool that tracks which elements of wordin that document matches, by default
     all values in the array are set to false, array will not be modified until near the end of the program,
     initialized here to draw attention
     */
    bool matchesWordin[MAX_DOCUMENT_LENGTH + 1] = {false};
    
    /* matchesWordout is an array of bool that tracks which elements of wordout that document matches, by default
     all values in the array are set to false, array will not be modified until near the end of the program,
     initialized here to draw attention
     */
    bool matchesWordout[MAX_DOCUMENT_LENGTH + 1] = {false};
    
    // currentWord is a temporary word that will be used to compare with match rules
    char currentWord[MAX_DOCUMENT_LENGTH + 1] = {};
    
    // variable i represents the next character of interest in document
    int i = score;
    
    while (i < strlen(document))
    {
        /* iterate through all non-alphabetic characters between words to arrive
         at the beginning of next word or the null byte, in case of document with only
         non-alphabetic characters, iterate straight through the end of the document
         */
        while (!isalpha(document[i]))
        {
            i++;
            // if condition ensures that execution exists loop condition at correct time
            if (i == strlen(document))
                break;
        }
        
        int j = 0; // j tracks next position of interest in currentWord
        
        /* while the next character of interest is not a space and the next element is in bounds
         (i would currently be in an out of bounds position if document had only contained nonletter characters)
         */
        while (!isspace(document[i]) && i < strlen(document))
        {
            // if the character at index i in document is a letter, store that character at index j, and increment j
            if (isalpha(document[i]))
            {
                currentWord[j] = tolower(document[i]);
                j++;
            }
            i++;
            
            /* at this point in execution, i and j will both be 1 greater than at the beginning of this loop
             iteration, if the character at position i in document is a space or the zero byte, set the character
             at position k in currentWord to the zero byte, marking the end of the string
             */
            if (isspace(document[i]) || document[i] == '\0')
            {
                currentWord[j] = '\0';
            }
        }
        
        /* if currentWord matches wordin[m] or wordout[m], indicate this fact by setting matchesWordin[m]
         or matchesWordout[m] to true, the use of the array prevents double counting multiple instances of
         a match with a same word rule
         */
        for (int m = 0; m < nRules; m++)
        {
            if (strcmp(currentWord, wordin[m]) == 0)
                matchesWordin[m] = true;
            if (strcmp(currentWord, wordout[m]) == 0)
                matchesWordout[m] = true;
        }
    }
    
    /* iterate through the matchesWordin and matchesWordout arrays, if the element at index p in matchesWordin
     is true and the element at index p in matchesWordout is false, increment score (these conditions apply for both
     one-word and two-word rules since a one-word rule match only depends on finding a match in the
     wordin array; the wordout array does not matter)
     */
    for (int p = 0; p < nRules; p++)
    {
        if (matchesWordin[p] && !matchesWordout[p])
            score++;
    }
    
    return score;
}

int main()
{
    
    char win1[][MAX_WORD_LENGTH + 1] = {"", "cat", "horse", "big", "Horse", "hoRse", "bear!", "tiger", "cat", "small", "rat", "aaaaaaaaaaaaaaaaaaaa", "bbbbbbbbbbbbbbbbbbbb", "cat", "horse"};
    char wout1[][MAX_WORD_LENGTH + 1] = {"pig", "", "big", "horse", "TRUck", "", "", "li0n", "", "horse", "rat", "bbbbbbbbbbbbbbbbbbbb", "", "", "big"};
    
    //assert(cleanupRules(win1, wout1, -1) == 0);
    //assert(cleanupRules(win1, wout1, 0) == 0);
    //assert(cleanupRules(win1, wout1, 1) == 0);
    //assert(cleanupRules(win1, wout1, 2) == 1);
    //assert(cleanupRules(win1, wout1, 3) == 2);
    //assert(cleanupRules(win1, wout1, 4) == 3);
    //assert(cleanupRules(win1, wout1, 5) == 4);
    //assert(cleanupRules(win1, wout1, 6) == 3);
    //assert(cleanupRules(win1, wout1, 7) == 3);
    //assert(cleanupRules(win1, wout1, 8) == 3);
    //assert(cleanupRules(win1, wout1, 9) == 3);
    //assert(cleanupRules(win1, wout1, 10) == 4);
    //assert(cleanupRules(win1, wout1, 11) == 4);
    //assert(cleanupRules(win1, wout1, 12) == 5);
    //assert(cleanupRules(win1, wout1, 13) == 6);
    //assert(cleanupRules(win1, wout1, 14) == 6);
    assert(cleanupRules(win1, wout1, 15) == 6);
    
    char win2[][MAX_WORD_LENGTH + 1] = {"confusion", "FAMILY", "charm", "hearty", "house", "worn-out", "family", "charm", "ties", "", "charm", "FaMiLy"};
    char wout2[][MAX_WORD_LENGTH + 1] = {"", "TIES", "confusion", "hearty", "intrigue", "younger", "first", "", "family", "frightened", "", "tIeS"};
    
    
    assert(cleanupRules(win2, wout2, 11) == 6);
    
    char win3[][MAX_WORD_LENGTH + 1] = {"big", "dog", "big"};
    char wout3[][MAX_WORD_LENGTH + 1] = {"horse", "", "house"};
    cleanupRules(win3, wout3, 3);
    
    assert(determineScore("I like dog", win3, wout3, -1) == 0);
    assert(determineScore("I like dog", win3, wout3, 0) == 0);
    assert(determineScore("", win3, wout3, 2) == 0);
    assert(determineScore(" !@#$%^&*() ", win3, wout3, 2) == 0);
    assert(determineScore("I like dog", win3, wout3, 2) == 1);
    assert(determineScore("I like big", win3, wout3, 2) == 1);
    assert(determineScore("I like big dog", win3, wout3, 2) == 2);
    assert(determineScore("I like BIG dog", win3, wout3, 2) == 2);
    assert(determineScore("I like B-I-G dog", win3, wout3, 2) == 2);
    assert(determineScore(" !@#$%^&*() I like big dog !@#$%^&*() ", win3, wout3, 2) == 2);
    assert(determineScore("I ^&*(&*() like     big    dog", win3, wout3, 2) == 2);
    assert(determineScore("Ilikebigdog", win3, wout3, 2) == 0);
    assert(determineScore("I like big, big dog", win3, wout3, 2) == 2);
    assert(determineScore("I like big dog dog", win3, wout3, 2) == 2);
    assert(determineScore("I like big horse", win3, wout3, 2) == 0);
    assert(determineScore("I like big horse", win3, wout3, 3) == 1);
    assert(determineScore("I like big dog", win3, wout3, 3) == 3);
    assert(determineScore("I like big ggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggg      ", win3, wout3, 3) == 2);
    
    const int TEST1_NRULES = 3;
    char test1win[TEST1_NRULES][MAX_WORD_LENGTH+1] = {
        "family", "unhappy", "horse",
    };
    char test1wout[TEST1_NRULES][MAX_WORD_LENGTH+1] = {
        "",       "horse",   "",
    };
    assert(determineScore("Happy families are all alike; every unhappy family is unhappy in its own way.",
                          test1win, test1wout, TEST1_NRULES) == 2);
    assert(determineScore("Happy horses are all alike; every unhappy horse is unhappy in its own way.",
                          test1win, test1wout, TEST1_NRULES-1) == 0);
    assert(determineScore("Happy horses are all alike; every unhappy horse is unhappy in its own way.",
                          test1win, test1wout, TEST1_NRULES) == 1);
    assert(determineScore("A horse!  A horse!  My kingdom for a horse!",
                          test1win, test1wout, TEST1_NRULES) == 1);
    assert(determineScore("horse:stable ratio is 10:1",
                          test1win, test1wout, TEST1_NRULES) == 0);
    assert(determineScore("**** 2020 ****",
                          test1win, test1wout, TEST1_NRULES) == 0);
    cout << "All tests succeeded" << endl;
}


