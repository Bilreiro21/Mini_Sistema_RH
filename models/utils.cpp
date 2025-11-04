#include "../models/utils.h"

// Verifica se um ano é bissexto
bool anoBissexto(int ano) {
    return ((ano%4==0 && ano%100!=0) || (ano%400==0));
}

int diasNoMes(int mes, int ano) {
    switch(mes){
        case 1: case 3: case 5: case 7: case 8: case 10: case 12: return 31;
        case 4: case 6: case 9: case 11: return 30;
        case 2: return anoBissexto(ano) ? 29 : 28;
        default: return 30;
    }
}
// Calcula o dia da semana usando a Congruência de Zeller
int diaDaSemana(int ano, int mes, int dia) {
    // Ajuste necessário para o algoritmo: Jan e Fev são tratados como meses 13 e 14 do ano anterior
    if (mes < 3) { 
        mes += 12; ano--; 
    }
    int k = ano % 100;
    int j = ano / 100;
    int h = (dia + 13*(mes+1)/5 + k + k/4 + j/4 + 5*j) % 7;
    int d = (h + 6) % 7; // 0 = Domingo, 6 = Sábado
    return d;
}

bool isFimDeSemana(int ano, int mes, int dia) {
    int dw = diaDaSemana(ano, mes, dia);
    return (dw == 0 || dw == 6);
}

std::string nomeMes(int mes){
    const std::string meses[] = {"Janeiro","Fevereiro","Março","Abril","Maio","Junho","Julho","Agosto","Setembro","Outubro","Novembro","Dezembro"};
    // Verifica se o mês é válido (1-12)
    if (mes >= 1 && mes <= 12) 
        return meses[mes-1];
    return "???"; // Retorna "???" para mês inválido
}

bool dataValida(int ano, int mes, int dia) {
    // Limita anos a intervalo razoável
    if (ano < 1900 || ano > 2100) return false;
    // Verifica se mês é válido
    if (mes < 1 || mes > 12) return false;
    // Verifica se dia é válido para o mês específico (considera bissextos)
    if (dia < 1 || dia > diasNoMes(mes, ano)) return false;
    return true;
}
