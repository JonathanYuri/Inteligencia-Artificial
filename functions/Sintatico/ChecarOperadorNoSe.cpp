#pragma once
#include <vector>
#include <string>
#include <iostream>

#include "SyntaticAnalyzer.h"
#include "RegraAtual.cpp"

using namespace std;

void ReconhecerOperadorNoSe(vector<string> rule, int *string_stopped, int linha, variavel varSE, string operador)
{
    if (*string_stopped >= rule.size())
    {
        throw runtime_error("Esperando um '='");
    }
    if (rule[*string_stopped].compare("=") == 0)
    {
        *string_stopped += 1;
        ReconhecerValorNoSe(rule, string_stopped, linha, varSE, operador);
        return;
    }
    throw runtime_error("Esperando um '=' depois da variavel");
}