#include <iostream>
#include <string>
#include <vector>

#include "utils/IsLower.cpp"
#include "utils/readFile.cpp"
#include "utils/negarVariavel.cpp"
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

int procurarNaMT(variavel se_var)
{
    for (int k = 0; k < MT.size(); k++)
    {
        if (MT[k].nome.compare(se_var.nome) == 0)
        {
            if (MT[k].valor.compare(se_var.valor) == 0)
            {
                // pra prox se_var
                return 1;
            }
            else
            {
                // quebro e vou para prox regra
                return 0;
            }
        }
    }
    return -1;
}

bool encadeamentoParaTras(variavel objetivo)
{
    // verificar minha MT
    switch (procurarNaMT(objetivo))
    {
        case 1:
            return true;
            break;
        case 0:
            return false;
            break;
        default:
            break;
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

int encadeamentoParaFrente(variavel objetivo, vector<int> regras_N_Usadas)
{
    //while (!encontreiObjetivo(objetivo))
    int encontrei = procurarNaMT(objetivo);
    while (encontrei == -1)
    {
        if (regras_N_Usadas.size() == 0)
        {
            // nao tem mais regras
            return -1;
        }

        vector<int> usouRegra;
        // testando cada regra nao usada, inicia com todas
        for (int i = 0; i < regras_N_Usadas.size(); i++)
        {
            int c = 1;
            for (auto se_var : regras[regras_N_Usadas[i]].se)
            {
                int resultado = procurarNaMT(se_var.first);
                if (resultado == 1)
                {
                    continue;
                }
                // se achei que eh indeterminado tenho que deixar a regra ainda, se for falso eu descarto
                if (resultado == -1 || resultado == 0)
                {
                    c = resultado;
                    break;
                }
            }

            usouRegra.push_back(c);
            if (c == 1)
            {
                // adicionar o que esta no entao para MT
                for (auto entao_var : regras[regras_N_Usadas[i]].entao)
                {
                    MT.push_back(entao_var.first);
                }
                // descarto a regra
                auto elem_to_remove = regras_N_Usadas.begin() + i;
                regras_N_Usadas.erase(elem_to_remove);
            }
            else if (c == 0)
            {
                // descarto a regra
                auto elem_to_remove = regras_N_Usadas.begin() + i;
                regras_N_Usadas.erase(elem_to_remove);
            }
            else if (c == -1)
            {
                // nao faco nd
            }
        }

        bool deuBreak = false;
        for (int c : usouRegra)
        {
            if (c == -1) continue;

            deuBreak = true;
            break;
        }
        
        // nao consegui usar nenhuma regra
        if (!deuBreak)
        {
            return -1;
        }

        usouRegra.clear();
        encontrei = procurarNaMT(objetivo);
    }
    if (encontrei == 1) {
        return 1;
    }
    else {
        return 0;
    }
}

int main()
{
    vector<string> lines = readFile("rules.txt");
    cout << "\t-----COMANDOS----- " << endl << endl;
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

    vector<variavel> MTantes = MT;

    cout << endl;

    variavel objetivo;

    cout << "Digite o nome da variavel: ";
    cin >> objetivo.nome;
    cout << "Digite o valor da variavel: ";
    cin >> objetivo.valor;

    cout << "digite 0 para usar o encadeamento para tras e 1 para usar o para frente" << endl;
    int escolha = 0;
    cin >> escolha;
    
    if (escolha == 0)
    {
        bool achei = encadeamentoParaTras(objetivo);
        cout << endl;
        if (achei) {
            cout << "**(" << objetivo.nome << "=" << objetivo.valor << ")**";
        } else {
            cout << "falso" << endl;
            if (objetivo.valor.compare("true") == 0)
            {
                cout << "**(" << objetivo.nome << "=false" << ")**";
            }
            else
            {
                cout << "**(" << objetivo.nome << "=true" << ")**";
            }
        }

        cout << endl << endl << "MT ao final:" << endl;
        for (auto s : MT)
        {
            cout << s.nome << " = " << s.valor << endl;
        }

        cout << endl;

        negarVariavel(&objetivo);

        // voltar a memória de trabalho
        MT = MTantes;

        bool acheiFalse = encadeamentoParaTras(objetivo);
        if (acheiFalse == achei)
        {
            if (achei)
            {
                cout << "Contradição: variavel assumiu false e true";
            }
            else
            {
                cout << "indeterminado";
            }
            cout << endl;
        }
    }

    else if (escolha == 1)
    {
        vector<int> regrasNaoUsadas;

        for (int i = 0; i < regras.size(); i++)
        {
            regrasNaoUsadas.push_back(i);
        }
        int achei = encadeamentoParaFrente(objetivo, regrasNaoUsadas);
        if (achei == -1)
        {
            cout << "indeterminado";
        }
        else if (achei == 1)
        {
            cout << "verdadeiro" << endl;
            cout << "**(" << objetivo.nome << "=" << objetivo.valor << ")**";
        }
        else
        {
            cout << "falso" << endl;
            if (objetivo.valor.compare("true") == 0)
            {
                cout << "**(" << objetivo.nome << "=false" << ")**";
            }
            else
            {
                cout << "**(" << objetivo.nome << "=true" << ")**";
            }
        }
    }

    // testar o false para ver se tem conflito

    return 0;
}
