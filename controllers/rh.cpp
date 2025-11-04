#include "rh.h"
#include "../models/utils.h"


// Adiciona um colaborador
bool RH::adicionarColaborador(const std::string& nome) {
    // Percorre o vetor de colaboradores para verificar duplicados
    for (const auto& c : colaboradores) {
        if (c.getNome() == nome) return false;// se já existe, não adiciona
    }
    // Adiciona novo colaborador ao vetor
    colaboradores.push_back(Colaborador(nome));
    return true;
}

// Verifica se um colaborador existe
bool RH::existeColaborador(const std::string& nome) const {
    // Pesquisa linear no vetor de colaboradores
    for (const auto& c : colaboradores) {
        if (c.getNome() == nome) return true;
    }
    return false;
}

// Obtém um pointer para um colaborador específico
Colaborador* RH::obterColaborador(const std::string& nome) {
    for (auto& c : colaboradores) {
        if (c.getNome() == nome) return &c;
    }
    return nullptr; // colaborador não encontrado
}

// Marca férias ou faltas para um colaborador numa data específica
bool RH::marcar(const std::string& nome, int a, int m, int d, char tipo) {
    // Verifica se o colaborador existe
    Colaborador* c = obterColaborador(nome);
    if (!c) return false;
    // Valida se a data é válida (ano entre 1900-2100, mês 1-12, dia correto)
    if (!dataValida(a, m, d)) return false;
    if (isFimDeSemana(a, m, d)) return false; // regra: não marcar ao fim de semana
    // Adiciona a marcação ao colaborador
    c->adicionarMarcacao(a, m, d, tipo);
    return true;
}
// Remove uma marcação de férias/falta de um colaborador
bool RH::desmarcar(const std::string& nome, int a, int m, int d) {
    // Verifica se o colaborador existe
    Colaborador* c = obterColaborador(nome);
    if (!c) return false;
    return c->removerMarcacao(a, m, d);
}
