#include <iostream>
#include <string>
#include <fstream>
#include <vector>

#include "utils/EveryLetterIsLower.cpp"

using namespace std;

struct variavel{
    string nome;
    string valor;
    int linha;
};

vector<variavel> variavelSE;
vector<variavel> variavelENTAO;

vector<variavel> variavelMT;

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
void S7(vector<string> rule, int *string_stopped, int linha, variavel varENTAO)
{
    if (*string_stopped >= rule.size())
    {
        throw runtime_error("Esperando true/false");
    }
    if (rule[*string_stopped].compare("true") == 0 || rule[*string_stopped].compare("false") == 0)
    {
        varENTAO.valor = rule[*string_stopped];
        varENTAO.linha = linha;

        variavelENTAO.push_back(varENTAO);

        *string_stopped += 1;
        S8(rule, string_stopped);
        return;
    }
    throw runtime_error("Esperando true/false");
}

/*
S6
*/
void S6(vector<string> rule, int *string_stopped, int linha, variavel varENTAO)
{
    if (*string_stopped >= rule.size())
    {
        throw runtime_error("Esperando um '='");
    }
    if (rule[*string_stopped].compare("=") == 0)
    {
        *string_stopped += 1;
        S7(rule, string_stopped, linha, varENTAO);
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
        variavel varENTAO;
        varENTAO.nome = rule[*string_stopped];

        *string_stopped += 1;
        S6(rule, string_stopped, linha, varENTAO);
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
void S3(vector<string> rule, int *string_stopped, int linha, variavel varSE)
{
    if (*string_stopped >= rule.size())
    {
        throw runtime_error("Esperando true/false");
    }
    if (rule[*string_stopped].compare("true") == 0 || rule[*string_stopped].compare("false") == 0)
    {
        varSE.valor = rule[*string_stopped];
        varSE.linha = linha;

        variavelSE.push_back(varSE);

        *string_stopped += 1;
        S4(rule, string_stopped);
        return;
    }
    throw runtime_error("Esperando true/false");
}

/*
S2
*/
void S2(vector<string> rule, int *string_stopped, int linha, variavel varSE)
{
    if (*string_stopped >= rule.size())
    {
        throw runtime_error("Esperando um '='");
    }
    if (rule[*string_stopped].compare("=") == 0)
    {
        *string_stopped += 1;
        S3(rule, string_stopped, linha, varSE);
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
        variavel varSE;
        varSE.nome = rule[*string_stopped];

        *string_stopped += 1;
        S2(rule, string_stopped, linha, varSE);
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
            if (*entao) // 2 entao na msm linha
            {
                throw runtime_error("2 'ENTAO' na mesma linha");
            }
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

bool encadeamentoParaTras(string objetivoVar, string objetivoValor)
{
    // verificar minha MT
    for (int i = 0; i < variavelMT.size(); i++)
    {
        if (variavelMT[i].nome.compare(objetivoVar) == 0)
        {
            if (variavelMT[i].valor.compare(objetivoValor) == 0)
            {
                variavel varMT;
                varMT.nome = objetivoVar;
                varMT.valor = objetivoValor;
                varMT.linha = -1;

                cout << objetivoVar << "=" << objetivoValor << endl;
                variavelMT.push_back(varMT);

                return true;
            }
            else
            {
                variavel varMT;
                varMT.nome = objetivoVar;
                if (variavelMT[i].valor.compare("true") == 0)
                {
                    varMT.valor = "true";
                }
                else
                {
                    varMT.valor = "false";
                }
                
                varMT.linha = -1;

                //cout << objetivoVar << "=" << objetivoValor << endl;
                variavelMT.push_back(varMT);

                return false;
            }
        }
    }

    // pegar todas as regras que tem o meu objetivo no entao
    vector<int> regrasComOObjetivo;
    for (int i = 0; i < variavelENTAO.size(); i++)
    {
        if (variavelENTAO[i].nome.compare(objetivoVar) == 0)
        {
            if (variavelENTAO[i].valor.compare(objetivoValor) == 0)
            {
                regrasComOObjetivo.push_back(variavelENTAO[i].linha);
            }
        }
    }

    for (int regra : regrasComOObjetivo)
    {
        vector<string> procurarVar;
        vector<string> procurarValor;
        
        // pegar cada regra e colocar no vetor o que esta no SE
        for (int i = 0; i < variavelSE.size(); i++)
        {
            if (variavelSE[i].linha > regra)    break;
            if (variavelSE[i].linha == regra)
            {
                //cout << variavelSE[i].nome << "=" << variavelSE[i].valor;
                procurarVar.push_back(variavelSE[i].nome);
                procurarValor.push_back(variavelSE[i].valor);
                // if (i + 1 < variavelSE.size() && variavelSE[i+1].linha == regra)
                // {
                //     cout << " & ";
                // }
            }
        }

        bool deuBreak = false;
        while (procurarVar.size() != 0)
        {
            // cout << "ATUAL " << objetivoVar << endl << "-=-=-=-=-=" << endl;
            string p1 = procurarVar.back();
            procurarVar.pop_back();

            string p2 = procurarValor.back();
            procurarValor.pop_back();

            // cout << "procurando " << p1 << "=" << p2 << endl;
            bool achei = encadeamentoParaTras(p1, p2);
            // cout << "achei " << p1 << "=";

            if (achei)
            {
                //cout << p2 << endl;
                continue;
            }
            else
            {
                // if (p2 == "false")
                // {
                //     cout << "true" << endl;
                // }
                // else
                // {
                //     cout << "false" << endl;
                // }
                deuBreak = true;
                break;
            }
        }
        //cout << "DEU BREAK " << deuBreak << endl;
        if (!deuBreak)
        {
            return true;
        }
    }
    return false;
}

void f3(vector<string> fact, int pos, variavel varMT)
{
    if (pos < fact.size())
    {
        throw runtime_error("erro na base de fatos");
    }
    varMT.linha = -1;
    variavelMT.push_back(varMT);
}

void f2(vector<string> fact, int pos, variavel varMT)
{
    if (pos >= fact.size())
    {
        throw runtime_error("erro na base de fatos");
    }
    if (fact[pos].compare("true") == 0 || fact[pos].compare("false") == 0)
    {
        varMT.valor = fact[pos];
        f3(fact, pos+1, varMT);
    }
    else
    {
        throw runtime_error("erro na base de fatos");
    }
}

void f1(vector<string> fact, int pos, variavel varMT)
{
    if (pos >= fact.size())
    {
        throw runtime_error("erro na base de fatos");
    }
    if (fact[pos].compare("=") == 0)
    {
        f2(fact, pos+1, varMT);
    }
    else
    {
        throw runtime_error("erro na base de fatos");
    }
}

void f0(vector<string> fact)
{
    if (EveryLetterIsLower(fact[0]))
    {
        variavel varMT;
        varMT.nome = fact[0];
        f1(fact, 1, varMT);
    }
    else
    {
        throw runtime_error("erro na base de fatos");
    }
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

    cout << endl;

    for (int i = 0; i < variavelSE.size(); i++)
    {
        cout << "Regra " << variavelSE[i].linha << ": var SE: " << variavelSE[i].nome << " valor: " << variavelSE[i].valor << endl;
    }

    for (int i = 0; i < variavelENTAO.size(); i++)
    {
        cout << "Regra " << variavelENTAO[i].linha << ": var ENTAO: " << variavelENTAO[i].nome << " valor: " << variavelENTAO[i].valor << endl;
    }

    cout << endl;

    // ler a base de fatos e interpretar os baguio
    vector<string> facts = readFile("facts.txt");
    vector<vector<string>> slavei = analyzer(facts);

    for (vector<string> r : slavei)
    {
        f0(r);
    }

    cout << "MT:" << endl;

    for (int i = 0; i < variavelMT.size(); i++)
    {
        cout << variavelMT[i].nome << "=" << variavelMT[i].valor << endl;
    }

    cout << endl;

    bool achei = encadeamentoParaTras("q", "true");
    cout << endl;
    if (achei) {
        cout << "TRUE";
    } else {
        cout << "FALSE";
    }

    return 0;
}
