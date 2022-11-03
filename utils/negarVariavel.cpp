#include "types.h"

#pragma once

variavel NegarVariavel(variavel var)
{
    if (var.valor.compare("true") == 0)
    {
        var.valor = "false";
        return var;
    }
    var.valor = "true";
    return var;
}