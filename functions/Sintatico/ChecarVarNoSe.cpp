#pragma once
#include <vector>
#include <string>
#include <iostream>

#include "SyntaticAnalyzer.h"
#include "RegraAtual.cpp"

using namespace std;

void ReconhecerVarNoSe(vector<string> rule, int *string_stopped, int linha, string operador)
{
    if (*string_stopped >= rule.size())
    {
        throw runtime_error("Esperando uma expressao depois do 'SE'");
    }
    if (EveryLetterIsLower(rule[*string_stopped]))
    {
        variavel varSE;
        varSE.nome = rule[*string_stopped];

        *string_stopped += 1;
        ReconhecerOperadorNoSe(rule, string_stopped, linha, varSE, operador);
        return;
    }
    throw runtime_error("Todas as letras de uma variável devem ser minúsculas");
}