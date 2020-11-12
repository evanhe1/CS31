//
//  array.cpp
//  Project4
//

#include <iostream>
#include <string>
#include <cassert>

using namespace std;

// Append value to the end of each of the n elements of the array and return n.
int appendToAll(string a[], int n, string value)
{
    // return -1 if input indicates to consider a negative number of array elements
    if (n <= -1)
        return -1;
    
    // loop through all indexes of a[] that are less than n and append value to each one
    for (int i = 0; i != n; i++)
    {
        a[i] += value;
    }
    
    return n;
}

/* Return the position of a string in the array that is equal to target;
 if there is more than one such string, return the smallest position number
 of such a matching string. Return -1 if there is no such string.
 */
int lookup(const string a[], int n, string target)
{
    // return -1 if input indicates to consider zero or less array elements
    if (n <= 0)
        return -1;
    
    // iterate through each term in a[]
    for (int i = 0; i != n; i++)
    {
        // if target is the empty string, check if string at a[i] has length 0 and is therefore a match
        if (target == "" && a[i].size() == 0)
            return i;
        
        // return the index of the first match to target
        if (a[i] == target)
            return i;
    }
    
    // if execution reaches this point, no match would have been found
    return -1;
}

/* Return the position of a string in the array such that that string is >= every string in the array.
 If there is more than one such string, return the smallest position number of such a string.
 Return -1 if the array has no interesting elements.
 */
int positionOfMax(const string a[], int n)
{
    // return -1 if input indicates to consider zero or less array elements
    if (n <= 0)
        return -1;
    
    int posMax = 0;
    
    /* iterate through array and update posMax if the string at index i is greater than
     the string previously stored at posMax
     */
    for (int i = 1; i != n; i++)
    {
        if (a[i] > a[posMax])
            posMax = i;
    }
    
    return posMax;
}

/* Elmininate the item at position pos by copying all elements after it one place to the left.
 Put the item that was thus eliminated into the last position of the array.
 */
int rotateLeft(string a[], int n, int pos)
{
    // return -1 if input indicates to consider a negative number of array elements
    if (n <= -1)
        return -1;
    
    // return -1 if input indicates to consider a negative position in the array
    if (pos <= -1)
        return -1;
    
    /* return -1 if input indicates to consider an array element beyond the last element
    that the program is interested in
     */
    if (pos >= n)
        return -1;
    
    // removedString stores the value of the string to be overwritten and reinserted at the end of the array
    string removedString = a[pos];
    
    /* currentElement and nextElement respectively track the element at the index
     which the loop is currently processing and the subsequent element, and are initialized
     with the values of the penultimate and final elements of a[]
     */
    string currentElement = a[n - 2];
    string nextElement = a[n - 1];
    
    // shifts each element in a[] to the left while leaving the final element unchanged
    for (int i = n - 2; i >= pos; i--)
    {
        a[i] = nextElement;
        nextElement = currentElement;
        
        // if condition to prevent out of bounds error
        if (i > pos)
            currentElement = a[i - 1];
    }
    
    // reinsertes removedString at index n - 1 (the final index) of a[]
    a[n - 1] = removedString;
    
    return pos;
}

// Return the number of sequences of one or more consecutive identical items in a.
int countRuns(const string a[], int n)
{
    // return -1 if input indicates to consider a negative number of array elements
    if (n <= -1)
        return -1;
    // return 0 if input indicates to consider zero array elements
    if (n == 0)
        return 0;
    
    int numRuns = 1;
    
    /* iterate n - 1 times through the array and compare the element at position i
     with the preceding element; if the two are different, this indicates that a run has concluded
     and to add one to numRuns
     */
    for (int i = 1; i != n; i++)
    {
        if (a[i] != a[i - 1])
        {
            numRuns++;
        }
    }
    
    return numRuns;
}

