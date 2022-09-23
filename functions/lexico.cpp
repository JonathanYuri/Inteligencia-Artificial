#include <string>
#include <vector>

#include "../utils/substring.cpp"

using namespace std;

string s4(string line, int *characterStopped)
{
    string op (1, line[*characterStopped]);

    *characterStopped += 1;
    //cout << op << " is a operator" << endl;;

    if (*characterStopped >= line.length())
    {
        *characterStopped = -1;
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
    throw runtime_error("error de sintaxe, esperando letra minuscula depois de operador\nlinha: " + line + "caractere" + line[*characterStopped]);
}

string s3(string line, int *characterStopped)
{
    for (int i = *characterStopped; i < line.length(); i++)
    {
        if (isalpha(line[i]))
        {
            if (islower(line[i]))
            {
                // print
                string subs = Substring(line, *characterStopped, i);
                //cout << subs << " is a keyword" << endl;
                *characterStopped = i;
                return subs;
            }
        }
        else
        {
            // print
            string subs = Substring(line, *characterStopped, i);
            //cout << subs << " is a keyword" << endl;
            *characterStopped = i;
            return subs;
        }
    }

    // print
    string subs = Substring(line, *characterStopped, line.length());
    //cout << subs << " is a keyword" << endl;
    *characterStopped = -1;
    return subs;
}

string s2(string line, int *characterStopped)
{
    for (int i = *characterStopped; i < line.length(); i++)
    {
        if (isalpha(line[i]) && isupper(line[i]))
        {
            string subs = Substring(line, *characterStopped, i);
            if (subs.compare("true") == 0 || subs.compare("false") == 0)
            {
                //cout << subs << " is a keyword" << endl;
                *characterStopped = i;
            }
            else
            {
                // erro
                *characterStopped = -1;
            }
            return subs;
        }
        if (!isalnum(line[i]))
        {
            string subs = Substring(line, *characterStopped, i);
            if (subs.compare("true") == 0 || subs.compare("false") == 0)
            {
                //cout << subs << " is a keyword" << endl;
            }
            else
            {
                //cout << subs << " is a identifier" << endl;
            }
            
            *characterStopped = i;
            return subs;
        }
    }

    string subs = Substring(line, *characterStopped, line.length());
    if (subs.compare("true") == 0 || subs.compare("false") == 0)
    {
        //cout << subs << " is a keyword" << endl;
    }
    else
    {
        //cout << subs << " is a identifier" << endl;
    }
    *characterStopped = -1;
    return subs;
}

string s1(string line, int *characterStopped)
{
    if (islower(line[*characterStopped]))
    {
        return s2(line, characterStopped);
    }
    else
    {
        return s3(line, characterStopped);
    }
}

string s0(string line, int *characterStopped)
{
    if (isalpha(line[*characterStopped]))
    {
        return s1(line, characterStopped);
    }
    else
    {
        return s4(line, characterStopped);
    }
}