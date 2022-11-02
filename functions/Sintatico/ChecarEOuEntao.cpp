#pragma once
#include <vector>
#include <string>
#include <iostream>

#include "SyntaticAnalyzer.h"
#include "RegraAtual.cpp"

using namespace std;

void ReconhecerEOuEntao(vector<string> rule, int *string_stopped, int linha)
{
    if (*string_stopped >= rule.size())
    {
        throw runtime_error("Esperando um 'ENTAO' ou '&'");
    }
    if (rule[*string_stopped].compare("&") == 0)
    {
        *string_stopped += 1;
        ReconhecerVarNoSe(rule, string_stopped, linha, "&");
        return;
    }
    else if (rule[*string_stopped].compare("ENTAO") == 0)
    {
        *string_stopped += 1;
        ReconhecerVarNoEntao(rule, string_stopped, linha, "");
        return;
    }
    throw runtime_error("Esperando um 'ENTAO' ou '&'");
}