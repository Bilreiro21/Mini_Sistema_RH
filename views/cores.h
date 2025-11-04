#ifndef CORES_H
#define CORES_H

#include <string>

/*
 * Namespace para guardar as constantes de cores ANSI.
 * NOTA: Funciona apenas se ativarCoresANSI() for chamada em main.cpp
 */
namespace Cor {
    // Estilos
    const std::string RESET = "\033[0m";
    const std::string NEGRITO = "\033[1m";
    const std::string SUBLINHADO = "\033[4m";

    // Cores do Texto
    const std::string PRETO = "\033[30m";
    const std::string VERMELHO = "\033[31m";
    const std::string VERDE = "\033[32m";
    const std::string AMARELO = "\033[33m";
    const std::string AZUL = "\033[34m";
    const std::string MAGENTA = "\033[35m";
    const std::string CIANO = "\033[36m";
    const std::string BRANCO = "\033[37m";

    // Cores de Fundo (Background)
    const std::string BG_PRETO = "\033[40m";
    const std::string BG_VERMELHO = "\033[41m";
    const std::string BG_VERDE = "\033[42m";
    const std::string BG_AMARELO = "\033[43m";
    const std::string BG_AZUL = "\033[44m";
    const std::string BG_MAGENTA = "\033[45m";
    const std::string BG_CIANO = "\033[46m";
    const std::string BG_BRANCO = "\033[47m";

} // namespace Cor

#endif // CORES_H