#include "types.h"

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