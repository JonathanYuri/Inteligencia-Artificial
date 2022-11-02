#pragma once
#include <vector>
#include <string>
#include <iostream>

#include "SyntaticAnalyzer.h"
#include "RegraAtual.cpp"

using namespace std;

void ReconhecerVarNoEntao(vector<string> rule, int *string_stopped, int linha, string operador)
{
    if (*string_stopped >= rule.size())
    {
        throw runtime_error("Esperando variaveis");
    }
    if (EveryLetterIsLower(rule[*string_stopped]))
    {   
        variavel varENTAO;
        varENTAO.nome = rule[*string_stopped];

        *string_stopped += 1;
        ReconhecerOperadorNoEntao(rule, string_stopped, linha, varENTAO, operador);
        return;
    }
    throw runtime_error("Todas as letras de uma variável devem ser minúsculas");
}