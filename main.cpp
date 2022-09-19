#include <iostream>
#include <string>
#include <vector>

#include "utils/IsLower.cpp"
#include "utils/readFile.cpp"
#include "functions/fatos.cpp"
#include "functions/lexico.cpp"
#include "functions/sintaticoRegras.cpp"

using namespace std;

vector<variavel> MT;
vector<regra> regras;

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

bool encadeamentoParaTras(variavel objetivo)
{
    // verificar minha MT
    for (int i = 0; i < MT.size(); i++)
    {
        if (MT[i].nome.compare(objetivo.nome) == 0)
        {
            if (MT[i].valor.compare(objetivo.valor) == 0)
            {
                return true;
            }
            else
            {
                return false;
            }
        }
    }

    // pegar todas as regras que tem o meu objetivo no entao
    vector<int> regrasComOObjetivo;

    for (int i = 0; i < regras.size(); i++)
    {
        for (int j = 0; j < regras[i].entao.size(); j++)
        {
            if (regras[i].entao[j].first.nome.compare(objetivo.nome) == 0)
            {
                if (regras[i].entao[j].first.valor.compare(objetivo.valor) == 0)
                {
                    regrasComOObjetivo.push_back(i);
                }
            }
        }
    }

    for (int regra : regrasComOObjetivo)
    {
        vector<variavel> se_variaveis;
        
        // pegar cada regra colocar no vetor o que esta no SE
        for (auto se_var : regras[regra].se)
        {
            se_variaveis.push_back(se_var.first);
        }

        bool deuBreak = false;
        while (se_variaveis.size() != 0)
        {
            // cout << "ATUAL " << objetivoVar << endl << "-=-=-=-=-=" << endl;
            variavel var = se_variaveis.back();
            se_variaveis.pop_back();

            // cout << "procurando " << p1 << "=" << p2 << endl;
            bool achei = encadeamentoParaTras(var);
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
            variavel varMT;
            varMT.nome = objetivo.nome;
            varMT.valor = objetivo.valor;

            cout << objetivo.nome << "=" << objetivo.valor << endl;
            MT.push_back(varMT);
            return true;
        }
    }
    return false;
}

int main()
{
    vector<string> lines = readFile("rules.txt");
    cout << "comandos: " << endl;
    for (string line : lines)
    {
        cout << line << endl;
    }
    
    vector<vector<string>> rules = analyzer(lines);

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
        regras.push_back(atual());
    }

    cout << endl << endl;

    for (int i = 0; i < regras.size(); i++)
    {
        cout << "Regra " << i << ": SE (";

        for (auto regra_se : regras[i].se)
        {
            if (regra_se.second.compare("") != 0)    cout << " " << regra_se.second << " ";
            cout << regra_se.first.nome << "=" << regra_se.first.valor;
        }
        cout << ") ENTAO (";
        for (auto regra_entao : regras[i].entao)
        {
            if (regra_entao.second.compare("") != 0)    cout << " " << regra_entao.second << " ";
            cout << regra_entao.first.nome << "=" << regra_entao.first.valor;
        }
        cout << ")" << endl;
    }

    cout << endl;

    // ler a base de fatos e interpretar os baguio
    vector<string> facts = readFile("facts.txt");
    vector<vector<string>> slavei = analyzer(facts);

    for (vector<string> r : slavei)
    {
        MT.push_back(f0(r));
    }

    cout << "MT:" << endl;

    for (int i = 0; i < MT.size(); i++)
    {
        cout << MT[i].nome << "=" << MT[i].valor << endl;
    }

    cout << endl;

    variavel objetivo;
    objetivo.nome = "q";
    objetivo.valor = "true";
    bool achei = encadeamentoParaTras(objetivo);
    cout << endl;
    if (achei) {
        cout << "TRUE";
    } else {
        cout << "FALSE";
    }

    cout << endl << "MT ao final:" << endl;
    for (auto s : MT)
    {
        cout << s.nome << " = " << s.valor << endl;
    }

    // testar o false para ver se tem conflito

    return 0;
}
