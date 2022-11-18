#include <iostream>
#include <string>

#pragma once

using namespace std;

bool isNumber(string word)
{
    for (int i = 0; i < word.size(); i++)
    {
        if (i != 1 && !isdigit(word[i]))
        {
            return false;
        }
    }
    return true;
}

bool EveryLetterIsLower(string word)
{
    for (char letter : word)
    {
        if (isupper(letter))
        {
            return false;
        }
    }
    return true;
}