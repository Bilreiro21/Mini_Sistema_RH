#ifndef COLABORADOR_H
#define COLABORADOR_H

#include <string>
#include <map>
#include <vector>

/* Estrutura para armazenar as marcações de faltas e férias de um colaborador */
struct Marcacao {
    int dia;
    int mes;
    int ano;
    char tipo; // 'F' para as férias, 'X' para as faltas.
};

class Colaborador {
private:
    std::string nome; // Nome único do colaborador
    std::vector<Marcacao> marcacoes; // Lista de todas as marcações

public:
    // Construtores, este é o padrão
    Colaborador(){}
    // Construtor com nome
    Colaborador(const std::string& nome) : nome(nome) {}
    // Getters e Setters
    // Obtém o nome do colaborador
    const std::string& getNome() const { 
        return nome; 
    }
    // Define/altera o nome do colaborador
    void setNome(const std::string& n) { 
        nome = n; 
    }
    // Obtém todas as marcações do colaborador
    const std::vector<Marcacao>& getMarcacoes() const {
        return marcacoes;
    }

    // Vai adicionar uma marcação se não existir uma para esse dia.
    bool adicionarMarcacao(int a, int m, int d, char t);
    // Vai remover a marcação se existir.
    bool removerMarcacao(int a, int m, int d);
    // Devolve o tipo marcado nesse dia ou 0.
    char obterMarcacao(int a, int m, int d) const;
};

#endif