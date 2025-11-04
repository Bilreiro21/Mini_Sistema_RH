#include "io.h"
#include "../controllers/rh.h"
#include <fstream>
#include <sstream>
#include <cctype>

namespace IO
{
    std::string cifrar(const std::string &texto, int chave)
    {
        std::string resultado = texto;

        // Percorre cada caractere do texto
        for (size_t i = 0; i < texto.size(); ++i)
        {
            char c = texto[i];

            // Apenas processa letras (A-Z, a-z)
            if (std::isalpha(c))
            {
                // Define a base: 'A' para maiúsculas, 'a' para minúsculas
                char base = std::isupper(c) ? 'A' : 'a';

                // Aplica a cifra: desloca a letra e usa módulo 26 para dar a volta ao alfabeto
                resultado[i] = char((c - base + chave) % 26 + base);
            }
            else
            {
                // Mantém caracteres não-alfabéticos (espaços, números, pontuação)
                resultado[i] = c;
            }
        }
        return resultado;
    }

    std::string decifrar(const std::string &texto, int chave)
    {
        // Decifra usando a cifra de César inversa
        return cifrar(texto, 26 - (chave % 26));
    }


    // Guarda todos os dados do RH num ficheiro
    bool guardar(const RH &rh, const std::string &filename)
    {
        // Abre ficheiro para escrita
        std::ofstream f(filename.c_str());
        if (!f.is_open())
            return false; // Erro ao abrir ficheiro

        const int K = 3; // Chave da cifra de César (desloca 3 posições)
        const auto &lista = rh.listar();

        // Escreve o número total de colaboradores
        f << lista.size() << "\n";

        // Percorre cada colaborador
        for (const auto &c : lista)
        {
            // Cifra o nome do colaborador para segurança
            std::string nomeCif = cifrar(c.getNome(), K);
            const auto &marc = c.getMarcacoes();

            // Escreve o nome cifrado e o número de marcações
            f << nomeCif << ";" << marc.size() << "\n";

            // Escreve cada marcação do colaborador
            for (const auto &m : marc)
            {
                // Formato: ano;mês;dia;tipo
                f << m.ano << ";" << m.mes << ";" << m.dia << ";" << m.tipo << "\n";
            }
        }
        return true;
    }

    // Carrega dados do RH a partir de um ficheiro
    bool carregar(RH &rh, const std::string &filename)
    {
        // Abre ficheiro para leitura
        std::ifstream f(filename.c_str());
        if (!f.is_open())
        {
            // Primeiro arranque: ficheiro ainda não existe, não é erro
            return false;
        }

        const int K = 3; // Mesma chave usada na cifragem
        size_t n;

        // Lê o número de colaboradores
        f >> n;
        f.ignore(1024, '\n'); // Ignora o resto da linha

        // Processa cada colaborador
        for (size_t i = 0; i < n; ++i)
        {
            std::string linha;
            if (!std::getline(f, linha))
                break; // Fim do ficheiro

            // Ignora linhas vazias
            if (linha.empty())
            {
                --i;
                continue;
            }

            // Parse da linha: nome_cifrado;número_marcações
            std::stringstream ss(linha);
            std::string nomeCif, numStr;

            if (!std::getline(ss, nomeCif, ';'))
                continue;
            if (!std::getline(ss, numStr, ';'))
                continue;

            // Decifra o nome e obtém quantidade de marcações
            std::string nome = decifrar(nomeCif, K);
            int q = std::stoi(numStr);

            // Adiciona o colaborador ao sistema
            rh.adicionarColaborador(nome);
            Colaborador *col = rh.obterColaborador(nome);

            // Lê todas as marcações deste colaborador
            for (int k = 0; k < q; ++k)
            {
                std::string l2;
                if (!std::getline(f, l2))
                    break;

                // Ignora linhas vazias
                if (l2.empty())
                {
                    --k;
                    continue;
                }

                // Parse da marcação: ano;mês;dia;tipo
                std::stringstream ss2(l2);
                std::string sa, sm, sd, st;
                std::getline(ss2, sa, ';');
                std::getline(ss2, sm, ';');
                std::getline(ss2, sd, ';');
                std::getline(ss2, st, ';');

                // Converte strings para valores numéricos
                int a = std::stoi(sa);
                int m = std::stoi(sm);
                int d = std::stoi(sd);
                char t = st.empty() ? 'F' : st[0]; // Default 'F' se vazio

                // Adiciona a marcação ao colaborador
                if (col)
                {
                    col->adicionarMarcacao(a, m, d, t);
                }
            }
        }

        return true; // Carregamento bem-sucedido
    }

}