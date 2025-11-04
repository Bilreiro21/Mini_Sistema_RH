#include <iostream>
#include <string>
#include <iomanip>
#include "controllers/rh.h"
#include "models/utils.h"
#include "views/io.h"
#include "views/cores.h" // cores

using namespace std;


const string FICHEIRO_DADOS = "dados_rh.txt";

void mostrarMenu() {
    cout << Cor::NEGRITO << Cor::CIANO << "\n===== MINI-SISTEMA RH =====\n" << Cor::RESET;
    cout << "1. Adicionar colaborador\n";
    cout << "2. Listar colaboradores\n";
    cout << "3. Marcar " << Cor::AZUL << "FERIAS (F)" << Cor::RESET << "\n";
    cout << "4. Marcar " << Cor::VERMELHO << "FALTA (X)" << Cor::RESET << "\n";
    cout << "5. Desmarcar dia\n";
    cout << "6. Ver calendario mensal de colaborador\n";
    cout << Cor::AMARELO << "0. Sair (guarda automaticamente)\n" << Cor::RESET;
    cout << Cor::NEGRITO << "Opcao: " << Cor::RESET;
}

void listarColabs(const RH& rh) {
    cout << Cor::NEGRITO << Cor::MAGENTA << "\n-- Colaboradores --\n" << Cor::RESET;
    const auto &lista = rh.listar();
    if (lista.empty()) {
        cout << Cor::AMARELO << "(nenhum)\n" << Cor::RESET;
        return;
    }
    for (size_t i = 0; i < lista.size(); ++i) {
        cout << (i+1) << ". " << lista[i].getNome() << "\n";
    }
}

void mostrarCalendarioColab(Colaborador* c, int ano, int mes) {
    if (!c) return;

    cout << Cor::NEGRITO << Cor::CIANO << "\nCalendario de " << c->getNome()
         << " - " << nomeMes(mes) << " " << ano << Cor::RESET << "\n";
    cout << Cor::NEGRITO << "Dom Seg Ter Qua Qui Sex Sab\n" << Cor::RESET;

    int primeiroDW = diaDaSemana(ano, mes, 1); 
    int totalDias  = diasNoMes(mes, ano);

    int col = 0;
    // espaços até ao primeiro dia
    for (int i = 0; i < primeiroDW; ++i) {
        cout << setw(3) << " ";
        col++;
    }

    for (int dia = 1; dia <= totalDias; ++dia) {
        char mk = c->obterMarcacao(ano, mes, dia);
        bool fimsem = isFimDeSemana(ano, mes, dia);

        string out;
        string cor = Cor::RESET;

        if (mk == 'F') {
            out = "F";
            cor = Cor::AZUL;
        } else if (mk == 'X') {
            out = "X";
            cor = Cor::VERMELHO;
        } else if (fimsem) {
            out = "-";
            cor = Cor::AMARELO;
        } else {
            out = to_string(dia);
        }

        if (out.size() == 1) out = " " + out;

        cout << cor << setw(2) << out << Cor::RESET << " ";
        col++;
        if (col == 7) {
            cout << "\n";
            col = 0;
        }
    }
    if (col != 0) cout << "\n";
    cout << "Legenda: " << Cor::AZUL << "F=ferias" << Cor::RESET
         << ", " << Cor::VERMELHO << "X=falta" << Cor::RESET
         << ", " << Cor::AMARELO << "-=fim-de-semana" << Cor::RESET << "\n";
}

int main() {

    RH rh;

    IO::carregar(rh, FICHEIRO_DADOS);

    int opc = -1;
    while (true) {
        mostrarMenu();
        cin >> opc;
        cin.ignore(1024, '\n');

        if (opc == 0) {
            if (!IO::guardar(rh, FICHEIRO_DADOS)) {
                cout << Cor::VERMELHO << "Aviso: nao foi possivel guardar no ficheiro.\n" << Cor::RESET;
            } else {
                cout << Cor::VERDE << "Dados guardados em '" << FICHEIRO_DADOS << "'.\n" << Cor::RESET;
            }
            break;
        }
        else if (opc == 1) {
            cout << "Nome do colaborador: ";
            string nome;
            getline(cin, nome);
            if (nome.empty()) {
                cout << Cor::VERMELHO << "Nome invalido.\n" << Cor::RESET;
                continue;
            }
            if (!rh.adicionarColaborador(nome)) {
                cout << Cor::VERMELHO << "Ja existe colaborador com esse nome.\n" << Cor::RESET;
            } else {
                cout << Cor::VERDE << "Colaborador adicionado.\n" << Cor::RESET;
            }
        }
        else if (opc == 2) {
            listarColabs(rh);
        }
        else if (opc == 3 || opc == 4) {
            cout << "Nome do colaborador: ";
            string nome;
            getline(cin, nome);
            if (!rh.existeColaborador(nome)) {
                cout << Cor::VERMELHO << "Colaborador nao existe.\n" << Cor::RESET;
                continue;
            }

            int a, m, d;
            cout << "Ano: "; cin >> a;
            cout << "Mes (1-12): "; cin >> m;
            cout << "Dia: "; cin >> d;
            cin.ignore(1024, '\n');

            if (!dataValida(a, m, d)) {
                cout << Cor::VERMELHO << "Data invalida.\n" << Cor::RESET;
                continue;
            }
            if (isFimDeSemana(a, m, d)) {
                cout << Cor::VERMELHO << "Nao e permitido marcar ao fim de semana.\n" << Cor::RESET;
                continue;
            }

            char tipo = (opc == 3) ? 'F' : 'X';
            if (rh.marcar(nome, a, m, d, tipo)) {
                cout << Cor::VERDE << "Marcado com sucesso.\n" << Cor::RESET;
            } else {
                cout << Cor::VERMELHO << "Falha ao marcar.\n" << Cor::RESET;
            }
        }
        else if (opc == 5) {
            cout << "Nome do colaborador: ";
            string nome;
            getline(cin, nome);
            if (!rh.existeColaborador(nome)) {
                cout << Cor::VERMELHO << "Colaborador nao existe.\n" << Cor::RESET;
                continue;
            }
            int a, m, d;
            cout << "Ano: "; cin >> a;
            cout << "Mes (1-12): "; cin >> m;
            cout << "Dia: "; cin >> d;
            cin.ignore(1024, '\n');

            if (rh.desmarcar(nome, a, m, d)) {
                cout << Cor::VERDE << "Desmarcado.\n" << Cor::RESET;
            } else {
                cout << Cor::AMARELO << "Nao havia marcacao para esse dia.\n" << Cor::RESET;
            }
        }
        else if (opc == 6) {
            cout << "Nome do colaborador: ";
            string nome;
            getline(cin, nome);
            Colaborador* c = rh.obterColaborador(nome);
            if (!c) {
                cout << Cor::VERMELHO << "Colaborador nao existe.\n" << Cor::RESET;
                continue;
            }
            int a, m;
            cout << "Ano: "; cin >> a;
            cout << "Mes (1-12): "; cin >> m;
            cin.ignore(1024, '\n');

            if (m < 1 || m > 12) {
                cout << Cor::VERMELHO << "Mes invalido.\n" << Cor::RESET;
                continue;
            }
            mostrarCalendarioColab(c, a, m);
        }
        else {
            cout << Cor::VERMELHO << "Opcao invalida.\n" << Cor::RESET;
        }
    }

    return 0;
}