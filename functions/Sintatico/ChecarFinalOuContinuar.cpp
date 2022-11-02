#pragma once
#include <vector>
#include <string>
#include <iostream>

#include "SyntaticAnalyzer.h"
#include "RegraAtual.cpp"

using namespace std;

void ReconhecerFinalOuContinuar(vector<string> rule, int *string_stopped)
{
    if (*string_stopped >= rule.size())
    {
        *string_stopped = WAS_ENTIRE_COMMAND_VERIFIED;
        return;
    }
    if (rule[*string_stopped].compare("&") == 0)
    {
        return;
    }
    throw runtime_error("Esperando &");
}