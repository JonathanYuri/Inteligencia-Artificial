#include <vector>

#include "types.h"

#pragma once

using namespace std;

int AchouNaMT(vector<pair<variavel, float>> *MT, variavel var)
{
    for (int k = 0; k < MT->size(); k++)
    {
        if (MT->at(k).first.nome.compare(var.nome) == 0)
        {
            if (MT->at(k).first.valor.compare(var.valor) == 0)     return 1;
            else    return 0;
        }
    }
    return -1;
}

void AdicionarNaMT(vector<pair<variavel, float>> *MT, variavel var, float certeza)
{
    switch (AchouNaMT(MT, var))
    {
        case -1:
            cout << "ADC " << endl;
            MT->push_back({var, certeza});
            return;
        default:
            return;
    }
}
