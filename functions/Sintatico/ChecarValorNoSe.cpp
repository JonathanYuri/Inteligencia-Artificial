#pragma once
#include <vector>
#include <string>
#include <iostream>

#include "SyntaticAnalyzer.h"
#include "RegraAtual.cpp"

using namespace std;

void ReconhecerValorNoSe(vector<string> rule, int *string_stopped, int linha, variavel varSE, string operador)
{
    if (*string_stopped >= rule.size())
    {
        throw runtime_error("Esperando true/false");
    }
    if (rule[*string_stopped].compare("true") == 0 || rule[*string_stopped].compare("false") == 0)
    {
        varSE.valor = rule[*string_stopped];
        regraAtual.se.push_back({varSE, operador});

        *string_stopped += 1;
        ReconhecerEOuEntao(rule, string_stopped, linha);
        return;
    }
    throw runtime_error("Esperando true/false");
}