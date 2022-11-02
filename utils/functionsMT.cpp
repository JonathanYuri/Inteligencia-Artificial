#include <vector>

#include "types.h"

#pragma once

using namespace std;

int AchouNaMT(vector<variavel> *MT, variavel var)
{
    for (int k = 0; k < MT->size(); k++)
    {
        if (MT->at(k).nome.compare(var.nome) == 0)
        {
            if (MT->at(k).valor.compare(var.valor) == 0)     return 1;
            else    return 0;
        }
    }
    return -1;
}

void AdicionarNaMT(vector<variavel> *MT, variavel var)
{
    switch (AchouNaMT(MT, var))
    {
        case -1:
            MT->push_back(var);
            return;
        default:
            return;
    }
}
