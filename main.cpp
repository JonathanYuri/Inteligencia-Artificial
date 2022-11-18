#include <iostream>
#include <string>
#include <vector>

#include "utils/IsLower.cpp"
#include "utils/readFile.cpp"
#include "utils/negarVariavel.cpp"
#include "utils/functionsMT.cpp"
#include "utils/types.h"

#include "functions/fatos.cpp"
#include "functions/lexico.cpp"
#include "functions/Sintatico/SyntaticAnalyzer.h"
#include "functions/Sintatico/Estados.cpp"
#include "functions/Sintatico/RegraAtual.cpp"

#include "modes/modes.h"
#include "modes/modes.cpp"

using namespace std;

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

vector<regra> syntatic(vector<vector<string>> rules)
{
    vector<regra> regras;
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
    return regras;
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
    vector<regra> regras = syntatic(rules);

    if (escolha == 1)
    {
        akinator(regras);
    }
    else if (escolha == 2)
    {
        vector<string> facts = readFile("facts.txt");
        vector<vector<string>> linhasFatos = lexical(facts);

        vector<pair<variavel, float>> MT;
        for (vector<string> r : linhasFatos)    AdicionarNaMT(&MT, ReconhecerVariavel(r), 1.0f);

        questions(regras, MT);
    }
    return 0;
}
