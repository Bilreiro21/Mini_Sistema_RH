#include "io.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm> // Para std::all_of

using namespace std;

namespace IO {

    // Cifra simples de César para ofuscar nomes no ficheiro
    // Desloca cada caractere 1 posição para a frente na tabela ASCII
    string cifrar(const string& s) {
        string r = s;
        for (auto& c : r) c++;
        return r;
    }

    // Descifra a string deslocando cada caractere 1 posição para trás
    string decifrar(const string& s) {
        string r = s;
        for (auto& c : r) c--;
        return r;
    }

    // Guarda todos os dados do sistema num ficheiro de texto
    // Formato: ID;NomeCifrado;Departamento
    //          M;Ano;Mes;Dia;Tipo
    //          F;NomeCurso;Data
    //          N;TextoNota;Data
    bool guardar(const RH& rh, const string& ficheiro) {
        ofstream ofs(ficheiro);
        if (!ofs.is_open()) return false;

        for (const auto& c : rh.listar()) {
            // Guarda dados básicos do colaborador
            ofs << c.getId() << ";" << cifrar(c.getNome()) << ";" << c.getDepartamento() << "\n";
            
            // Guarda as marcações (Férias/Faltas)
            for (const auto& m : c.getMarcacoes()) {
                ofs << "M;" << m.ano << ";" << m.mes << ";" << m.dia << ";" << m.tipo << "\n";
            }

            // Guarda as formações
            for (const auto& f : c.getFormacoes()) {
                ofs << "F;" << f.nome_curso << ";" << f.data_conclusao << "\n";
            }

            // Guarda as notas
            for (const auto& n : c.getNotas()) {
                ofs << "N;" << n.texto << ";" << n.data << "\n";
            }
        }
        return true;
    }

    // Carrega os dados do ficheiro para o sistema
    bool carregar(RH& rh, const string& ficheiro) {
        ifstream ifs(ficheiro);
        if (!ifs.is_open()) return false;

        string linha;
        Colaborador* atual = nullptr;

        while (getline(ifs, linha)) {
            if (linha.empty()) continue;

            stringstream ss(linha);
            
            // Verifica o tipo de linha pelo primeiro caractere ou estrutura
            // Se começar por M;, F; ou N; é um detalhe do colaborador atual
            try {
                if (linha.substr(0, 2) == "M;") {
                    // Linha de Marcação: M;Ano;Mes;Dia;Tipo
                    char ignore;
                    int a, m, d;
                    char t;
                    ss >> ignore >> ignore >> a >> ignore >> m >> ignore >> d >> ignore >> t;
                    if (atual) atual->adicionarMarcacao(a, m, d, t);
                }
                else if (linha.substr(0, 2) == "F;") {
                    // Linha de Formação: F;Curso;Data
                    string tag, curso, data;
                    getline(ss, tag, ';');
                    getline(ss, curso, ';');
                    getline(ss, data);
                    if (atual) atual->adicionarFormacao(curso, data);
                }
                else if (linha.substr(0, 2) == "N;") {
                    // Linha de Nota: N;Texto;Data
                    string tag, texto, data;
                    getline(ss, tag, ';');
                    getline(ss, texto, ';');
                    getline(ss, data);
                    if (atual) atual->adicionarNota(texto, data);
                }
                else {
                    // Linha de Colaborador: ID;NomeCifrado;Departamento
                    // Tenta ler ID primeiro
                    string idStr, nomeCif, dep;
                    getline(ss, idStr, ';');
                    getline(ss, nomeCif, ';');
                    getline(ss, dep);

                    // Verifica se idStr contém apenas dígitos para evitar erros de stoi
                    bool isNum = !idStr.empty() && std::all_of(idStr.begin(), idStr.end(), ::isdigit);

                    if (isNum) {
                        // Se não houver departamento (formato antigo), define padrão
                        if (dep.empty()) dep = "Geral";

                        // Adiciona colaborador e define como atual para receber os detalhes seguintes
                        rh.adicionarColaborador(decifrar(nomeCif), dep, stoi(idStr));
                        atual = rh.obterColaborador(decifrar(nomeCif));
                    }
                }
            } catch (...) {
                // Ignora linhas malformadas
                continue;
            }
        }
        return true;
    }

    // Exporta um relatório legível para ficheiro de texto
    // Pode filtrar por departamento
    bool exportarRelatorio(const RH& rh, const std::string& nomeFicheiro, const std::string& departamentoFiltro) {
        std::ofstream ofs(nomeFicheiro);
        if (!ofs.is_open()) return false;

        ofs << "=== RELATORIO DE RECURSOS HUMANOS ===\n\n";

        for (const auto& c : rh.listar()) {
            // Aplica filtro de departamento se especificado
            if (!departamentoFiltro.empty() && c.getDepartamento() != departamentoFiltro) {
                continue;
            }

            ofs << "Colaborador: " << c.getNome() << " (ID: " << c.getId() << ")\n";
            ofs << "Departamento: " << c.getDepartamento() << "\n";
            
            // Resumo de Férias e Faltas
            int f = 0, x = 0;
            for (const auto& m : c.getMarcacoes()) {
                if (m.tipo == 'F') f++;
                if (m.tipo == 'X') x++;
            }
            ofs << "Total Ferias: " << f << " | Total Faltas: " << x << "\n";

            // Lista Formações
            if (!c.getFormacoes().empty()) {
                ofs << "Formacoes:\n";
                for (const auto& form : c.getFormacoes()) {
                    ofs << " - " << form.nome_curso << " (" << form.data_conclusao << ")\n";
                }
            }

            // Lista Notas
            if (!c.getNotas().empty()) {
                ofs << "Notas:\n";
                for (const auto& n : c.getNotas()) {
                    ofs << " - [" << n.data << "] " << n.texto << "\n";
                }
            }
            ofs << "----------------------------------------\n";
        }
        return true;
    }
}