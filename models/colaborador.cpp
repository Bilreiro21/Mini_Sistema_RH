#include "../models/colaborador.h"

bool Colaborador::adicionarMarcacao(int a, int m, int d, char t) {

    // Percorre o vetor de marcações existentes
    for (auto &mk : marcacoes) {
        // Verifica se já existe uma marcação para esta data
        if (mk.ano == a && mk.mes == m && mk.dia == d) {
            // já existe, vai atualizar
            mk.tipo = t;
            return true;
        }
    }
    // Não existe: cria nova marcação e adiciona ao vetor
    Marcacao nova{d, m, a, t};
    marcacoes.push_back(nova);
    return true;
}

// Remove uma marcação específica pela data
bool Colaborador::removerMarcacao(int a, int m, int d) {
    // Percorre o vetor com iterador para permitir remoção
    for (auto i = marcacoes.begin(); i != marcacoes.end(); ++i){
        // Verifica se é a marcação procurada
        if (i -> ano == a && i -> mes == m && i -> dia == d) {
            marcacoes.erase(i); // Remove a marcação
            return true;
        }
    }
    return false; // Não encontrou a marcação
}

// Consulta o tipo de marcação numa data específica
char Colaborador::obterMarcacao(int a, int m, int d) const{
    // Procura a marcação correspondente à data
    for (const auto &mk : marcacoes) {
        if (mk.ano == a && mk.mes == m && mk.dia == d) {
            return mk.tipo; // Retorna 'F' ou 'X'
        }
    }
    return 0; // Sem marcação, retorna 0
}