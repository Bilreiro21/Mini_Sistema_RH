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

struct Formacao {
    std::string nome_curso;
    std::string data_conclusao;
};

struct Nota {
    std::string texto;
    std::string data;
};

class Colaborador {
private:
    std::string nome; // Nome único do colaborador
    int id;
    std::string departamento;
    std::vector<Marcacao> marcacoes; // Lista de todas as marcações
    std::vector<Formacao> formacoes;
    std::vector<Nota> notas;

public:
    // Construtores, este é o padrão
    Colaborador() : id(0) {}
    // Construtor com nome
    Colaborador(const std::string& nome, int id = 0, const std::string& dep = "Geral") 
        : nome(nome), id(id), departamento(dep) {}
    
    // Getters e Setters
    const std::string& getNome() const { return nome; }
    void setNome(const std::string& n) { nome = n; }

    int getId() const { return id; }
    void setId(int i) { id = i; }

    const std::string& getDepartamento() const { return departamento; }
    void setDepartamento(const std::string& d) { departamento = d; }

    const std::vector<Marcacao>& getMarcacoes() const { return marcacoes; }
    
    // Gestão de Formações
    const std::vector<Formacao>& getFormacoes() const { return formacoes; }
    void adicionarFormacao(const std::string& curso, const std::string& data);
    void removerFormacao(int index);
    void editarFormacao(int index, const std::string& novoCurso, const std::string& novaData);

    // Gestão de Notas
    const std::vector<Nota>& getNotas() const { return notas; }
    void adicionarNota(const std::string& texto, const std::string& data);
    void removerNota(int index);
    void editarNota(int index, const std::string& novoTexto, const std::string& novaData);

    // Vai adicionar uma marcação se não existir uma para esse dia.
    bool adicionarMarcacao(int a, int m, int d, char t);
    // Vai remover a marcação se existir.
    bool removerMarcacao(int a, int m, int d);
    // Devolve o tipo marcado nesse dia ou 0.
    char obterMarcacao(int a, int m, int d) const;
};

#endif