// Reverse the order of the elements of the array and return n.
int flip(string a[], int n)
{
    // return -1 if input indicates to consider a negative number of array elements
    if (n <= -1)
        return -1;
    
    /* iterate through first n / 2 - 1 elements of a[]; if a[] has an odd number of elements,
    the middle element will simply be ignored by the loop
     */
    for (int i = 0; i != n / 2; i++)
    {
        string temp = a[i];
        a[i] = a[n - 1 - i];
        a[n - 1 - i] = temp;
    }
    
    return n;
}

/* Return the position of the first corresponding elements of a1 and a2 that are not equal.
 n1 is the number of interesting elements in a1, and n2 is the number of interesting elements in a2.
 If the arrays are equal up to the point where one or both runs out,
 return whichever value of n1 and n2 is less than or equal to the other.
*/
 
int differ(const string a1[], int n1, const string a2[], int n2)
{
    // return -1 if input indicates to consider a negative number of elements in either array
    if (n1 <= -1 || n2 <= -1)
        return -1;
    
    // set nShorter to the length of the shorter array if there is a length difference between the arrays
    int nShorter;
    if (n1 < n2)
        nShorter = n1;
    else
        nShorter = n2;
    
    // compare elements at index i in a1 and a2 for value equivalence
    for (int i = 0; i != nShorter; i++)
    {
        if (a1[i] != a2[i])
        {
            return i;
        }
    }
    
    // at this point, the shorter array will have run out, so return its length
    return nShorter;
}

/* if all n2 elements of a2 appear in a1, consecutively and in the same order, then return the position in a1 where that subsequence begins. If the subsequence appears more than once in a1, return the smallest such beginning position in the array. Return -1 if a1 does not contain a2 as a contiguous subsequence.
 */
int subsequence(const string a1[], int n1, const string a2[], int n2)
{
    // return -1 if input indicates to consider a negative number of elements in either array
    if (n1 <= -1 || n2 <= -1)
        return -1;
    
    // return -1 if input indicates to consider more elements of a2 than a1
    if (n2 > n1)
        return -1;
    
    /* return 0 if input indicates to consider 0 elements of a2,
     as it is a subsequence of any sequence starting at position 0
     (n2 is already confirmed to be <= n1)
     */
    if (n2 == 0)
        return 0;
    
    // iterate through first n1 - n2 + 1 elements of a1[] (to prevent out of bounds error)
    for (int i = 0; i <= n1 - n2; i++)
    {
        /* beginning with element i in a1 and element 0 in a2, check next n2 elements in each array to
         see if the elements match
         */
        for (int j = i; j != i + n2; j++)
        {
            if (a1[j] != a2[j - i])
                break;
            if (j == i + n2 - 1)
                return i;
        }
        
    }
    // if execution reaches this point, no match would have been found
    return -1;
}

/* Return the smallest position in a1 of an element that is equal to any of the n2 elements in a2.
 Return -1 if no element of a1 is equal to any element of a2.
 */
int lookupAny(const string a1[], int n1, const string a2[], int n2)
{
    /* return -1 if input indicates to consider zero or fewer elements in either array,
     since it would be impossible for a match to exist
     */
    if (n1 <= 0 || n2 <= 0)
        return -1;
    
    // iterate through n1 elements of a1[]
    for (int i = 0; i != n1; i++)
        // iterate through n2 elements of a2[]
        for (int j = 0; j != n2; j++)
        {
            /* compare if the element at index i in a1 is equal to the element at index j in a2,
             return index of first match in a1
             */
            if (a1[i] == a2[j])
                return i;
            
            /* compare if both the element at index i in a1 and the element at index j in a2 are of length 0,
             and are therefore both the empty string; return location of said empty string in a1
             */
            else if (a1[i].size() == 0 && a2[j].size() == 0)
                return i;
        }
     // if execution reaches this point, no match would have been found
    return -1;
}

/* Rearrange the elements of the array so that all the elements whose value is < divider come
 before all the other elements and all the elements whose value is > divider
 come after all the other elements. Return the position of the first element that,
 after the rearrangement, is not < divider, or n if there are no such elements.
 */
