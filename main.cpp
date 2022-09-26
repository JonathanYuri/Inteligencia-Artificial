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
            //AnalisadorLexico
            string token = EncaminharOperadorOuPalavra(line, &character_stopped);
            rule.push_back(token);
        }
        rules.push_back(rule);
    }

    return rules;
}

bool Regra_inaplicaveis(vector<int> usouRegra)
{
    for (int c : usouRegra)
    {
        if (c == -1) continue;
        
        return false;
    }
    return true;
}

int AchouNaMT(variavel se_var)
{
    for (int k = 0; k < MT.size(); k++)
    {
        if (MT[k].nome.compare(se_var.nome) == 0)
        {
            if (MT[k].valor.compare(se_var.valor) == 0)     return 1;
            else    return 0;
        }
    }
    return -1;
}

int EncadeamentoParaTras(variavel objetivo)
{
    // verificar minha MT
    switch (AchouNaMT(objetivo))
    {
        case 1:
            return 1;
        case 0:
            return 0;
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
            variavel var = se_variaveis.back();
            se_variaveis.pop_back();

            int achei = EncadeamentoParaTras(var);

            if (achei == 1)     continue;
            else
            {
                deuBreak = true;
                break;
            }
        }

        if (!deuBreak)
        {
            variavel varMT;
            varMT.nome = objetivo.nome;
            varMT.valor = objetivo.valor;

            MT.push_back(varMT);
            return 1;
        }
    }
    return -1;
}

int EncadeamentoMisto(variavel objetivo, vector<int> regras_N_Usadas)
{
    for (int i = 0; i < regras_N_Usadas.size(); i++)
    {
        bool deuBreak = false;
        for (auto se_var : regras[regras_N_Usadas[i]].se)
        {
            int resultado = AchouNaMT(se_var.first);
            if (resultado == 1)     continue;
            else if (resultado == 0)
            {
                deuBreak = true;
                break;
            }
            else
            {
                resultado = EncadeamentoParaTras(se_var.first);
                if (resultado == 0)
                {
                    variavel adc = NegarVariavel(se_var.first);
                    MT.push_back(adc);
                    deuBreak = true;
                    break;
                }

                if (resultado == -1)
                {
                    variavel adc = se_var.first;
                    adc.valor = "indeterminado";
                    MT.push_back(adc);
                    deuBreak = true;
                    break;
                }

                MT.push_back(se_var.first);
            }
        }

        if (deuBreak)
        {
            auto elem_to_remove = regras_N_Usadas.begin() + i;
            regras_N_Usadas.erase(elem_to_remove);
        }
        else
        {
            // adicionar o que esta no entao na MT
            for (auto entao_var : regras[regras_N_Usadas[i]].entao)
            {
                MT.push_back(entao_var.first);
            }
        }

        switch (AchouNaMT(objetivo))
        {
            case 1:
                return 1;
            case 0:
                return 0;
            default:
                break;
        }
    }

    return -1;
}

int EncadeamentoParaFrente(variavel objetivo, vector<int> regras_N_Usadas)
{
    int encontrei = AchouNaMT(objetivo);
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
                int resultado = AchouNaMT(se_var.first);
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
                // regra nao foi usada
            }
        }

        // todos == -1
        if (Regra_inaplicaveis(usouRegra))
        {
            return -1;
        }
        usouRegra.clear();
        encontrei = AchouNaMT(objetivo);
    }

    if (encontrei == 1)     return 1;
    else    return 0;
}

