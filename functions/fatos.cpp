#include <vector>
#include <string>

#include "../utils/IsLower.cpp"
#include "../utils/types.h"

using namespace std;

variavel f3(vector<string> fact, int pos, variavel varMT)
{
    if (pos < fact.size())
    {
        throw runtime_error("erro na base de fatos");
    }
    return varMT;
    //variavelMT.push_back(varMT);
}

variavel f2(vector<string> fact, int pos, variavel varMT)
{
    if (pos >= fact.size())
    {
        throw runtime_error("erro na base de fatos");
    }
    if (fact[pos].compare("true") == 0 || fact[pos].compare("false") == 0)
    {
        varMT.valor = fact[pos];
        return f3(fact, pos+1, varMT);
    }
    else
    {
        throw runtime_error("erro na base de fatos");
    }
}

variavel f1(vector<string> fact, int pos, variavel varMT)
{
    if (pos >= fact.size())
    {
        throw runtime_error("erro na base de fatos");
    }
    if (fact[pos].compare("=") == 0)
    {
        return f2(fact, pos+1, varMT);
    }
    else
    {
        throw runtime_error("erro na base de fatos");
    }
}

variavel f0(vector<string> fact)
{
    if (EveryLetterIsLower(fact[0]))
    {
        variavel varMT;
        varMT.nome = fact[0];
        return f1(fact, 1, varMT);
    }
    else
    {
        throw runtime_error("erro na base de fatos");
    }
}