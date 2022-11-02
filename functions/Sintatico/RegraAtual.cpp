#pragma once
#include <vector>

#include "../../utils/types.h"

using namespace std;

regra regraAtual;

regra ObterRegraAtual()
{
    regra r = regraAtual;
    regraAtual.se.clear();
    regraAtual.entao.clear();
    return r;
}