#include <iostream>
#include <string>

#pragma once

using namespace std;

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