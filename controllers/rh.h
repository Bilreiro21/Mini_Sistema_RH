#ifndef RH_H
#define RH_H

#include "../models/colaborador.h"
#include <vector>
#include <string>

class RH
{
private:
    // Vetor que armazena todos os colaboradores do sistema
    std::vector<Colaborador> colaboradores;

public:
    // Adiciona um novo colaborador (evita duplicados)
    bool adicionarColaborador(const std::string &nome);
    // Verifica se um colaborador existe
    bool existeColaborador(const std::string &nome) const;
    // Obtém um pointer para o colaborador pelo nome (ou nullptr se não existir)
    Colaborador *obterColaborador(const std::string &nome);
    // Lista todos os colaboradores 
    const std::vector<Colaborador> &listar() const
    {
        return colaboradores;
    }

    // Marca férias ou faltas para um colaborador numa data específica
    bool marcar(const std::string &nome, int a, int m, int d, char tipo);
    // Remove uma marcação de férias/falta de um colaborador
    bool desmarcar(const std::string &nome, int a, int m, int d);
};

#endif
