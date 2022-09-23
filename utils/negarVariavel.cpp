#include "types.h"

void negarVariavel(variavel *var)
{
    if (var->valor.compare("true") == 0)
    {
        var->valor = "false";
        return;
    }
    var->valor = "true";
    return;
}