#include <string>

#pragma once

struct variavel{
    string nome;
    string valor;
};

struct regra{
    vector<pair<variavel, string>> se;
    vector<pair<variavel, string>> entao;
};