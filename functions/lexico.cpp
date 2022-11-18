#include <string>
#include <vector>

#include "../utils/substring.cpp"
#include "../utils/types.h"

using namespace std;

string ReconhecerOperadores(string line, int *characterStopped)
{
    string op (1, line[*characterStopped]);

    *characterStopped += 1;

    if (*characterStopped >= line.length())
    {
        *characterStopped = WAS_ENTIRE_COMMAND_VERIFIED;
        if (line[*characterStopped] == '&' || line[*characterStopped] == '=')   return op;
        throw runtime_error("caractere nao reconhecido " + line[*characterStopped]);
    }

    if (isalpha(line[*characterStopped]))
    {
        if (islower(line[*characterStopped]))
        {
            return op;
        }
    }
    return op;
    //throw runtime_error("error de sintaxe, esperando letra minuscula depois de operador\nlinha: " + line + "caractere" + line[*characterStopped]);
}

string ReconhecerSeOuEntao(string line, int *characterStopped)
{
    for (int i = *characterStopped; i < line.length(); i++)
    {
        if (isalpha(line[i]))
        {
            if (islower(line[i]))
            {
                string subs = Substring(line, *characterStopped, i);
                *characterStopped = i;
                return subs;
            }
        }
        else
        {
            string subs = Substring(line, *characterStopped, i);
            *characterStopped = i;
            return subs;
        }
    }

    string subs = Substring(line, *characterStopped, line.length());
    *characterStopped = WAS_ENTIRE_COMMAND_VERIFIED;
    return subs;
}

string MontarVarEValor(string line, int *characterStopped)
{
    for (int i = *characterStopped; i < line.length(); i++)
    {
        if (isalpha(line[i]) && isupper(line[i]))
        {
            string subs = Substring(line, *characterStopped, i);

            if (subs.compare("true") == 0 || subs.compare("false") == 0)
            {
                *characterStopped = i;
            }
            else
            {
                *characterStopped = WAS_ENTIRE_COMMAND_VERIFIED;
            }
            return subs;
        }
        if (!isalnum(line[i]))
        {
            string subs = Substring(line, *characterStopped, i);
            *characterStopped = i;
            return subs;
        }
    }

    string subs = Substring(line, *characterStopped, line.length());
    *characterStopped = WAS_ENTIRE_COMMAND_VERIFIED;
    return subs;
}

string EncaminharVarOuPalavra(string line, int *characterStopped)
{
    if (islower(line[*characterStopped]))
    {
        return MontarVarEValor(line, characterStopped);
    }
    else
    {
        return ReconhecerSeOuEntao(line, characterStopped);
    }
}

string ReconhecerPorcentagem(string line, int *characterStopped)
{
    int i = *characterStopped;
    *characterStopped += 1;

    if (line[*characterStopped] != '.')
    {
        throw runtime_error("Esperando . apos o numero");
    }
    *characterStopped += 1;
    while (isdigit(line[*characterStopped]))
    {
        *characterStopped += 1;
    }
    return Substring(line, i, *characterStopped);
}

string EncaminharOperadorOuPalavra(string line, int *characterStopped)
{
    if (isalpha(line[*characterStopped]))
    {
        return EncaminharVarOuPalavra(line, characterStopped);
    }
    else if (isdigit(line[*characterStopped]))
    {
        string a = ReconhecerPorcentagem(line, characterStopped);
        if (*characterStopped >= line.length())
        {
            *characterStopped = WAS_ENTIRE_COMMAND_VERIFIED;
        }
        return a;
    }
    else
    {
        return ReconhecerOperadores(line, characterStopped);
    }
}