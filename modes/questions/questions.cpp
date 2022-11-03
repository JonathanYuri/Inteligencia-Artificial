#include "../modes.h"
#include "../../utils/negarVariavel.cpp"
#include "../../utils/IsLower.cpp"

bool Regra_inaplicaveis(vector<int> usouRegra)
{
    for (int c : usouRegra)
    {
        if (c == -1) continue;
        
        return false;
    }
    return true;
}

int EncadeamentoParaTras(vector<regra> *regras, vector<variavel> *MT, variavel objetivo)
{
    // verificar minha MT
    switch (AchouNaMT(MT, objetivo))
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

    for (int i = 0; i < regras->size(); i++)
    {
        for (int j = 0; j < regras->at(i).entao.size(); j++)
        {
            if (regras->at(i).entao[j].first.nome.compare(objetivo.nome) == 0)
            {
                if (regras->at(i).entao[j].first.valor.compare(objetivo.valor) == 0)
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
        for (auto se_var : regras->at(regra).se)
        {
            se_variaveis.push_back(se_var.first);
        }

        bool deuBreak = false;
        while (se_variaveis.size() != 0)
        {
            variavel var = se_variaveis.back();
            se_variaveis.pop_back();

            int achei = EncadeamentoParaTras(regras, MT, var);

            if (achei == 1)     continue;
            else
            {
                deuBreak = true;
                break;
            }
        }

        if (!deuBreak)
        {
            AdicionarNaMT(MT, {objetivo.nome, objetivo.valor});
            return 1;
        }
    }
    return -1;
}

int EncadeamentoMisto(vector<regra> *regras, vector<variavel> *MT, variavel objetivo)
{
    vector<int> regras_N_Usadas;

    for (int i = 0; i < regras->size(); i++)
    {
        regras_N_Usadas.push_back(i);
    }

    for (int i = 0; i < regras_N_Usadas.size(); i++)
    {
        bool deuBreak = false;
        for (auto se_var : regras->at(regras_N_Usadas[i]).se)
        {
            int resultado = AchouNaMT(MT, se_var.first);
            if (resultado == 1)     continue;
            else if (resultado == 0)
            {
                deuBreak = true;
                break;
            }
            else
            {
                resultado = EncadeamentoParaTras(regras, MT, se_var.first);
                if (resultado == 0)
                {
                    variavel adc = NegarVariavel(se_var.first);
                    AdicionarNaMT(MT, adc);
                    deuBreak = true;
                    break;
                }

                if (resultado == -1)
                {
                    variavel adc = se_var.first;
                    adc.valor = "indeterminado";
                    AdicionarNaMT(MT, adc);
                    deuBreak = true;
                    break;
                }

                AdicionarNaMT(MT, se_var.first);
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
            for (auto entao_var : regras->at(regras_N_Usadas[i]).entao)
            {
                AdicionarNaMT(MT, entao_var.first);
            }
        }

        switch (AchouNaMT(MT, objetivo))
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

int EncadeamentoParaFrente(vector<regra> *regras, vector<variavel> *MT, variavel objetivo)
{
    vector<int> regras_N_Usadas;
    for (int i = 0; i < regras->size(); i++)
    {
        regras_N_Usadas.push_back(i);
    }

    int encontrei = AchouNaMT(MT, objetivo);
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
            for (auto se_var : regras->at(regras_N_Usadas[i]).se)
            {
                int resultado = AchouNaMT(MT, se_var.first);
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
                for (auto entao_var : regras->at(regras_N_Usadas[i]).entao)
                {
                    AdicionarNaMT(MT, entao_var.first);
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
        encontrei = AchouNaMT(MT, objetivo);
    }

    if (encontrei == 1)     return 1;
    else    return 0;
}

void ChecarContradicao(variavel objetivo, variavel objetivo2, int achei, int acheiFalse)
{
    if (achei == 1 && acheiFalse == 1) // a=true (1) e a=false (1)
    {
        cout << "contradicao: objetivo atribuiu valor true e false";
    }
    else if (achei == 0 && acheiFalse == 0) // a=true (0) e a=false (0)
    {
        cout << "contradicao: objetivo atribuiu valor true e false";
    }
    else if (achei == -1 && acheiFalse == -1)
    {
        cout << "objetivo indeterminado";
    }

    else if (achei == 1 && acheiFalse == 0)
    {
        cout << "CERTO, objetivo encontrado: " << objetivo.nome << " = " << objetivo.valor;
    }
    else if (achei == 1 && acheiFalse == -1)
    {
        cout << "CERTO, objetivo encontrado: " << objetivo.nome << " = " << objetivo.valor;
    }

    else if (achei == 0 && acheiFalse == 1)
    {
        cout << "ERRADO, objetivo encontrado: " << objetivo2.nome << " = " << objetivo2.valor;
    }
    // R
    else if (achei == 0 && acheiFalse == -1)
    {
        cout << "ERRADO, objetivo encontrado: " << objetivo2.nome << " = " << objetivo2.valor;
    }

    // R
    else if (achei == -1 && acheiFalse == 1)
    {
        cout << "ERRADO, objetivo encontrado: " << objetivo2.nome << " = " << objetivo2.valor;
    }
    else if (achei == -1 && acheiFalse == 0)
    {
        cout << "CERTO, objetivo encontrado: " << objetivo.nome << " = " << objetivo.valor;
    }
}

bool ObjetivoVerdadeiro(vector<regra> *regras, vector<variavel> *MT, int escolha, variavel objetivo)
{
    vector<variavel> MTantes = *MT;

    cout << "-------------------";
    int achei = 0, acheiFalse = 0;
    if (escolha == 0)
    {
        achei = EncadeamentoParaTras(regras, MT, objetivo);

        variavel objetivo2 = NegarVariavel(objetivo);

        // voltar a memória de trabalho
        vector<variavel> MTprimeira = *MT;
        *MT = MTantes;

        acheiFalse = EncadeamentoParaTras(regras, MT, objetivo2);

        ChecarContradicao(objetivo, objetivo2, achei, acheiFalse);

        if (achei == 1)     *MT = MTprimeira;
        if (achei == 1 && acheiFalse == 1)  AdicionarNaMT(MT, objetivo2);
    }

    else if (escolha == 1)
    {
        achei = EncadeamentoParaFrente(regras, MT, objetivo);

        vector<variavel> MTprimeira = *MT;
        *MT = MTantes;

        variavel objetivo2 = NegarVariavel(objetivo);

        // procurar pelo objetivo
        if (achei == 0) {
            acheiFalse = 1;
            achei = EncadeamentoParaTras(regras, MT, objetivo);
        }
        else{
            acheiFalse = EncadeamentoParaTras(regras, MT, objetivo2);
        }

        ChecarContradicao(objetivo, objetivo2, achei, acheiFalse);

        if (achei == 1)     *MT = MTprimeira;
        if (achei == 1 && acheiFalse == 1)  AdicionarNaMT(MT, objetivo2);
    }

    else if (escolha == 2)
    {
        achei = EncadeamentoMisto(regras, MT, objetivo);
        variavel objetivo2 = NegarVariavel(objetivo);

        vector<variavel> MTprimeira = *MT;
        *MT = MTantes;

        if (achei == 0) {
            acheiFalse = 1;
            achei = EncadeamentoParaTras(regras, MT, objetivo);
        }
        else{
            acheiFalse = EncadeamentoParaTras(regras, MT, objetivo2);
        }

        ChecarContradicao(objetivo, objetivo2, achei, acheiFalse);

        if (achei == 1)     *MT = MTprimeira;
        if (achei == 1 && acheiFalse == 1)  AdicionarNaMT(MT, objetivo2);
    }
    cout << "-------------------" << endl;

    cout << endl << "\tMemoria de Trabalho:" << endl;
    for (auto var : *MT)
    {
        cout << var.nome << " = " << var.valor << endl;
    }

    return achei == 1;
}

void TestarVariaveis(vector<regra> *regras, vector<pair<variavel, int>> objetivos, vector<variavel> *MT)
{
    vector<variavel> MTantes = *MT;

    bool objetivosVerdadeiros = true;

    for (auto obj : objetivos)
    {
        *MT = MTantes;
        
        bool objVerdadeiro = ObjetivoVerdadeiro(regras, MT, obj.second, obj.first);
        if (!objVerdadeiro)     objetivosVerdadeiros = false;
        cout << endl;
    }

    cout << "-------------------";
    for (int i = 0; i < objetivos.size(); i++)
    {
        cout << objetivos[i].first.nome << "=" << objetivos[i].first.valor;
        if (i != objetivos.size() - 1)      cout << " & ";
    }
    if (objetivosVerdadeiros)   cout << " = TRUE";
    else    cout << " = FALSE";
    cout << "-------------------";
}

vector<pair<variavel, int>> LerVariaveis(int qntVariaveis)
{
    vector<pair<variavel, int>> variaveis;
    for (int i = 0; i < qntVariaveis; i++)
    {
        variavel objetivo;

        cout << "Digite o nome da variavel: ";
        cin >> objetivo.nome;
        cout << "Digite o valor da variavel: ";
        cin >> objetivo.valor;

        if (objetivo.valor.compare("true") != 0 && objetivo.valor.compare("false") != 0)    throw runtime_error("objetivo deve ser true ou false");
        if (!EveryLetterIsLower(objetivo.nome))     throw runtime_error("variavel objetivo deve ter todas as letras minusculas");

        cout << "Digite:\n0 para usar o encadeamento para tras\n1 para usar o para frente\n2 para usar o misto" << endl << endl;
        int escolha = 0;
        cin >> escolha;

        variaveis.push_back({objetivo, escolha});
    }
    return variaveis;
}

void questions(vector<regra> regras, vector<variavel> MT)
{
    int qntVariaveis = 0;
    cout << "Digite quantas variaveis quer testar: ";
    cin >> qntVariaveis;

    if (qntVariaveis <= 0)  throw runtime_error("Digite um numero maior que 0");

    vector<pair<variavel, int>> variaveis = LerVariaveis(qntVariaveis);
    TestarVariaveis(&regras, variaveis, &MT);
}