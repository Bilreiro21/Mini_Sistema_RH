#include "colaborador.h"

// Adiciona uma marcação se não houver conflito (dia já marcado)
// Retorna true se adicionou com sucesso, false se já existia
bool Colaborador::adicionarMarcacao(int a, int m, int d, char t) {
    // Verificar se já existe marcação para este dia
    for (const auto& marc : marcacoes) {
        if (marc.ano == a && marc.mes == m && marc.dia == d) {
            return false; // Já existe
        }
    }
    // Cria e adiciona a nova marcação
    Marcacao nova;
    nova.ano = a;
    nova.mes = m;
    nova.dia = d;
    nova.tipo = t;
    marcacoes.push_back(nova);
    return true;
}

// Remove uma marcação existente
// Retorna true se encontrou e removeu, false caso contrário
bool Colaborador::removerMarcacao(int a, int m, int d) {
    for (auto it = marcacoes.begin(); it != marcacoes.end(); ++it) {
        if (it->ano == a && it->mes == m && it->dia == d) {
            marcacoes.erase(it); // Remove do vetor
            return true;
        }
    }
    return false;
}

// Devolve o tipo de marcação ('F' ou 'X') para um dia específico, ou 0 se não houver
char Colaborador::obterMarcacao(int a, int m, int d) const {
    for (const auto& marc : marcacoes) {
        if (marc.ano == a && marc.mes == m && marc.dia == d) {
            return marc.tipo;
        }
    }
    return 0; // Não encontrado
}

// --- Gestão de Formações ---

// Adiciona um novo curso à lista de formações do colaborador
void Colaborador::adicionarFormacao(const std::string& curso, const std::string& data) {
    Formacao f;
    f.nome_curso = curso;
    f.data_conclusao = data;
    formacoes.push_back(f);
}

// Remove um curso pelo índice na lista
void Colaborador::removerFormacao(int index) {
    if (index >= 0 && index < (int)formacoes.size()) {
        formacoes.erase(formacoes.begin() + index);
    }
}

// Edita os dados de um curso existente
// Se a string for vazia, mantém o valor original
void Colaborador::editarFormacao(int index, const std::string& novoCurso, const std::string& novaData) {
    if (index >= 0 && index < (int)formacoes.size()) {
        if (!novoCurso.empty()) formacoes[index].nome_curso = novoCurso;
        if (!novaData.empty()) formacoes[index].data_conclusao = novaData;
    }
}

// --- Gestão de Notas ---

// Adiciona uma nota interna ao colaborador
void Colaborador::adicionarNota(const std::string& texto, const std::string& data) {
    Nota n;
    n.texto = texto;
    n.data = data;
    notas.push_back(n);
}

// Remove uma nota pelo índice
void Colaborador::removerNota(int index) {
    if (index >= 0 && index < (int)notas.size()) {
        notas.erase(notas.begin() + index);
    }
}

// Edita o texto ou data de uma nota existente
void Colaborador::editarNota(int index, const std::string& novoTexto, const std::string& novaData) {
    if (index >= 0 && index < (int)notas.size()) {
        if (!novoTexto.empty()) notas[index].texto = novoTexto;
        if (!novaData.empty()) notas[index].data = novaData;
    }
}