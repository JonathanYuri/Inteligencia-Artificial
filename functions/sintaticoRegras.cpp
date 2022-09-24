#include <iostream>
#include <string>
#include <vector>

#include "../utils/types.h"
#include "../utils/IsLower.cpp"

using namespace std;

regra regraAtual;

regra ObterRegraAtual()
{
    regra r = regraAtual;
    regraAtual.se.clear();
    regraAtual.entao.clear();
    return r;
}

void ChecarFinalOuContinuar(vector<string> rule, int *string_stopped)
{
    if (*string_stopped >= rule.size())
    {
        *string_stopped = -1;
        return;
    }
    if (rule[*string_stopped].compare("&") == 0)
    {
        return;
    }
    throw runtime_error("Esperando &");
}

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
        ChecarFinalOuContinuar(rule, string_stopped);
        return;
    }
    throw runtime_error("Esperando true/false");
}

void ReconhecerOperadorNoEntao(vector<string> rule, int *string_stopped, int linha, variavel varENTAO, string operador)
{
    if (*string_stopped >= rule.size())
    {
        throw runtime_error("Esperando um '='");
    }
    if (rule[*string_stopped].compare("=") == 0)
    {
        *string_stopped += 1;
        ReconhecerValorNoEntao(rule, string_stopped, linha, varENTAO, operador);
        return;
    }
    throw runtime_error("Esperando um '='");
}

void ReconhecerVariavelNoEntao(vector<string> rule, int *string_stopped, int linha, string operador)
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

void ChecarEOuEntao(vector<string> rule, int *string_stopped)
{
    if (*string_stopped >= rule.size())
    {
        throw runtime_error("Esperando um 'ENTAO' ou '&'");
    }
    if (rule[*string_stopped].compare("&") == 0 || rule[*string_stopped].compare("ENTAO") == 0)
    {
        return;
    }
}

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
        ChecarEOuEntao(rule, string_stopped);
        return;
    }
    throw runtime_error("Esperando true/false");
}

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

void ReconhecerVariavelNoSe(vector<string> rule, int *string_stopped, int linha, string operador)
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

void ChecarSeOuEntaoEncaminharOperadores(vector<string> rule, int *string_stopped, bool *entao, int linha)
{
    if (rule[*string_stopped].compare("SE") == 0 && *string_stopped == 0)
    {
        *string_stopped += 1;
        ReconhecerVariavelNoSe(rule, string_stopped, linha, "");
        return;
    }
    else if (*string_stopped != 0)
    {
        if (rule[*string_stopped].compare("&") == 0 || rule[*string_stopped].compare("|") == 0)
        {
            *string_stopped += 1;
            if (*entao)
            {
                ReconhecerVariavelNoEntao(rule, string_stopped, linha, rule[*string_stopped-1]);
            }
            else
            {
                ReconhecerVariavelNoSe(rule, string_stopped, linha, rule[*string_stopped-1]);
            }
            return;
        }
        else if (rule[*string_stopped].compare("ENTAO") == 0)
        {
            if (*entao)     throw runtime_error("2 'ENTAO' na mesma linha");

            *string_stopped += 1;
            *entao = true;
            ReconhecerVariavelNoEntao(rule, string_stopped, linha, "");
            return;
        }
    }
    
    throw runtime_error("error de sintaxe, esperando 'SE'");
}