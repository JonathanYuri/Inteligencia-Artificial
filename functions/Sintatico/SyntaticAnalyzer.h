#pragma once
#include <vector>
#include <string>
#include <iostream>

#include "../../utils/IsLower.cpp"
#include "../../utils/types.h"

using namespace std;

void ReconhecerSe (vector<string> rule, int *string_stopped, int linha);

void ReconhecerVarNoSe(vector<string> rule, int *string_stopped, int linha, string operador);

void ReconhecerOperadorNoSe(vector<string> rule, int *string_stopped, int linha, variavel varSE, string operador);

void ReconhecerValorNoSe(vector<string> rule, int *string_stopped, int linha, variavel varSE, string operador);

void ReconhecerEOuEntao(vector<string> rule, int *string_stopped, int linha);

void ReconhecerVarNoEntao(vector<string> rule, int *string_stopped, int linha, string operador);

void ReconhecerOperadorNoEntao(vector<string> rule, int *string_stopped, int linha, variavel varENTAO, string operador);

void ReconhecerValorNoEntao(vector<string> rule, int *string_stopped, int linha, variavel varENTAO, string operador);

void ReconhecerFinalOuContinuar(vector<string> rule, int *string_stopped);