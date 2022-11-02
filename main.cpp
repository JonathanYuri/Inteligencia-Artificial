#include <iostream>
#include <string>
#include <vector>
#include <map>

#include "utils/IsLower.cpp"
#include "utils/readFile.cpp"
#include "utils/negarVariavel.cpp"

#include "utils/types.h"

#include "functions/fatos.cpp"
#include "functions/lexico.cpp"
#include "functions/Sintatico/SyntaticAnalyzer.h"
#include "functions/Sintatico/Estados.cpp"
#include "functions/Sintatico/RegraAtual.cpp"

using namespace std;

vector<variavel> MT;
vector<regra> regras;

map<string, string> perguntas;

void addmap()
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
    perguntas.insert(make_pair("rumina", "Seu animal eh uma rumina?"));
    perguntas.insert(make_pair("dedospares", "Seu animal tem quantidade de dedos pares?"));
}

vector<vector<string>> lexical(vector<string> lines)
{
    vector<vector<string>> rules;

    for (string line : lines)
    {
        if (line.length() == 0) continue;

        int character_stopped = 0;
        vector<string> rule;

        while (character_stopped != WAS_ENTIRE_COMMAND_VERIFIED)
        {
            //AnalisadorLexico
            string token = EncaminharOperadorOuPalavra(line, &character_stopped);
            rule.push_back(token);
        }
        rules.push_back(rule);
    }

    return rules;
}

