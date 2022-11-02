#include <iostream>
#include <map>

#include "../utils/types.h"
#include "../utils/functionsMT.cpp"

#pragma once

using namespace std;

map<string, string> perguntas;
vector<variavel> MTAk;

void addMap()
{
    perguntas.insert(make_pair("carnivoro", "Seu animal eh carnivoro?"));
    perguntas.insert(make_pair("coramarelotostado", "Seu animal tem cor amarelo tostado?"));
    perguntas.insert(make_pair("manchasescuras", "Seu animal tem manchas escuras?"));
    perguntas.insert(make_pair("leopardo", "Seu animal eh um leopardo?"));
    perguntas.insert(make_pair("listraspretas", "Seu animal tem listras pretas?"));
    perguntas.insert(make_pair("tigre", "Seu animal eh um tigre?"));
    perguntas.insert(make_pair("ungulado", "Seu animal eh ungulado?"));
    perguntas.insert(make_pair("corbranca", "Seu animal tem cor branca?"));
    perguntas.insert(make_pair("zebra", "Seu animal eh uma zebra?"));
    perguntas.insert(make_pair("ave", "Seu animal eh uma ave?"));
    perguntas.insert(make_pair("pernaslongas", "Seu animal tem pernas longas?"));
    perguntas.insert(make_pair("pretoebranco", "Seu animal eh preto e branco?"));
    perguntas.insert(make_pair("avestruz", "Seu animal eh um avestruz?"));
    perguntas.insert(make_pair("voa", "Seu animal voa?"));
    perguntas.insert(make_pair("nada", "Seu animal nada?"));
    perguntas.insert(make_pair("pinguim", "Seu animal eh um pinguim?"));
    perguntas.insert(make_pair("girafa", "Seu animal eh uma girafa?"));
    perguntas.insert(make_pair("corpoarredondado", "Seu animal tem um corpo arredondado?"));
    perguntas.insert(make_pair("penasdensas", "Seu animal tem penas densas?"));
    perguntas.insert(make_pair("domestico", "Seu animal eh domestico?"));
    perguntas.insert(make_pair("pescococomprido", "Seu animal tem pescococomprido"));
    perguntas.insert(make_pair("galinha", "Seu animal eh uma galinha?"));
    perguntas.insert(make_pair("caudacurta", "Seu animal tem cauda curta?"));
    perguntas.insert(make_pair("corderosa", "Seu animal eh cor de rosa?"));
    perguntas.insert(make_pair("flamingo", "Seu animal eh um flamingo?"));
    perguntas.insert(make_pair("mamifero", "Seu animal eh um mamifero?"));
    perguntas.insert(make_pair("dentespontiagudos", "Seu animal tem dentes pontiagudos?"));
    perguntas.insert(make_pair("garras", "Seu animal tem garras?"));
    perguntas.insert(make_pair("olhosfrontais", "Seu animal tem olhos frontais?"));
    perguntas.insert(make_pair("pelo", "Seu animal tem pelos?"));
    perguntas.insert(make_pair("daleite", "Seu animal da leite?"));
    perguntas.insert(make_pair("penas", "Seu animal tem penas?"));
    perguntas.insert(make_pair("botaovos", "Seu animal bota ovos?"));
    perguntas.insert(make_pair("comecarne", "Seu animal come carne?"));
    perguntas.insert(make_pair("casco", "Seu animal tem casco?"));
    perguntas.insert(make_pair("bomvoador", "Seu animal eh um bom voador?"));
    perguntas.insert(make_pair("albatroz", "Seu animal eh um albatroz?"));
    perguntas.insert(make_pair("rumina", "Seu animal rumina?"));
    perguntas.insert(make_pair("dedospares", "Seu animal tem quantidade de dedos pares?"));
}

int EncadeamentoParaTras(vector<regra> *regras, variavel objetivo)
{
    // verificar minha MTAk
    switch (AchouNaMT(&MTAk, objetivo))
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

    //cout << "objetivo atual: " << objetivo.nome << " = " << objetivo.valor << endl;
    for (int i = 0; i < regras->size(); i++)
    {
        for (int j = 0; j < regras->at(i).entao.size(); j++)
        {
            if (regras->at(i).entao[j].first.nome.compare(objetivo.nome) == 0)
            {
                if (regras->at(i).entao[j].first.valor.compare(objetivo.valor) == 0)
                {
                    regrasComOObjetivo.push_back(i);
                    //cout << "regra: " << i << endl;
                }
            }
        }
    }

    for (int regra : regrasComOObjetivo)
    {
        //cout << "regra: " << regra << endl;
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
            //cout << "VAR ATUAL: " << var.nome << " = " << var.valor << endl;
            se_variaveis.pop_back();

            int achei = EncadeamentoParaTras(regras, var);

            if (achei == 1)     continue;
            else
            {
                if (AchouNaMT(&MTAk, var) == 1)
                {
                    continue;
                }
                else if (AchouNaMT(&MTAk, var) == 0)
                {
                    deuBreak = true;
                    break;
                }

                char resposta;
                cout << perguntas[var.nome] << " [s / n] ";
                cin >> resposta;

                if (resposta == 's')
                {
                    AdicionarNaMT(&MTAk, {var.nome, "true"});

                    if (var.valor.compare("true") == 0) {
                        continue;
                    }
                    deuBreak = true;
                    break;
                }
                else if (resposta == 'n')
                {
                    AdicionarNaMT(&MTAk, {var.nome, "false"});

                    // se eu adicionei o que estava procurando eu continuo
                    if (var.valor.compare("false") == 0) {
                        continue;
                    }
                    deuBreak = true;
                    break;
                }
                else
                {
                    throw runtime_error("digite s ou n (sim ou nao)");
                }
            }
        }

        if (!deuBreak)
        {
            AdicionarNaMT(&MTAk, {objetivo.nome, objetivo.valor});
            //cout << "[" << varMTAk.nome << " = " << varMTAk.valor << "]" << endl;
            return 1;
        }
    }
    return -1;
}

void akinator(vector<regra> *regras)
{
    addMap();

    vector<variavel> objetivos = {
        {"leopardo", "true"}, {"tigre", "true"}, {"zebra", "true"}, {"avestruz", "true"}, {"pinguim", "true"},
        {"girafa", "true"}, {"galinha", "true"}, {"flamingo", "true"}, {"albatroz", "true"}
    };

    for (auto obj : objetivos)
    {
        if (EncadeamentoParaTras(regras, obj) == 1)
        {
            cout << perguntas[obj.nome] << " [s / n] ";
            char resposta;
            cin >> resposta;

            if (resposta == 's') {
                for (auto var : MTAk)
                {
                    cout << "[ " << var.nome << " = " << var.valor << " ]" << endl;
                }
                return;
            } else {
                continue;
            }
        }
    }

    for (auto var : MTAk)
    {
        cout << "[ " << var.nome << " = " << var.valor << " ]" << endl;
    }

    cout << "sinto muito nao existe esse animal na base de dados :/ " << endl;
}