int divide(string a[], int n, string divider)
{
    // return -1 if input indicates to consider a negative number of array elements
    if (n <= -1)
        return -1;
    
    // return 0 if input indicates to consider zero array elements
    if (n == 0)
        return 0;
    
    // basic selection sort implementation
    int indexOfMin;
    
    // iterate through n elements of a
    for (int i = 0; i != n - 1; i++)
    {
        // assume first element is min
        indexOfMin = i;
        // iterate through all elements of a with an index greater than i
        for (int j = i + 1; j != n; j++)
        {
            /* if the element at position j in a is the empty string and
             the element at position i is not the empty string, set indexOfMin to the
             index of the element at position j
             */
            if (a[j].size() == 0 && a[i].size() != 0)
            {
                indexOfMin = j;
            }
            /* if another element is less than the min so far, set
             indexOfMin to the index of that element
             */
            else if (a[indexOfMin] > a[j])
            {
                indexOfMin = j;
            }
        }
        
        /* if the index of the min is no longer the same as the initial index,
         swap the elements at the two locations
         */
        if (indexOfMin != i)
        {
            string temp = a[indexOfMin];
            a[indexOfMin] = a[i];
            a[i] = temp;
        }
    }
    
    // return index of the first element whose value is >= divider, if present
    for (int i = 0; i != n; i++)
    {
        if (a[i] >= divider)
            return i;
    }
    
    return n;
}

