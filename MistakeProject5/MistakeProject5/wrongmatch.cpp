//
//  wrongmatch.cpp
//  Project5
//
// program works based on belief that 2-word rule checks if a word is in matches
//wordin and the next word does not match wordout

#include <iostream>
#include <cstring>
#include <cctype>

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
    /* create temporary arrays for program efficiency to reduce the number of traversals
     through original arrays when modifying them to only contain match rules in clean form,
     nextLocationInTemp indicates where to store next valid word rule
     */
    char tempWordin[nRules][MAX_WORD_LENGTH + 1];
    char tempWordout[nRules][MAX_WORD_LENGTH + 1];
    int nextLocationInTemp = 0;
    
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
                    // check if element at wordin[i] does not already appear in tempWordin
                    int j;
                    for (j = 0; j < nRules; j++)
                        if (strcmp(wordin[i], tempWordin[j]) == 0)
                            break;
                    
                    /* at this point all criteria are satisfied for a valid, non-duplicate one-word rule
                     so wordin[i] is stored at the next available location with an undefined
                     value in tempWordIn, and wordout[i] (guarenteed to be the empty string) is stored
                     at the next available location with an undefined value in tempWordout
                     */
                    if (j == nRules)
                    {
                        strcpy(tempWordin[nextLocationInTemp], wordin[i]);
                        strcpy(tempWordout[nextLocationInTemp], wordout[i]); /* wordout[i] is empty string */
                        nextLocationInTemp++;
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
             because although all letters in wordin[i] are now lowercase, there could still be be
             nonletter characters in the string)
             */
            if (isOnlyLowerCase(wordin[i]) && isOnlyLowerCase(wordout[i]))
            {
                // check if the corresponding elements at index i in wordin and wordout are not the same
                if (strcmp(wordin[i], wordout[i]) != 0)
                {
                    int k;
                    for (k = 0; k < nRules; k++)
                    {
                        /* check if element at wordin[i] does not already appear in tempWordin as part of a
                         a one-word rule (wordin[i] is present is tempWordin and tempWordout[i] is the empty
                         string)
                         */
                        if (strcmp(wordin[i], tempWordin[k]) == 0 && strlen(tempWordout[k]) == 0)
                            break;
                        /* check if element at wordin[i] does not already appear in tempWordin as part of a
                         an identical two-word rule (wordin[i] is present is tempWordin and tempWordout[i] is the empty
                         string)
                         */
                        if (strcmp(wordin[i], tempWordin[k]) == 0 && strcmp(wordout[i], tempWordout[k]) == 0)
                            break;
                    }
                    
                    /* at this point all criteria are satisfied for a valid, non-duplicate two-word rule
                     that does not also overlap with a pre-existing one-word rule, so wordin[i] is stored
                     at the next available location with an undefined value in tempWordin, and wordout[i]
                     is stored at the next available location with an undefined value in tempWordout
                     */
                    if (k == nRules)
                    {
                        strcpy(tempWordin[nextLocationInTemp], wordin[i]);
                        strcpy(tempWordout[nextLocationInTemp], wordout[i]);
                        nextLocationInTemp++;
                    }
                }
            }
        }
    }
    
    // copy elements into tempWordin and tempWordout into wordin and wordout respectively
    for (int i = 0; i < nRules; i++)
    {
        strcpy(wordin[i], tempWordin[i]);
        strcpy(wordout[i], tempWordout[i]);
    }
    
    /* returns nextLocationInTemp, which is eqaul to the length of the temporary arrays and therefore
     the number of word rules in clean form
     */
    return nextLocationInTemp;
}

