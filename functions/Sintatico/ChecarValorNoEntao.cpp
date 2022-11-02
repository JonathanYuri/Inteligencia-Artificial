#pragma once
#include <vector>
#include <string>
#include <iostream>

#include "SyntaticAnalyzer.h"
#include "RegraAtual.cpp"

using namespace std;

void ReconhecerValorNoEntao(vector<string> rule, int *string_stopped, int linha, variavel varENTAO, string operador)
{
    if (*string_stopped >= rule.size())
    {
        throw runtime_error("Esperando true/false");
    }
    if (rule[*string_stopped].compare("true") == 0 || rule[*string_stopped].compare("false") == 0)
    {
        varENTAO.valor = rule[*string_stopped];
        regraAtual.entao.push_back({varENTAO, operador});
        
        *string_stopped += 1;
        ReconhecerFinalOuContinuar(rule, string_stopped);
        return;
    }
    throw runtime_error("Esperando true/false");
}