#ifndef RH_H
#define RH_H

#include "../models/colaborador.h"
#include <vector>
#include <string>
#include <map>
#include <utility>

class RH
{
private:
    // Vetor que armazena todos os colaboradores do sistema
    std::vector<Colaborador> colaboradores;

public:
    // Adiciona um novo colaborador (evita duplicados)
    // Agora aceita departamento opcional
    bool adicionarColaborador(const std::string &nome, const std::string &departamento = "Geral", int id = 0);
    
    // Verifica se um colaborador existe
    bool existeColaborador(const std::string &nome) const;
    
    // Obtém um pointer para o colaborador pelo nome (ou nullptr se não existir)
    Colaborador *obterColaborador(const std::string &nome);
    
    // Obtém um pointer para o colaborador pelo ID (ou nullptr se não existir)
    Colaborador *obterColaboradorPorId(int id);

    // Lista todos os colaboradores 
    const std::vector<Colaborador> &listar() const;

    // Marca férias ou faltas para um colaborador numa data específica
    bool marcar(const std::string &nome, int a, int m, int d, char tipo);
    // Remove uma marcação de férias/falta de um colaborador
    bool desmarcar(const std::string &nome, int a, int m, int d);

    // Estatísticas
    // Retorna mapa: Departamento -> {total_ferias, total_faltas}
    std::map<std::string, std::pair<int, int>> getEstatisticasDepartamento() const;

    // Verifica conflito de férias
    // Retorna true se houver OUTRO colaborador do MESMO departamento com férias nesse dia
    bool verificarConflitoFerias(const std::string& nomeColab, int a, int m, int d);
};

#endif
