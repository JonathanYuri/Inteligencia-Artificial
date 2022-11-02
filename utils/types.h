#include <string>

#define WAS_ENTIRE_COMMAND_VERIFIED -1

#pragma once

struct variavel{
    string nome;
    string valor;
};

struct regra{
    vector<pair<variavel, string>> se;
    vector<pair<variavel, string>> entao;
};