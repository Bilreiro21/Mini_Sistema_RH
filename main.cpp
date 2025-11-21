#include <iostream>
#include <string>
#include <iomanip>
#include <limits>
#include <cstddef>
#include <vector>
#include <algorithm>
#include "controllers/rh.h"
#include "models/utils.h"
#include "views/io.h"
#include "views/cores.h"

using namespace std;

// Nome do ficheiro onde os dados são guardados automaticamente
const string FICHEIRO_DADOS = "dados_rh.txt";

// --- Funções Auxiliares de Input ---
// Lê uma linha inteira de texto, permitindo espaços (ex: "Diogo Bilreiro")
void lerString(string& s) {
    getline(cin, s);
}

// Lê um número inteiro e trata erros caso o utilizador insira texto
int lerInt() {
    int x;
    while (!(cin >> x)) {
        cin.clear(); // Limpa o estado de erro do cin
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignora o resto da linha inválida
        cout << Cor::VERMELHO << "Entrada invalida. Tente novamente: " << Cor::RESET;
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Limpa o buffer após ler o número
    return x;
}

// --- Menus e Funcionalidades ---

// Exibe o menu principal com todas as opções disponíveis
void mostrarMenu() {
    cout << Cor::NEGRITO << Cor::CIANO << "\n===== RH AVANCADO =====\n" << Cor::RESET;
    cout << " 1. Adicionar Colaborador\n";
    cout << " 2. Listar Colaboradores\n";
    cout << " 3. Marcar Ferias/Faltas\n";
    cout << " 4. Desmarcar Dia\n";
    cout << " 5. Relatorios Mensais\n";
    cout << " 6. Buscar Colaborador (Nome/ID)\n";
    cout << " 7. Estatisticas de Departamento\n";
    cout << " 8. Dashboard Resumido\n";
    cout << " 9. Gestao de Formacoes\n";
    cout << "10. Gestao de Notas\n";
    cout << "11. Exportar Relatorio\n";
    cout << Cor::AMARELO << " 0. Sair\n" << Cor::RESET;
    cout << Cor::NEGRITO << "Opcao: " << Cor::RESET;
}

// Lista todos os colaboradores de forma formatada (tabela)
void listarColabs(const RH& rh) {
    cout << Cor::NEGRITO << Cor::MAGENTA << "\n-- Colaboradores --\n" << Cor::RESET;
    const auto &lista = rh.listar();
    if (lista.empty()) {
        cout << Cor::AMARELO << "(nenhum)\n" << Cor::RESET;
        return;
    }
    // setw define a largura da coluna para alinhar o texto
    cout << left << setw(5) << "ID" << setw(20) << "Nome" << setw(15) << "Departamento" << "\n";
    cout << "----------------------------------------\n";
    for (const auto& c : lista) {
        cout << left << setw(5) << c.getId() << setw(20) << c.getNome() << setw(15) << c.getDepartamento() << "\n";
    }
}

// Exibe o calendário mensal de um colaborador com as marcações (Férias/Faltas)
void mostrarCalendarioColab(Colaborador* c, int ano, int mes) {
    if (!c) return;

    cout << Cor::NEGRITO << Cor::CIANO << "\nCalendario de " << c->getNome()
         << " - " << nomeMes(mes) << " " << ano << Cor::RESET << "\n";
    cout << Cor::NEGRITO << "Dom Seg Ter Qua Qui Sex Sab\n" << Cor::RESET;

    // Calcula em que dia da semana começa o mês e quantos dias tem
    int primeiroDW = diaDaSemana(ano, mes, 1); 
    int totalDias  = diasNoMes(mes, ano);

    int col = 0;
    // Espaços em branco até ao primeiro dia do mês
    for (int i = 0; i < primeiroDW; ++i) {
        cout << setw(3) << " ";
        col++;
    }

    // Loop para imprimir os dias do mês
    for (int dia = 1; dia <= totalDias; ++dia) {
        char mk = c->obterMarcacao(ano, mes, dia);
        bool fimsem = isFimDeSemana(ano, mes, dia);

        string out;
        string cor = Cor::RESET;

        // Define o que mostrar e a cor baseada no tipo de dia/marcação
        if (mk == 'F') {
            out = "F"; // Férias
            cor = Cor::AZUL;
        } else if (mk == 'X') {
            out = "X"; // Falta
            cor = Cor::VERMELHO;
        } else if (fimsem) {
            out = "-"; // Fim de semana
            cor = Cor::AMARELO;
        } else {
            out = to_string(dia); // Dia normal
        }

        if (out.size() == 1) out = " " + out; // Alinhamento

        cout << cor << setw(2) << out << Cor::RESET << " ";
        col++;
        if (col == 7) { // Quebra de linha ao fim da semana (Sábado)
            cout << "\n";
            col = 0;
        }
    }
    if (col != 0) cout << "\n";
}

// Req 1: Relatórios Mensais - Mostra totais de férias e faltas por colaborador num mês
void relatorioMensal(const RH& rh) {
    int ano, mes;
    cout << "Ano: "; ano = lerInt();
    cout << "Mes: "; mes = lerInt();

    cout << "\n--- Relatorio " << mes << "/" << ano << " ---\n";
    for (const auto& c : rh.listar()) {
        int f = 0, x = 0;
        // Conta as marcações do mês específico
        for (const auto& m : c.getMarcacoes()) {
            if (m.ano == ano && m.mes == mes) {
                if (m.tipo == 'F') f++;
                if (m.tipo == 'X') x++;
            }
        }
        cout << left << setw(20) << c.getNome() 
             << " | Ferias: " << setw(2) << f 
             << " | Faltas: " << setw(2) << x << "\n";
    }
}

// Req 2: Busca - Permite encontrar colaboradores por Nome ou ID
void buscarColaborador(RH& rh) {
    cout << "Buscar por (1) Nome ou (2) ID? ";
    int op = lerInt();
    Colaborador* c = nullptr;
    
    if (op == 1) {
        cout << "Nome: ";
        string nome;
        lerString(nome);
        c = rh.obterColaborador(nome);
    } else if (op == 2) {
        cout << "ID: ";
        int id = lerInt();
        c = rh.obterColaboradorPorId(id);
    }

    if (c) {
        cout << Cor::VERDE << "Encontrado: " << c->getNome() << " (ID: " << c->getId() << ")\n" << Cor::RESET;
        cout << "Departamento: " << c->getDepartamento() << "\n";
        
        // Oferece visualização imediata do calendário
        cout << "Ver calendario de qual mes/ano? \n";
        int a, m;
        cout << "Ano: "; a = lerInt();
        cout << "Mes: "; m = lerInt();
        mostrarCalendarioColab(c, a, m);
    } else {
        cout << Cor::VERMELHO << "Nao encontrado.\n" << Cor::RESET;
    }
}

// Req 3: Estatisticas - Agrega dados por departamento
void estatisticasDepartamento(const RH& rh) {
    auto stats = rh.getEstatisticasDepartamento();
    cout << "\n--- Estatisticas por Departamento ---\n";
    string piorDep;
    int maxAusencias = -1;

    for (const auto& par : stats) {
        int total = par.second.first + par.second.second; // Soma Férias + Faltas
        cout << "Dep: " << setw(15) << par.first 
             << " | Ferias: " << par.second.first 
             << " | Faltas: " << par.second.second 
             << " | Total Ausencias: " << total << "\n";
        
        // Identifica o departamento com mais ausências
        if (total > maxAusencias) {
            maxAusencias = total;
            piorDep = par.first;
        }
    }
    if (!piorDep.empty()) {
        cout << Cor::AMARELO << "Departamento com mais ausencias: " << piorDep << " (" << maxAusencias << ")\n" << Cor::RESET;
    }
}

// Req 5: Dashboard - Visão geral dos saldos de férias
void dashboard(const RH& rh) {
    cout << "\n--- Dashboard Resumido ---\n";
    cout << left << setw(20) << "Nome" << setw(10) << "Ferias" << setw(10) << "Faltas" << "Dias Restantes (Ferias)\n";
    
    const int MAX_FERIAS = 22; // Base de dias de férias anuais

    for (const auto& c : rh.listar()) {
        int f = 0, x = 0;
        for (const auto& m : c.getMarcacoes()) {
            if (m.tipo == 'F') f++;
            if (m.tipo == 'X') x++;
        }
        int restantes = MAX_FERIAS - f;
        cout << left << setw(20) << c.getNome() 
             << setw(10) << f 
             << setw(10) << x 
             << restantes << "\n";
    }
}

// Req 6: Formacoes - Submenu para gerir cursos
void gerirFormacoes(RH& rh) {
    cout << "Nome do colaborador: ";
    string nome;
    lerString(nome);
    Colaborador* c = rh.obterColaborador(nome);
    if (!c) { cout << Cor::VERMELHO << "Nao encontrado.\n" << Cor::RESET; return; }

    cout << "1. Listar\n2. Adicionar\n3. Remover\n4. Editar\nOpcao: ";
    int op = lerInt();

    if (op == 1) {
        const auto& fs = c->getFormacoes();
        if (fs.empty()) cout << "(sem formacoes)\n";
        for (size_t i=0; i<fs.size(); ++i) {
            cout << i+1 << ". " << fs[i].nome_curso << " (" << fs[i].data_conclusao << ")\n";
        }
    } else if (op == 2) {
        cout << "Nome do Curso: "; string curso; lerString(curso);
        cout << "Data Conclusao: "; string data; lerString(data);
        c->adicionarFormacao(curso, data);
        cout << Cor::VERDE << "Adicionado.\n" << Cor::RESET;
    } else if (op == 3) {
        cout << "Numero da formacao a remover: ";
        int idx = lerInt();
        c->removerFormacao(idx - 1);
        cout << Cor::VERDE << "Removido.\n" << Cor::RESET;
    } else if (op == 4) {
        cout << "Numero da formacao a editar: ";
        int idx = lerInt();
        cout << "Novo Nome (Enter para manter): "; string curso; lerString(curso);
        cout << "Nova Data (Enter para manter): "; string data; lerString(data);
        c->editarFormacao(idx - 1, curso, data);
        cout << Cor::VERDE << "Editado.\n" << Cor::RESET;
    }
}

// Req 7: Notas - Submenu para gerir notas internas
void gerirNotas(RH& rh) {
    cout << "Nome do colaborador: ";
    string nome;
    lerString(nome);
    Colaborador* c = rh.obterColaborador(nome);
    if (!c) { cout << Cor::VERMELHO << "Nao encontrado.\n" << Cor::RESET; return; }

    cout << "1. Listar\n2. Adicionar\n3. Remover\n4. Editar\nOpcao: ";
    int op = lerInt();

    if (op == 1) {
        const auto& ns = c->getNotas();
        if (ns.empty()) cout << "(sem notas)\n";
        for (size_t i=0; i<ns.size(); ++i) {
            cout << i+1 << ". [" << ns[i].data << "] " << ns[i].texto << "\n";
        }
    } else if (op == 2) {
        cout << "Texto da Nota: "; string txt; lerString(txt);
        cout << "Data: "; string data; lerString(data);
        c->adicionarNota(txt, data);
        cout << Cor::VERDE << "Adicionada.\n" << Cor::RESET;
    } else if (op == 3) {
        cout << "Numero da nota a remover: ";
        int idx = lerInt();
        c->removerNota(idx - 1);
        cout << Cor::VERDE << "Removida.\n" << Cor::RESET;
    } else if (op == 4) {
        cout << "Numero da nota a editar: ";
        int idx = lerInt();
        cout << "Novo Texto (Enter para manter): "; string txt; lerString(txt);
        cout << "Nova Data (Enter para manter): "; string data; lerString(data);
        c->editarNota(idx - 1, txt, data);
        cout << Cor::VERDE << "Editada.\n" << Cor::RESET;
    }
}

int main() {
    RH rh;
    // Carrega os dados do ficheiro ao iniciar
    IO::carregar(rh, FICHEIRO_DADOS);

    while (true) {
        mostrarMenu();
        int opc = lerInt();

        if (opc == 0) {
            // Guarda os dados antes de sair
            if (IO::guardar(rh, FICHEIRO_DADOS)) {
                cout << Cor::VERDE << "Dados guardados.\n" << Cor::RESET;
            } else {
                cout << Cor::VERMELHO << "Erro ao guardar.\n" << Cor::RESET;
            }
            break;
        }
        else if (opc == 1) {
            cout << "Nome: "; string nome; lerString(nome);
            cout << "Departamento: "; string dep; lerString(dep);
            if (rh.adicionarColaborador(nome, dep)) {
                cout << Cor::VERDE << "Adicionado.\n" << Cor::RESET;
            } else {
                cout << Cor::VERMELHO << "Erro/Duplicado.\n" << Cor::RESET;
            }
        }
        else if (opc == 2) {
            listarColabs(rh);
        }
        else if (opc == 3 || opc == 4) { // Marcar / Desmarcar
             bool marcar = (opc == 3);
             cout << "Nome: "; string nome; lerString(nome);
             if (!rh.existeColaborador(nome)) {
                 cout << Cor::VERMELHO << "Nao existe.\n" << Cor::RESET; continue;
             }
             int a, m, d;
             cout << "Ano: "; a = lerInt();
             cout << "Mes: "; m = lerInt();
             cout << "Dia: "; d = lerInt();

             if (marcar) {
                 cout << "(F)erias ou (X)Falta? ";
                 string t; lerString(t);
                 char tipo = (t.size() > 0) ? toupper(t[0]) : 'F';
                 
                 // Req 4: Aviso de Conflito - Verifica se há colegas do mesmo departamento de férias
                 if (tipo == 'F' && rh.verificarConflitoFerias(nome, a, m, d)) {
                     cout << Cor::AMARELO << "AVISO: Outro colaborador do mesmo departamento tem ferias neste dia!\n" << Cor::RESET;
                     cout << "Deseja continuar? (S/N): ";
                     string conf; lerString(conf);
                     if (toupper(conf[0]) != 'S') continue;
                 }

                 if (rh.marcar(nome, a, m, d, tipo)) cout << Cor::VERDE << "Marcado.\n" << Cor::RESET;
                 else cout << Cor::VERMELHO << "Erro ao marcar.\n" << Cor::RESET;
             } else {
                 // Desmarcar
                 if (rh.desmarcar(nome, a, m, d)) cout << Cor::VERDE << "Desmarcado.\n" << Cor::RESET;
                 else cout << Cor::VERMELHO << "Erro/Nao encontrado.\n" << Cor::RESET;
             }
        }
        else if (opc == 5) relatorioMensal(rh);
        else if (opc == 6) buscarColaborador(rh);
        else if (opc == 7) estatisticasDepartamento(rh);
        else if (opc == 8) dashboard(rh);
        else if (opc == 9) gerirFormacoes(rh);
        else if (opc == 10) gerirNotas(rh);
        else if (opc == 11) {
            cout << "Nome do ficheiro (ex: relatorio.txt): "; string f; lerString(f);
            cout << "Filtrar por departamento (Enter para todos): "; string d; lerString(d);
            if (IO::exportarRelatorio(rh, f, d)) cout << Cor::VERDE << "Exportado.\n" << Cor::RESET;
            else cout << Cor::VERMELHO << "Erro.\n" << Cor::RESET;
        }
        else {
            cout << Cor::VERMELHO << "Opcao invalida.\n" << Cor::RESET;
        }
    }
    return 0;
}