void ChecarObjetivo(int escolha, variavel objetivo)
{
    vector<variavel> MTantes = MT;

    cout << "-------------------";
    if (escolha == 0)
    {
        int achei = EncadeamentoParaTras(objetivo);

        variavel objetivo2 = NegarVariavel(objetivo);

        // voltar a memória de trabalho
        vector<variavel> MTprimeira = MT;
        MT = MTantes;

        int acheiFalse = EncadeamentoParaTras(objetivo2);

        if (achei == -1 && acheiFalse == -1)    cout << "objetivo indeterminado";
        else if (acheiFalse == -1)
        {
            if (achei == 1)             cout << "CERTO, objetivo encontrado: " << objetivo.nome << " = " << objetivo.valor;
            else if (achei == 0)        cout << "ERRADO, objetivo encontrado: " << objetivo2.nome << " = " << objetivo2.valor;
        }
        else if (achei == -1)
        {
            if (acheiFalse == 1)        cout << "ERRADO, objetivo encontrado: " << objetivo2.nome << " = " << objetivo2.valor;
            else if (acheiFalse == 0)   cout << "CERTO, objetivo encontrado: " << objetivo.nome << " = " << objetivo.valor;
        }
        else if (achei == acheiFalse)       cout << "contradicao: objetivo atribuiu valor true e false";
        else
        {
            // q = true (1)
            // q = false (0)
            if (achei == 1)     cout << "CERTO, objetivo encontrado: " << objetivo.nome << " = " << objetivo.valor;
            else                cout << "ERRADO, objetivo encontrado: " << objetivo2.nome << " = " << objetivo2.valor;
        }

        if (achei == 1)     MT = MTprimeira;
        if (achei == 1 && acheiFalse == 1)  MT.push_back(objetivo2);
    }

    else if (escolha == 1)
    {
        vector<int> regrasNaoUsadas;
        for (int i = 0; i < regras.size(); i++)
        {
            regrasNaoUsadas.push_back(i);
        }

        variavel objetivo2 = NegarVariavel(objetivo);

        int achei = EncadeamentoParaFrente(objetivo, regrasNaoUsadas);
        
        if (achei == -1)        cout << "objetivo indeterminado";
        else if (achei == 1)    cout << "CERTO, objetivo encontrado: " << objetivo.nome << " = " << objetivo.valor;
        else                    cout << "ERRADO, objetivo encontrado: " << objetivo2.nome << " = " << objetivo2.valor;
    }

    else if (escolha == 2)
    {
        vector<int> regrasNaoUsadas;
        for (int i = 0; i < regras.size(); i++)
        {
            regrasNaoUsadas.push_back(i);
        }

        variavel objetivo2 = NegarVariavel(objetivo);

        int achei = EncadeamentoMisto(objetivo, regrasNaoUsadas);
        if (achei == -1)        cout << "objetivo indeterminado";
        else if (achei == 1)    cout << "CERTO, objetivo encontrado: " << objetivo.nome << " = " << objetivo.valor;
        else                    cout << "ERRADO, objetivo encontrado: " << objetivo2.nome << " = " << objetivo2.valor;
    }
    cout << "-------------------" << endl;

    cout << endl << "\tMemoria de Trabalho:" << endl;
    for (auto var : MT)
    {
        cout << var.nome << " = " << var.valor << endl;
    }
}

int main()
{
    vector<string> lines = readFile("rules.txt");
    vector<vector<string>> rules = analyzer(lines);

    for (int i = 0; i < rules.size(); i++)
    {
        if (rules[i].size() == 0) continue;

        int string_stopped = 0;
        bool imInEntao = false;

        while (string_stopped != -1)
        {
            //AnalisadorSintatico
            ChecarSeOuEntaoEncaminharOperadores(rules[i], &string_stopped, &imInEntao, i);
        }
        regras.push_back(ObterRegraAtual());
    }

    vector<string> facts = readFile("facts.txt");
    vector<vector<string>> linhasFatos = analyzer(facts);

    for (vector<string> r : linhasFatos)    MT.push_back(ReconhecerVariavel(r));

    variavel objetivo;

    cout << "Digite o nome da variavel: ";
    cin >> objetivo.nome;
    cout << "Digite o valor da variavel: ";
    cin >> objetivo.valor;

    if (objetivo.valor.compare("true") != 0 && objetivo.valor.compare("false") != 0)
    {
        throw runtime_error("objetivo deve ser true ou false");
    }
    if (!EveryLetterIsLower(objetivo.nome))
    {
        throw runtime_error("variavel objetivo deve ter todas as letras minusculas");
    }

    cout << "Digite:\n0 para usar o encadeamento para tras\n1 para usar o para frente\n2 para usar o misto" << endl;
    int escolha = 0;
    cin >> escolha;
    
    ChecarObjetivo(escolha, objetivo);

    // testar o false para ver se tem conflito

    return 0;
}
