#include <iostream>
#include <string>
#include <vector>

#include "../utils/types.h"
#include "../utils/IsLower.cpp"

using namespace std;

regra regraAtual;

regra atual()
{
    regra r = regraAtual;
    regraAtual.se.clear();
    regraAtual.entao.clear();
    return r;
}

void S8(vector<string> rule, int *string_stopped)
{
    if (*string_stopped >= rule.size())
    {
        //regras.push_back(regraAtual);

        // regraAtual.se.clear();
        // regraAtual.entao.clear();

        *string_stopped = -1;
        return;
    }
    if (rule[*string_stopped].compare("&") == 0)
    {
        return;
    }
    throw runtime_error("Esperando &");
}

void S7(vector<string> rule, int *string_stopped, int linha, variavel varENTAO, string operador)
{
    if (*string_stopped >= rule.size())
    {
        throw runtime_error("Esperando true/false");
    }
    if (rule[*string_stopped].compare("true") == 0 || rule[*string_stopped].compare("false") == 0)
    {
        varENTAO.valor = rule[*string_stopped];

        regraAtual.entao.push_back({varENTAO, operador});
        //regras[linha].entao.push_back(varENTAO);

        //variavelENTAO.push_back(varENTAO);

        *string_stopped += 1;
        S8(rule, string_stopped);
        return;
    }
    throw runtime_error("Esperando true/false");
}

void S6(vector<string> rule, int *string_stopped, int linha, variavel varENTAO, string operador)
{
    if (*string_stopped >= rule.size())
    {
        throw runtime_error("Esperando um '='");
    }
    if (rule[*string_stopped].compare("=") == 0)
    {
        *string_stopped += 1;
        S7(rule, string_stopped, linha, varENTAO, operador);
        return;
    }
    throw runtime_error("Esperando um '='");
}

void S5(vector<string> rule, int *string_stopped, int linha, string operador)
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
        S6(rule, string_stopped, linha, varENTAO, operador);
        return;
    }
    throw runtime_error("Todas as letras de uma variável devem ser minúsculas");
}

void S4(vector<string> rule, int *string_stopped)
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

void S3(vector<string> rule, int *string_stopped, int linha, variavel varSE, string operador)
{
    if (*string_stopped >= rule.size())
    {
        throw runtime_error("Esperando true/false");
    }
    if (rule[*string_stopped].compare("true") == 0 || rule[*string_stopped].compare("false") == 0)
    {
        varSE.valor = rule[*string_stopped];
        //varSE.linha = linha;

        regraAtual.se.push_back({varSE, operador});
        //regras[linha].se.push_back(varSE);

        //variavelSE.push_back(varSE);

        *string_stopped += 1;
        S4(rule, string_stopped);
        return;
    }
    throw runtime_error("Esperando true/false");
}

void S2(vector<string> rule, int *string_stopped, int linha, variavel varSE, string operador)
{
    if (*string_stopped >= rule.size())
    {
        throw runtime_error("Esperando um '='");
    }
    if (rule[*string_stopped].compare("=") == 0)
    {
        *string_stopped += 1;
        S3(rule, string_stopped, linha, varSE, operador);
        return;
    }
    throw runtime_error("Esperando um '=' depois da variavel");
}

void S1(vector<string> rule, int *string_stopped, int linha, string operador)
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
        S2(rule, string_stopped, linha, varSE, operador);
        return;
    }
    throw runtime_error("Todas as letras de uma variável devem ser minúsculas");
}

void S0(vector<string> rule, int *string_stopped, bool *entao, int linha)
{
    if (rule[*string_stopped].compare("SE") == 0 && *string_stopped == 0)
    {
        *string_stopped += 1;
        S1(rule, string_stopped, linha, "");
        return;
    }
    else if (*string_stopped != 0)
    {
        //if (rule[*string_stopped].compare("&") == 0)
        if (rule[*string_stopped].compare("&") == 0 || rule[*string_stopped].compare("|") == 0)
        {
            *string_stopped += 1;
            if (*entao)
            {
                S5(rule, string_stopped, linha, rule[*string_stopped-1]);
            }
            else
            {
                S1(rule, string_stopped, linha, rule[*string_stopped-1]);
            }
            return;
        }
        else if (rule[*string_stopped].compare("ENTAO") == 0)
        {
            if (*entao) // 2 entao na msm linha
            {
                throw runtime_error("2 'ENTAO' na mesma linha");
            }
            *string_stopped += 1;
            *entao = true;
            S5(rule, string_stopped, linha, "");
            return;
        }
    }
    throw runtime_error("error de sintaxe, esperando 'SE'");
}