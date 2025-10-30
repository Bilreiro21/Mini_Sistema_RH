#ifndef COLABORADOR_H
#define COLABORADOR_H

#include <string>
#include <map>
#include <vector>

struct Marcacao {
    int dia;
    int mes;
    int ano;
    char tipo; // 'F' para as férias, 'X' para as faltas.
};

class Colaborador {
private:
    std::string nome;
    std::vector<Marcacao> marcacoes;

public:
    Colaborador(){}
    Colaborador(const std::string& nome) : nome(nome) {}

    const std::string& getNome() const { 
        return nome; 
    }

    void setNome(const std::string& n) { 
        nome = n; 
    }

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

#endif // COLABORADOR_H