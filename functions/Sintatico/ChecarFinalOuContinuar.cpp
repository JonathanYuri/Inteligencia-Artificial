#pragma once
#include <vector>
#include <string>
#include <iostream>

#include "SyntaticAnalyzer.h"
#include "RegraAtual.cpp"

using namespace std;

void ReconhecerFinal(vector<string> rule, int *string_stopped)
{
    if (*string_stopped >= rule.size())
    {
        cout << "stof: " << rule[*string_stopped-1] << endl;
        regraAtual.fc = stof(rule[*string_stopped-1]);
        *string_stopped = WAS_ENTIRE_COMMAND_VERIFIED;
        return;
    }
    throw runtime_error("Esperando final");
}

void ReconhecerNumber(vector<string> rule, int *string_stopped)
{
    cout << rule[*string_stopped] << endl;
    if (*string_stopped >= rule.size())
    {
        throw runtime_error("Esperando um numero");
    }
    if (isNumber(rule[*string_stopped]))
    {
        *string_stopped += 1;
        ReconhecerFinal(rule, string_stopped);
        return;
    }
    throw runtime_error("Esperando um numero");
}

void ReconhecerIgual(vector<string> rule, int *string_stopped)
{
    if (*string_stopped >= rule.size())
    {
        throw runtime_error("Esperando =");
    }
    if (rule[*string_stopped].compare("=") == 0)
    {
        *string_stopped += 1;
        ReconhecerNumber(rule, string_stopped);
        return;
    }
    throw runtime_error("Esperando =");
}

void ReconhecerFinalOuContinuar(vector<string> rule, int *string_stopped)
{
    if (*string_stopped >= rule.size())
    {
        regraAtual.fc = 1.0f;
        *string_stopped = WAS_ENTIRE_COMMAND_VERIFIED;
        return;
    }
    if (rule[*string_stopped].compare("&") == 0)
    {
        return;
    }
    if (rule[*string_stopped].compare("FC") == 0)
    {
        *string_stopped += 1;
        ReconhecerIgual(rule, string_stopped);
        return;
    }
    throw runtime_error("Esperando &");
}