int main() {
    /*
    string h[7] = { "martha", "mark", "joe", "susan", "", "kamala", "lindsey" };
    assert(lookup(h, 7, "kamala") == 5);
    assert(lookup(h, 7, "joe") == 2);
    assert(lookup(h, 2, "joe") == -1);
    assert(positionOfMax(h, 7) == 3);
    
    string g[4] = { "martha", "mark", "lindsey", "sara" };
    assert(differ(h, 4, g, 4) == 2);
    assert(appendToAll(g, 4, "?") == 4 && g[0] == "martha?" && g[3] == "sara?");
    assert(rotateLeft(g, 4, 1) == 1 && g[1] == "lindsey?" && g[3] == "mark?");
    
    string e[4] = { "joe", "susan", "", "kamala" };
    assert(subsequence(h, 7, e, 4) == 2);
    
    string d[5] = { "mark", "mark", "mark", "susan", "susan" };
    assert(countRuns(d, 5) == 2);
    
    string f[3] = { "lindsey", "joe", "mike" };
    assert(lookupAny(h, 7, f, 3) == 2);
    assert(flip(f, 3) == 3 && f[0] == "mike" && f[2] == "lindsey");
    
    assert(divide(h, 7, "lindsey") == 3);
    
    cerr << "All tests succeeded" << endl;
    
    string emptyArray1[0] = {};
    assert(appendToAll(emptyArray1, 0, "p") == 0);
    string a1[4] = {"cairnsmore", "cheshire", "lancashire", "swaledale"};
    assert(appendToAll(a1, 0, "!!!") == 0);
    assert(appendToAll(a1, -2, "!!!") == -1);
    assert(appendToAll(a1, 4, "!!!") == 4);
    //for (int i = 0; i != 4; i++)
        //cerr << a1[i] << " ";
    //cerr << endl;
    
    string a2[5] = {"cairnsmore", "norbury blue", "cheshire", "cornish yarg", "lancashire"};
    assert(appendToAll(a2, 5, "") == 5);
    //for (int i = 0; i != 5; i++)
        //cerr << a2[i] << " ";
    //cerr << endl;
    assert(appendToAll(a2, 3, "??") == 3);
    //for (int i = 0; i != 3; i++)
        //cerr << a2[i] << " ";
    //cerr << endl;
    
    string emptyArray2[0] = {};
    assert(lookup(emptyArray2, 0, "cheshire") == -1);
    assert(lookup(emptyArray2, 0, "") == -1);
    string b1[6] = {"cairnsmore", "cheshire", "lancashire", "swaledale", "swaledale", ""};
    assert(lookup(b1, 0, "lancashire") == -1);
    assert(lookup(b1, 6, "lancashire") == 2);
    assert(lookup(b1, 6, "Lancashire") == -1);
    assert(lookup(b1, 6, "stilton") == -1);
    assert(lookup(b1, -4, "cheshire") == -1);
    assert(lookup(b1, 3, "swaledale") == -1);
    assert(lookup(b1, 6, "") == 5);
    assert(lookup(b1, 6, "swaledale") == 3);
    
    string emptyArray3[0] = {};
    assert(positionOfMax(emptyArray3, 0) == -1);
    string c1[6] = {"cheshire", "cornish yarg", "cairnsmore", "norbury blue", "", "lancashire"};
    assert(positionOfMax(c1, 0) == -1);
    assert(positionOfMax(c1, -5) == -1);
    assert(positionOfMax(c1, 6) == 3);
    assert(positionOfMax(c1, 3) == 1);
    string c2[5] = {"cheshire", "cheshire", "cheshire", "cheshire", "cheshire"};
    assert(positionOfMax(c2, 5) == 0);

    string emptyArray4[0] = {};
    assert(rotateLeft(emptyArray4, 0, 0) == -1);
    string d1[6] = {"a", "b", "c", "d", "e", "f"};
    assert(rotateLeft(d1, -5, 0) == -1);
    assert(rotateLeft(d1, 6, -5) == -1);
    assert(rotateLeft(d1, 6, 0) == 0);
    //for (int i = 0; i != 6; i++)
        //cerr << d1[i] << " ";
    //cerr << endl;
    
    string d2[6] = {"a", "b", "c", "d", "e", "f"};
    assert(rotateLeft(d2, 6, 5) == 5);
    //for (int i = 0; i != 6; i++)
        //cerr << d2[i] << " ";
    //cerr << endl;
    string d3[6] = {"a", "b", "c", "d", "e", "f"};
    assert(rotateLeft(d3, 6, 6) == -1);
    assert(rotateLeft(d3, 4, 2) == 2);
    //for (int i = 0; i != 4; i++)
        //cerr << d3[i] << " ";
    //cerr << endl;
    string d4[6] = {"a", "b", "c", "d", "e", "f"};
    assert(rotateLeft(d4, 1, 0) == 0);
    //for (int i = 0; i != 1; i++)
        //cerr << d4[i] << " ";
        //cerr << endl;
    
    string emptyArray5[0] = {};
    assert(countRuns(emptyArray5, 0) == 0);
    string e1[5] = {"cheshire", "cornish yarg", "cairnsmore", "norbury blue", "lancashire"};
    assert(countRuns(e1, 5) == 5);
    assert(countRuns(e1, -2) == -1);
    assert(countRuns(e1, 4) == 4);
    assert(countRuns(e1, 1) == 1);
    string e2[5] = {"cheshire", "cornish yarg", "cornish yarg", "cheshire", "cheshire"};
    assert(countRuns(e2, 5) == 3);
    assert(countRuns(e2, 4) == 3);
    assert(countRuns(e2, 3) == 2);
    string e3[5] = {"cheshire", "cornish yarg", "Cornish yarg", "cheshire", "cheshire"};
    assert(countRuns(e3, 5) == 4);
    string e4[5] = {"cheshire", "cheshire", "cheshire", "cheshire", "cheshire"};
    assert(countRuns(e4, 5) == 1);

    string emptyArray6[0] = {};
    assert(flip(emptyArray6, 0) == 0);
    string f1[5] = {"cheshire", "cornish yarg", "cairnsmore", "norbury blue", "lancashire"};
    assert(flip(f1, 0) == 0);
    assert(flip(f1, -5) == -1);
    assert(flip(f1, 5) == 5);
    //for (int i = 0; i != 5; i++)
        //cerr << f1[i] << " ";
        //cerr << endl;

    string f2[4] = {"cheshire", "cornish yarg", "cairnsmore", "norbury blue"};
    assert(flip(f2, 4) == 4);
    //for (int i = 0; i != 4; i++)
        //cerr << f2[i] << " ";
        //cerr << endl;
    string f3[5] = {"cheshire", "cornish yarg", "cairnsmore", "norbury blue", "lancashire"};
    assert(flip(f3, 3) == 3);
    //for (int i = 0; i != 3; i++)
        //cerr << f3[i] << " ";
        //cerr << endl;

    string f4[5] = {"", "", "", "", ""};
    assert(flip(f4, 5) == 5);
    //for (int i = 0; i != 5; i++)
        //cerr << f4[i] << "";
        //cerr << endl;
    
    string emptyArray7[0] = {};
    string emptyArray8[0] = {};
    assert(differ(emptyArray7, 0, emptyArray8, 0) == 0);
    string g1[5] = {"cheshire", "cornish yarg", "cairnsmore", "norbury blue", "lancashire"};
    assert(differ(g1, 5, g1, 4) == 4);
    assert(differ(g1, 5, g1, -2) == -1);
    string g2[4] = {"cheshire", "cornish yarg", "cairnsmore", "norbury blue"};
    assert(differ(g1, 5, g2, 4) == 4);
    assert(differ(g2, 4, g1, 5) == 4);
    assert(differ(g1, 4, g2, 0) == 0);
    string g3[5] = {"cheshire", "Cornish yarg", "cairnsmore", "norbury Blue", "lancashire"};
    assert(differ(g1, 5, g3, 5) == 1);
    string g4[4] = {"cornish yarg", "cairnsmore", "norbury blue", "stilton"};
    assert(differ(g1, 5, g4, 4) == 0);
    
    string emptyArray9[0] = {};
    string emptyArray10[0] = {};
    assert(subsequence(emptyArray9, 0, emptyArray10, 0) == 0);
    string h1[4] = {"I", "am", "the", "senate"};
    assert(subsequence(h1, 4, emptyArray9, 0) == 0);
    string h2[2] = {"the","senate"};
    assert(subsequence(h1, 4, h2, 2) == 2);
    assert(subsequence(h1, -4, h2, 2) == -1);
    assert(subsequence(h1, 3, h2, 2) == -1);
    assert(subsequence(h1, 3, h2, 1) == 2);
    assert(subsequence(h1, 1, h2, 2) == -1);
    string h3[1] = {"thesenate"};
    assert(subsequence(h1, 4, h3, 2) == -1);
    
    
    string emptyArray11[0] = {};
    string emptyArray12[0] = {};
    assert(lookupAny(emptyArray11, 0, emptyArray12, 0) == -1);
    string j1[6] = {"cornish yarg", "cairnsmore", "norbury blue", "norbury blue", "stilton", ""};
    string j2[5] = {"cheshire", "lancashire", "red windsor", "stilton", ""};
    assert(lookupAny(j1, 6, j2, 5) == 4);
    assert(lookupAny(j1, 4, j2, 5) == -1);
    assert(lookupAny(j2, 5, j1, 6) == 3);
    assert(lookupAny(j2, 5, j1, -5) == -1);
    assert(lookupAny(j2, 0, j1, 6) == -1);
    string j3[4] = {"", "", "", ""};
    assert(lookupAny(j1, 6, j3, 4) == 5);
    
    string emptyArray13[0] = {};
    assert(divide(emptyArray13, 0, "cheshire") == 0);
    string k1[8] = {"b", "c", "f", "", "a", "d", "d", "e"};
    assert(divide(k1, 8, "dorset blue vinney") == 6);
    assert(divide(k1, 8, "cheshire") == 4);
    assert(divide(k1, -7, "cheshire") == -1);
    assert(divide(k1, 2, "cheshire") == 2);
    assert(divide(k1, 3, "Cheshire") == 1);
    assert(divide(k1, 8, "lancashire") == 8);
    assert(divide(k1, 8, "") == 0)
    */
    cerr << "All tests succeeded" << endl;
}
