#include <iostream>
#include <map>

#include "../modes.h"
#include "../../utils/types.h"

#pragma once

using namespace std;

map<string, string> create_questions()
{
    map<string, string> perguntas;

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

    return perguntas;
}

int ProcurarNaMT(vector<pair<variavel, int>> *MT, variavel var)
{
    for (int k = 0; k < MT->size(); k++)
    {
        if (MT->at(k).first.nome.compare(var.nome) == 0)
        {
            if (MT->at(k).first.valor.compare(var.valor) == 0)     return 1;
            else    return 0;
        }
    }
    return -1;
}

void AddMT(vector<pair<variavel, int>> *MT, variavel var, int regra)
{
    switch (ProcurarNaMT(MT, var))
    {
        case -1:
            MT->push_back({var, regra});
            return;
        default:
            return;
    }
}

int EncadeamentoParaTras(map<string, string> *perguntas, vector<regra> *regras, vector<pair<variavel, int>> *MT, variavel objetivo)
{
    switch (ProcurarNaMT(MT, objetivo))
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

            int achei = EncadeamentoParaTras(perguntas, regras, MT, var);

            if (achei == 1)     continue;
            else
            {
                if (ProcurarNaMT(MT, var) == 1)
                {
                    continue;
                }
                else if (ProcurarNaMT(MT, var) == 0)
                {
                    deuBreak = true;
                    break;
                }

                char resposta;
                cout << perguntas->at(var.nome) << " [s / n] ";
                cin >> resposta;

                if (resposta == 's')
                {
                    AddMT(MT, {var.nome, "true"}, -1);

                    if (var.valor.compare("true") == 0) {
                        continue;
                    }
                    deuBreak = true;
                    break;
                }
                else if (resposta == 'n')
                {
                    AddMT(MT, {var.nome, "false"}, -1);

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
            AddMT(MT, {objetivo.nome, objetivo.valor}, regra);
            return 1;
        }
    }
    return -1;
}

void printarRegra(vector<regra> regras, int i)
{
    cout << "Regra " << i << ": ";
    cout << "SE ";
    for (int n = 0; n < regras[i].se.size(); n++)
    {
        cout << regras[i].se[n].first.nome << " = " << regras[i].se[n].first.valor;
        if (n != regras[i].se.size() - 1)   cout << " & ";
    }
    cout << " ENTAO ";
    for (int n = 0; n < regras[i].entao.size(); n++)
    {
        cout << regras[i].entao[n].first.nome << " = " << regras[i].entao[n].first.valor;
        if (n != regras[i].entao.size() - 1)   cout << " & ";
    }
    cout << endl;
}

void printarMT(vector<pair<variavel, int>> MT, vector<regra> regras)
{
    vector<pair<variavel, int>> deduzidos;
    vector<pair<variavel, int>> respondidos;

    for (auto var : MT)
    {
        if (var.second == -1) {
            respondidos.push_back(var);
        } else {
            deduzidos.push_back(var);
        }
    }

    cout << endl << "Respondidos: " << endl << endl;
    for (auto var : respondidos)
    {
        cout << "[ " << var.first.nome << " = " << var.first.valor << " ]" << endl;
    }
    cout << endl;
    cout << "Deduzidos: " << endl << endl;
    for (auto var : deduzidos)
    {
        cout << "[ " << var.first.nome << " = " << var.first.valor << " ], ";
        cout << " Por causa da regra: " << var.second << endl;
        printarRegra(regras, var.second);
        cout << endl;
    }
}

bool exist_in_vector(vector<variavel> vetor, variavel var)
{
    for (variavel v : vetor)
    {
        if (var.nome.compare(v.nome) == 0 && var.valor.compare(v.valor) == 0)
        {
            return true;
        }
    }
    return false;
}

void chute(vector<pair<variavel, int>> *MT, vector<regra> regras, vector<variavel> objetivos)
{
    // 1 variavel objetivo so vai poder aparecer em uma regra
    map<string, vector<variavel>> dependencias;

    for (auto regra : regras)
    {
        for (auto var_entao : regra.entao)
        {
            if (exist_in_vector(objetivos, var_entao.first))
            {
                // adc variaveis do se
                vector<variavel> se;
                for (auto var_se : regra.se)
                {
                    se.push_back(var_se.first);
                }

                //dependencias.insert(make_pair(var_entao.first, "se"));
                dependencias[var_entao.first.nome] = se;
                continue; // 1 variavel objetivo so vai poder aparecer em uma regra
            }
        }
    }

    map<string, float> porcentagens;
    for (auto iter = dependencias.begin(); iter != dependencias.end(); ++iter){
        float qnt_certos = 0;
        for (auto se : iter->second)
        {
            //cout << se.nome << " = " << se.valor << endl;
            if (ProcurarNaMT(MT, se) == 1) {
                //cout << "variavel " << se.nome << " = " << se.valor << " esta certa" << endl;
                qnt_certos += 1;
            }
        }
        //cout << "porcentagem de " << iter->first << " = " << (qnt_certos / (iter->second.size() * 1.0f)) << endl;
        porcentagens[iter->first] = (qnt_certos / iter->second.size());
    }

    pair<string, float> maior_acerto = {"Nenhum", .0f};
    for (auto iter = porcentagens.begin(); iter != porcentagens.end(); ++iter){
        if (iter->second >= maior_acerto.second) {
            maior_acerto.first = iter->first;
            maior_acerto.second = iter->second;
        }
    }

    cout << endl << "Nao existe um animal na base de dados que se encaixe com o descrito, mas" << endl;
    cout << "A maior probabilidade eh desse animal ser um(a) " << maior_acerto.first << " com probabilidade de: " << maior_acerto.second << endl;
}

void akinator(vector<regra> regras)
{
    map<string, string> perguntas = create_questions();
    vector<pair<variavel, int>> MT;

    vector<variavel> objetivos = {
        {"leopardo", "true"}, {"tigre", "true"}, {"zebra", "true"}, {"avestruz", "true"}, {"pinguim", "true"},
        {"girafa", "true"}, {"galinha", "true"}, {"flamingo", "true"}, {"albatroz", "true"}
    };

    /*cout << "regras: " << endl;
    for (int i = 0; i < regras.size(); i++)
    {
        printarRegra(regras, i);
    }*/

    cout << endl;

    for (auto obj : objetivos)
    {
        if (EncadeamentoParaTras(&perguntas, &regras, &MT, obj) == 1)
        {
            cout << perguntas[obj.nome] << " [s / n] ";
            char resposta;
            cin >> resposta;

            if (resposta == 's') {
                printarMT(MT, regras);
                return;
            } else {
                continue;
            }
        }
    }

    //printarMT(MT, regras);
    
    chute(&MT, regras, objetivos);
}