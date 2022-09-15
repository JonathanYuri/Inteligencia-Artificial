#include <iostream>
#include <string>
#include <fstream>
#include <vector>

#include "utils/EveryLetterIsLower.cpp"

using namespace std;

vector<string> variaveisSE;
vector<string> valoresSE;
vector<int> linhaSE;

vector<string> variaveisENTAO;
vector<string> valoresENTAO;
vector<int> linhaENTAO;

vector<string> readFile(string filename)
{
    string line;
    vector<string> lines;
    ifstream fileToRead(filename);
    if (fileToRead.is_open())
    {
        while (getline(fileToRead, line, '\n'))
        {
            string newline = "";
            for (char character: line)
            {
                if (!isspace(character))
                {
                    newline.push_back(character);
                }
            }
            lines.push_back(newline);
        }
        fileToRead.close();
        return lines;
    }
    throw runtime_error("Could not read file");
}

string substring(string line, int inicio, int final)
{
    string subs = "";
    for (int i = inicio; i < final; i++)
    {
        subs.push_back(line[i]);
    }
    return subs;
}

string s2(string line, int *characterStopped)
{
    for (int i = *characterStopped; i < line.length(); i++)
    {
        if (isalpha(line[i]) && isupper(line[i]))
        {
            string subs = substring(line, *characterStopped, i);
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
            string subs = substring(line, *characterStopped, i);
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

    string subs = substring(line, *characterStopped, line.length());
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

string s3(string line, int *characterStopped)
{
    for (int i = *characterStopped; i < line.length(); i++)
    {
        if (isalpha(line[i]))
        {
            if (islower(line[i]))
            {
                // print
                string subs = substring(line, *characterStopped, i);
                //cout << subs << " is a keyword" << endl;
                *characterStopped = i;
                return subs;
            }
        }
        else
        {
            // print
            string subs = substring(line, *characterStopped, i);
            //cout << subs << " is a keyword" << endl;
            *characterStopped = i;
            return subs;
        }
    }

    // print
    string subs = substring(line, *characterStopped, line.length());
    //cout << subs << " is a keyword" << endl;
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

/*
S8
*/
void S8(vector<string> rule, int *string_stopped)
{
    if (*string_stopped >= rule.size())
    {
        *string_stopped = -1;
        return;
    }
    if (rule[*string_stopped].compare("&") == 0)
    {
        return;
    }
    throw runtime_error("Esperando &");
}

/*
S7
*/
void S7(vector<string> rule, int *string_stopped, int linha)
{
    if (*string_stopped >= rule.size())
    {
        throw runtime_error("Esperando true/false");
    }
    if (rule[*string_stopped].compare("true") == 0 || rule[*string_stopped].compare("false") == 0)
    {
        valoresENTAO.push_back(rule[*string_stopped]);
        linhaENTAO.push_back(linha);

        *string_stopped += 1;
        S8(rule, string_stopped);
        return;
    }
    throw runtime_error("Esperando true/false");
}

/*
S6
*/
void S6(vector<string> rule, int *string_stopped, int linha)
{
    if (*string_stopped >= rule.size())
    {
        throw runtime_error("Esperando um '='");
    }
    if (rule[*string_stopped].compare("=") == 0)
    {
        *string_stopped += 1;
        S7(rule, string_stopped, linha);
        return;
    }
    throw runtime_error("Esperando um '='");
}

/*
S5
*/
void S5(vector<string> rule, int *string_stopped, int linha)
{
    if (*string_stopped >= rule.size())
    {
        throw runtime_error("Esperando variaveis");
    }
    if (EveryLetterIsLower(rule[*string_stopped]))
    {
        variaveisENTAO.push_back(rule[*string_stopped]);

        *string_stopped += 1;
        S6(rule, string_stopped, linha);
        return;
    }
    throw runtime_error("Todas as letras de uma variável devem ser minúsculas");
}

/*
S4
*/
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

/*
S3
*/
void S3(vector<string> rule, int *string_stopped, int linha)
{
    if (*string_stopped >= rule.size())
    {
        throw runtime_error("Esperando true/false");
    }
    if (rule[*string_stopped].compare("true") == 0 || rule[*string_stopped].compare("false") == 0)
    {
        valoresSE.push_back(rule[*string_stopped]);
        linhaSE.push_back(linha);

        *string_stopped += 1;
        S4(rule, string_stopped);
        return;
    }
    throw runtime_error("Esperando true/false");
}

/*
S2
*/
void S2(vector<string> rule, int *string_stopped, int linha)
{
    if (*string_stopped >= rule.size())
    {
        throw runtime_error("Esperando um '='");
    }
    if (rule[*string_stopped].compare("=") == 0)
    {
        *string_stopped += 1;
        S3(rule, string_stopped, linha);
        return;
    }
    throw runtime_error("Esperando um '=' depois da variavel");
}

/*
S1
*/
void S1(vector<string> rule, int *string_stopped, int linha)
{
    if (*string_stopped >= rule.size())
    {
        throw runtime_error("Esperando uma expressao depois do 'SE'");
    }
    if (EveryLetterIsLower(rule[*string_stopped]))
    {
        variaveisSE.push_back(rule[*string_stopped]);

        *string_stopped += 1;
        S2(rule, string_stopped, linha);
        return;
    }
    throw runtime_error("Todas as letras de uma variável devem ser minúsculas");
}

/*
S0
*/
void S0(vector<string> rule, int *string_stopped, bool *entao, int linha)
{
    if (rule[*string_stopped].compare("SE") == 0 && *string_stopped == 0)
    {
        *string_stopped += 1;
        S1(rule, string_stopped, linha);
        return;
    }
    else if (*string_stopped != 0)
    {
        if (rule[*string_stopped].compare("&") == 0)
        {
            *string_stopped += 1;
            if (*entao)
            {
                S5(rule, string_stopped, linha);
            }
            else
            {
                S1(rule, string_stopped, linha);
            }
            return;
        }
        else if (rule[*string_stopped].compare("ENTAO") == 0)
        {
            *string_stopped += 1;
            *entao = true;
            S5(rule, string_stopped, linha);
            return;
        }
    }
    throw runtime_error("error de sintaxe, esperando 'SE'");
}

vector<vector<string>> analyzer(vector<string> lines)
{
    vector<vector<string>> rules;
    for (string line : lines)
    {
        if (line.length() == 0) continue;
        int character_stopped = 0;
        vector<string> rule;
        while (character_stopped != -1)
        {
           string token = s0(line, &character_stopped);
           rule.push_back(token);
        }
        rules.push_back(rule);
    }

    return rules;
}

int main()
{
    vector<string> lines = readFile("rules.txt");
    for (string line : lines)
    {
        cout << line << endl;
    }
    
    cout << endl;
    vector<vector<string>> rules = analyzer(lines);

    for (int i = 0; i < rules.size(); i++)
    {
        cout << "Rule " << i + 1 << ": ";
        for (string token : rules[i])
        {
            cout << token << " ";
        }
        cout << endl;
    }

    for (int i = 0; i < rules.size(); i++)
    {
        if (rules[i].size() == 0) continue;
        int string_stopped = 0;
        bool imInEntao = false;
        while (string_stopped != -1)
        {
            //cout << "pos " << string_stopped << "string: " << rule[string_stopped] << endl;
            S0(rules[i], &string_stopped, &imInEntao, i);
        }
    }

    for (int i = 0; i < variaveisSE.size(); i++)
    {
        cout << "Regra " << linhaSE[i] << ": var SE: " << variaveisSE[i] << " valor: " << valoresSE[i] << endl;
    }

    for (int i = 0; i < variaveisENTAO.size(); i++)
    {
        cout << "Regra " << linhaENTAO[i] << ": var ENTAO: " << variaveisENTAO[i] << " valor: " << valoresENTAO[i] << endl;
    }

    return 0;
}
