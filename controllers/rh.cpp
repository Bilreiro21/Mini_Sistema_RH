#include "rh.h"
#include "../models/utils.h"
#include <algorithm>

// Tenta adicionar um novo colaborador ao sistema
// Retorna true se o nome for único e adicionar com sucesso, false caso contrário
bool RH::adicionarColaborador(const std::string& nome, const std::string& departamento, int id) {
    // Percorre o vetor de colaboradores para verificar duplicados
    for (const auto& c : colaboradores) {
        if (c.getNome() == nome) return false;// se já existe, não adiciona
    }
    
    int novoId = id;
    // Se id for 0, gera um novo ID sequencial
    if (novoId == 0) {
        int maxId = 0;
        for(const auto& c : colaboradores) {
            if(c.getId() > maxId) maxId = c.getId();
        }
        novoId = maxId + 1;
    }

    // Adiciona novo colaborador ao vetor
    colaboradores.push_back(Colaborador(nome, novoId, departamento));
    return true;
}

// Verifica se um colaborador já existe pelo nome
bool RH::existeColaborador(const std::string& nome) const {
    // Pesquisa linear no vetor de colaboradores
    for (const auto& c : colaboradores) {
        if (c.getNome() == nome) return true;
    }
    return false;
}

// Obtém um pointer para um colaborador específico pelo nome
// Retorna nullptr se não encontrar
Colaborador* RH::obterColaborador(const std::string& nome) {
    for (auto& c : colaboradores) {
        if (c.getNome() == nome) return &c;
    }
    return nullptr; 
}

// Obtém um pointer para um colaborador específico pelo ID
Colaborador* RH::obterColaboradorPorId(int id) {
    for (auto& c : colaboradores) {
        if (c.getId() == id) return &c;
    }
    return nullptr;
}

// Retorna a lista completa de colaboradores
const std::vector<Colaborador>& RH::listar() const {
    return colaboradores;
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
    return c->adicionarMarcacao(a, m, d, tipo);
}

// Remove uma marcação de férias/falta de um colaborador
bool RH::desmarcar(const std::string& nome, int a, int m, int d) {
    // Verifica se o colaborador existe
    Colaborador* c = obterColaborador(nome);
    if (!c) return false;
    return c->removerMarcacao(a, m, d);
}

// Calcula estatísticas de ausências por departamento
// Retorna um mapa: Departamento -> {Total Férias, Total Faltas}
std::map<std::string, std::pair<int, int>> RH::getEstatisticasDepartamento() const {
    std::map<std::string, std::pair<int, int>> stats; 
    
    for (const auto& c : colaboradores) {
        std::string dep = c.getDepartamento();
        for (const auto& mk : c.getMarcacoes()) {
            if (mk.tipo == 'F') stats[dep].first++;
            else if (mk.tipo == 'X') stats[dep].second++;
        }
    }
    return stats;
}

// Verifica se há conflito de férias (outro colega do mesmo departamento já tem férias no dia)
bool RH::verificarConflitoFerias(const std::string& nomeColab, int a, int m, int d) {
    Colaborador* atual = obterColaborador(nomeColab);
    if (!atual) return false;

    std::string dep = atual->getDepartamento();

    for (const auto& c : colaboradores) {
        // Ignora o próprio colaborador
        if (c.getNome() == nomeColab) continue;

        // Verifica se é do mesmo departamento
        if (c.getDepartamento() == dep) {
            // Verifica se tem férias nesse dia
            if (c.obterMarcacao(a, m, d) == 'F') {
                return true;
            }
        }
    }
    return false;
}