int determineScore(const char document[], const char wordin[][MAX_WORD_LENGTH + 1], const char wordout[][MAX_WORD_LENGTH + 1], int nRules)
{
    /* matchesRules is an array of bool that tracks which word rules that document matches, by default
     all values in the array are set to false, array will not be modified until near the end of the program,
     initialized here to draw attention
     */
    bool matchesRules[MAX_DOCUMENT_LENGTH + 1] = {false};
    
    // currentWord and nextWord are temporary words that will be used to compare with match rules
    char currentWord[MAX_DOCUMENT_LENGTH + 1];
    char nextWord[MAX_DOCUMENT_LENGTH + 1];
    
    /* iterate through all non-alphabetic characters before first word, in case of document with only
     non-alphabetic characters, iterate straight through the end of the document,
     variable i represents the next character of interest in document
     */
    int i = 0;
    while (!isalpha(document[i]))
    {
        i++;
    }
    
    // initial reading of currentWord as first word in the document
    int j = 0; // j tracks next position of interest in currentWord
    
    // while the next character of interest is not a space or newline
    while (!isspace(document[i]) && document[i] != '\0')
    {
        // if the character at index i in document is a letter, store that character at index j, and increment j
        if (isalpha(document[i]))
        {
            currentWord[j] = tolower(document[i]);
            j++;
        }
        i++;
        
        /* at this point in execution, i and j will both be 1 greater than at the beginning of this loop iteration,
         if the character at position i in document is a space or the zero byte, set the character at position k in
         currentWord to the zero byte, marking the end of the string
         */
        if (isspace(document[i]) || document[i] == '\0')
        {
            currentWord[j] = '\0';
        }
    }
    
    while (i < strlen(document))
    {
        /* iterate through all non-alphabetic characters between words to arrive
         at beginning of next word or the null byte
         */
        while (!isalpha(document[i]))
        {
            i++;
        }
        
        int k = 0; // k tracks next position of interest in nextWord
        
        // while the next character of interest is not a space or newline
        while (!isspace(document[i]) && document[i] != '\0')
        {
            // if the character at index i in document is a letter, store that character at index k, and increment k
            if (isalpha(document[i]))
            {
                nextWord[k] = tolower(document[i]);
                k++;
            }
            i++;
            
            /* at this point in execution, i and k will both be 1 greater than at the beginning of this loop iteration,
             if the character at position i in document is a space or the zero byte, set the character at position k in
             nextWord to the zero byte, marking the end of the string
             */
            if (isspace(document[i]) || document[i] == '\0')
            {
                nextWord[k] = '\0';
            }
        }
        
        /* execution will only reach this point if there are additional non-alphabetic characters
         between last word and document's final null byte, this code allows the while loop to
         terminate properly
         */
        while (!isalpha(document[i]))
        {
            i++;
        }
        
        cerr << currentWord << endl;
        cerr << nextWord << endl << endl;
        
        /* if currentWord and nextWord match wordin[m] and wordout[m] respectively as part of a two-word rule,
         or otherwise if currentWord alone matches wordin[m] as part of a one-word rule, change matchesRules[m],
         prevents double counting the match if multiple instances of the match occur throughout document
         */
        for (int m = 0; m < nRules; m++)
        {
            if (strcmp(currentWord, wordin[m]) == 0)
            {
                if (strlen(wordout[m]) == 0)
                    matchesRules[m] = true;
                else if (strcmp(nextWord, wordout[m]) == 0)
                    matchesRules[m] = true;
            }
        }
        
        strcpy(currentWord, nextWord);
    }
    
    /* score variable will track how many matches document contains with the word rule, as indicated in the
     matchesRules array, socre will increment if the element at index m in matchesRules is true
     */
    int score = 0;
    for (int p = 0; p < nRules; p++)
    {
        if (matchesRules[p])
            score++;
    }
    
    return score;
}

int main()
{
    int n = 3;
    char pee[] = "Happy families are all alike; every unhappy family is unhappy in its own way.";
    char win[][MAX_WORD_LENGTH + 1] = {"family", "unhappy", "horse"};
    char wout[][MAX_WORD_LENGTH + 1] = {"", "horse", ""};
    int a = cleanupRules(win, wout, n);
    
    cerr << a << endl;
    
    for (int i = 0; i < n; i++)
    {
        cerr << win[i] << '\t' << wout[i] << endl;
    }
    
    int b = determineScore(pee, win, wout, n);
    cerr << b << endl;
    
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