void syntatic(vector<vector<string>> rules)
{
    for (int i = 0; i < rules.size(); i++)
    {
        if (rules[i].size() == 0) continue;

        int string_stopped = 0;
        bool imInEntao = false;

        while (string_stopped != WAS_ENTIRE_COMMAND_VERIFIED)
        {
            //AnalisadorSintatico
            ReconhecerSe(rules[i], &string_stopped, i);
        }
        regras.push_back(ObterRegraAtual());
    }
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

int AchouNaMT(variavel var)
{
    for (int k = 0; k < MT.size(); k++)
    {
        if (MT[k].nome.compare(var.nome) == 0)
        {
            if (MT[k].valor.compare(var.valor) == 0)     return 1;
            else    return 0;
        }
    }
    return -1;
}

void AdicionarNaMT(variavel var)
{
    switch (AchouNaMT(var))
    {
        case -1:
            MT.push_back(var);
            return;
        default:
            return;
    }
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

            AdicionarNaMT(varMT);
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
                    AdicionarNaMT(adc);
                    deuBreak = true;
                    break;
                }

                if (resultado == -1)
                {
                    variavel adc = se_var.first;
                    adc.valor = "indeterminado";
                    AdicionarNaMT(adc);
                    deuBreak = true;
                    break;
                }

                AdicionarNaMT(se_var.first);
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
                AdicionarNaMT(entao_var.first);
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
                    AdicionarNaMT(entao_var.first);
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

bool ObjetivoVerdadeiro(int escolha, variavel objetivo)
{
    vector<variavel> MTantes = MT;

    cout << "-------------------";
    int achei = 0, acheiFalse = 0;
    if (escolha == 0)
    {
        achei = EncadeamentoParaTras(objetivo);

        variavel objetivo2 = NegarVariavel(objetivo);

        // voltar a memória de trabalho
        vector<variavel> MTprimeira = MT;
        MT = MTantes;

        acheiFalse = EncadeamentoParaTras(objetivo2);

        ChecarContradicao(objetivo, objetivo2, achei, acheiFalse);

        if (achei == 1)     MT = MTprimeira;
        if (achei == 1 && acheiFalse == 1)  AdicionarNaMT(objetivo2);
    }

    else if (escolha == 1)
    {
        vector<int> regrasNaoUsadas;
        vector<int> r;
        for (int i = 0; i < regras.size(); i++)
        {
            regrasNaoUsadas.push_back(i);
        }

        achei = EncadeamentoParaFrente(objetivo, regrasNaoUsadas);

        vector<variavel> MTprimeira = MT;
        MT = MTantes;

        variavel objetivo2 = NegarVariavel(objetivo);

        // procurar pelo objetivo
        if (achei == 0) {
            acheiFalse = 1;
            achei = EncadeamentoParaTras(objetivo);
        }
        else{
            acheiFalse = EncadeamentoParaTras(objetivo2);
        }

        ChecarContradicao(objetivo, objetivo2, achei, acheiFalse);

        if (achei == 1)     MT = MTprimeira;
        if (achei == 1 && acheiFalse == 1)  AdicionarNaMT(objetivo2);
    }

    else if (escolha == 2)
    {
        vector<int> regrasNaoUsadas;
        vector<int> r;
        for (int i = 0; i < regras.size(); i++)
        {
            regrasNaoUsadas.push_back(i);
        }

        achei = EncadeamentoMisto(objetivo, regrasNaoUsadas);
        variavel objetivo2 = NegarVariavel(objetivo);

        vector<variavel> MTprimeira = MT;
        MT = MTantes;

        if (achei == 0) {
            acheiFalse = 1;
            achei = EncadeamentoParaTras(objetivo);
        }
        else{
            acheiFalse = EncadeamentoParaTras(objetivo2);
        }

        ChecarContradicao(objetivo, objetivo2, achei, acheiFalse);

        if (achei == 1)     MT = MTprimeira;
        if (achei == 1 && acheiFalse == 1)  AdicionarNaMT(objetivo2);
    }
    cout << "-------------------" << endl;

    cout << endl << "\tMemoria de Trabalho:" << endl;
    for (auto var : MT)
    {
        cout << var.nome << " = " << var.valor << endl;
    }

    return achei == 1;
}

void testarVariaveis()
{
    int qntVariaveis = 0;
    cout << "Digite quantas variaveis quer testar: ";
    cin >> qntVariaveis;

    if (qntVariaveis == 0)  throw runtime_error("Digite um numero maior que 0");

    vector<variavel> MTantes = MT;
    vector<variavel> objetivos;

    bool objetivosVerdadeiros = true;

    for (int i = 0; i < qntVariaveis; i++)
    {
        MT = MTantes;
        variavel objetivo;

        cout << "Digite o nome da variavel: ";
        cin >> objetivo.nome;
        cout << "Digite o valor da variavel: ";
        cin >> objetivo.valor;

        if (objetivo.valor.compare("true") != 0 && objetivo.valor.compare("false") != 0)    throw runtime_error("objetivo deve ser true ou false");

        if (!EveryLetterIsLower(objetivo.nome))     throw runtime_error("variavel objetivo deve ter todas as letras minusculas");

        objetivos.push_back(objetivo);

        cout << "Digite:\n0 para usar o encadeamento para tras\n1 para usar o para frente\n2 para usar o misto" << endl << endl;
        int escolha = 0;
        cin >> escolha;
        
        bool objVerdadeiro = ObjetivoVerdadeiro(escolha, objetivo);
        if (!objVerdadeiro)     objetivosVerdadeiros = false;
        cout << endl;
    }

    cout << "-------------------";
    for (int i = 0; i < objetivos.size(); i++)
    {
        cout << objetivos[i].nome << "=" << objetivos[i].valor;
        if (i != objetivos.size() - 1)      cout << " & ";
    }
    if (objetivosVerdadeiros)   cout << " = TRUE";
    else    cout << " = FALSE";
    cout << "-------------------";
}

int EncadeamentoParaTrasAkinator(variavel objetivo)
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

    cout << "objetivo atual: " << objetivo.nome << " = " << objetivo.valor << endl;
    for (int i = 0; i < regras.size(); i++)
    {
        for (int j = 0; j < regras[i].entao.size(); j++)
        {
            if (regras[i].entao[j].first.nome.compare(objetivo.nome) == 0)
            {
                if (regras[i].entao[j].first.valor.compare(objetivo.valor) == 0)
                {
                    regrasComOObjetivo.push_back(i);
                    cout << "regra: " << i << endl;
                }
            }
        }
    }

    for (int regra : regrasComOObjetivo)
    {
        cout << "regra: " << regra << endl;
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
            cout << "VAR ATUAL: " << var.nome << " = " << var.valor << endl;
            se_variaveis.pop_back();

            int achei = EncadeamentoParaTrasAkinator(var);

            if (achei == 1)     continue;
            else
            {
                char resposta;
                cout << perguntas[var.nome] << " [s / n] ";
                cin >> resposta;

                if (resposta == 's')
                {
                    AdicionarNaMT(var);
                    continue;
                }
                else if (resposta == 'n')
                {
                    AdicionarNaMT(NegarVariavel(var));
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
            variavel varMT;
            varMT.nome = objetivo.nome;
            varMT.valor = objetivo.valor;

            AdicionarNaMT(varMT);
            cout << "[" << varMT.nome << " = " << varMT.valor << "]" << endl;
            return 1;
        }
    }
    return -1;
}

void akinator()
{
    EncadeamentoParaTrasAkinator(regras[0].entao[0].first);  
    /*
    for (auto c : regras)
    {
        cout << "SE: " << endl;
        for (auto se_var : c.se)
        {
            cout << "[" << perguntas[se_var.first.nome] << " = " << se_var.first.valor << "]" << endl;
        }
        cout << "ENTAO: " << endl;
        for (auto entao_var : c.entao)
        {
            cout << "[" << perguntas[entao_var.first.nome] << " = " << entao_var.first.valor << "]" << endl;
        }
    }*/
}

int main()
{
    cout << "Digite: \n(1): para usar o modo adivinho\n(2): para usar consultar uma variavel" << endl;
    vector<string> lines;

    int escolha = 0;
    cin >> escolha;

    string conhecimento;
    if (escolha == 1)   conhecimento = "rules-akinator.txt";
    else if (escolha == 2)    conhecimento = "rules.txt";
    else    return 0;

    lines = readFile(conhecimento);
    vector<vector<string>> rules = lexical(lines);
    syntatic(rules);

    if (escolha == 1)
    {
        addmap();
        akinator();
    }
    else if (escolha == 2)
    {
        vector<string> facts = readFile("facts.txt");
        vector<vector<string>> linhasFatos = lexical(facts);
        for (vector<string> r : linhasFatos)    AdicionarNaMT(ReconhecerVariavel(r));

        testarVariaveis();
    }
    return 0;
}
