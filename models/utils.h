#ifndef UTILS_H
#define UTILS_H

#include <string>

// Funções utilitárias relacionadas a datas

bool anoBissexto(int ano);
int diasNoMes(int mes, int ano);
bool dataValida(int ano, int mes, int dia);
int diaDaSemana(int ano, int mes, int dia);   // 0=Dom, 6=Sab
bool isFimDeSemana(int ano, int mes, int dia);
std::string nomeMes(int mes);

#endif