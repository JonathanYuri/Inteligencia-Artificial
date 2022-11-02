#pragma once
#include <vector>
#include <string>
#include <iostream>

#include "SyntaticAnalyzer.h"
#include "RegraAtual.cpp"

using namespace std;

void ReconhecerSe (vector<string> rule, int *string_stopped, int linha)
{
    if (*string_stopped >= rule.size())
    {
        throw runtime_error("Esperando uma expressao depois do 'SE'");
    }
    if (rule[*string_stopped].compare("SE") == 0)
    {
        *string_stopped += 1;
        ReconhecerVarNoSe(rule, string_stopped, linha, "");
        return;
    }
    throw runtime_error("Esperando uma expressao depois do 'SE'");
}